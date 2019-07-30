template <typename K> class depth {
 public:
   set<string> results;
#ifdef __STAT__
   size_t cnt = 0;
   size_t max_mapp = 0;
   size_t max_heap = 0;
   inline void update_stat(bool inc = true) {
      max_mapp = max(max_mapp, mapP.size());
      if (inc) cnt++;
      max_heap = max(max_heap, setMinHeap.size());
   }
#else
   inline void update_stat(bool inc = true) {}
#endif

   depth(const string& strPrefixQeury, int k) {
      MatchingTriple* mtMin = new MatchingTriple(0, trie::root, 0, false);
      mtMin->iNextQueryIndex = 1;
      mtMin->dTopkStaticValue = trie::root->dTopkMinStaticValue;
      mapP[1] = mtMin;
      setMinHeap.insert(mtMin);
      update_stat();
      while ((setMinHeap.size() > 0) && results.size() < k) {
         mtMin = *setMinHeap.begin();
         setMinHeap.erase(mtMin);
         if (!mtMin->bFinished) {
            AddNextLevelMatching(strPrefixQeury, mtMin);
         } else if (!getMinStrings(mtMin, k)) {
            setMinHeap.insert(mtMin);
         }
      }
      for (pair<long, MatchingTriple*> element : mapP) {
         if (element.second != nullptr) delete element.second;
      }
      mapP.clear();
   }

 private:
   set<MatchingTriple*, K> setMinHeap;

   map<BasicTrieNode*, double> mapUserPath;
   double dMinStaticValue;
   map<long, MatchingTriple*> mapP;
   void AddNextLevelMatching(const string& strPrefixQeury,
                             MatchingTriple* mtCurrent) {
      bool bFinished = false;
      if (mtCurrent->iNextQueryIndex == (strPrefixQeury.length()))
         bFinished = true;

      {
         int d = mtCurrent->btnNode->iDepth + 1 + mtCurrent->iNextQueryIndex -
                 1 - mtCurrent->iMatchingIndex;
         auto lst =
             trie::Index[d]
                        [strPrefixQeury[mtCurrent->iNextQueryIndex - 1] - 'a'];

         vector<BasicTrieNode*>::iterator start = std::lower_bound(
             lst.begin(), lst.end(), mtCurrent->btnNode->iMinNodeID,
             [](const BasicTrieNode* element, const long value) {
                return element->iID < value;
             });

         for (; start != lst.end(); start++) {
            BasicTrieNode* btnNode = *start;
            update_stat();
            if (btnNode->iID > mtCurrent->btnNode->iMaxNodeID) break;
            if ((btnNode->iID >= mtCurrent->btnNode->iMinNodeID) &&
                (btnNode->iID <= mtCurrent->btnNode->iMaxNodeID)) {
               int iED = mtCurrent->iED;
               if ((mtCurrent->iNextQueryIndex - 1 -
                    mtCurrent->iMatchingIndex) >
                   (btnNode->iDepth - 1 - mtCurrent->btnNode->iDepth))
                  iED += (mtCurrent->iNextQueryIndex - 1 -
                          mtCurrent->iMatchingIndex);
               else
                  iED += (btnNode->iDepth - 1 - mtCurrent->btnNode->iDepth);

               MatchingTriple* mtNew = new MatchingTriple(
                   mtCurrent->iNextQueryIndex, btnNode, iED, bFinished);
               mtNew->iNextQueryIndex = mtCurrent->iNextQueryIndex;
               mtNew->dTopkStaticValue = btnNode->dTopkMinStaticValue;
               mtNew->dTopkOnlineValue = iED * D_TAU_WEIGHT;

               if (!bFinished) mtNew->iNextQueryIndex++;
               if (mapP.find(btnNode->iID) == mapP.end()) {
                  mapP[btnNode->iID] = mtNew;
                  setMinHeap.insert(mtNew);
               } else if ((mapP[btnNode->iID]->iED +
                           mapP[btnNode->iID]->iNextQueryIndex -
                           mapP[btnNode->iID]->iMatchingIndex) > iED) {
                  mapP[btnNode->iID] = mtNew;
                  setMinHeap.erase(mapP[btnNode->iID]);
                  setMinHeap.insert(mtNew);
               }
               update_stat(false);
            }
         }
      }
      mtCurrent->bFinished = bFinished;
      if (!bFinished) {
         mtCurrent->iNextQueryIndex++;
         mtCurrent->dTopkOnlineValue =
             (mapP[mtCurrent->btnNode->iID]->iED +
              mapP[mtCurrent->btnNode->iID]->iNextQueryIndex -
              mapP[mtCurrent->btnNode->iID]->iMatchingIndex) *
             D_TAU_WEIGHT;
      }
      setMinHeap.insert(mtCurrent);
   }

   const int I_RESULTS_FINISHED = -1000;
   const int I_ALL_NODE_STRINGS_RETRIVED = 1000;

   double getMinString(BasicTrieNode* btn, double dTopkStaticValue, int k) {
      if (btn->isEndOfWord) {
         if (results.find(trie::Dictionary[btn->iMin]) == results.end()) {
            results.insert(trie::Dictionary[btn->iMin]);
            if (results.size() == k) return I_RESULTS_FINISHED;
         }
         return I_ALL_NODE_STRINGS_RETRIVED;
      }

      double dNextStaticValue = I_ALL_NODE_STRINGS_RETRIVED;
      double dChildStaticValue;
      for (BasicTrieNode* btnqNext : btn->children) {
         if (btnqNext == NULL) continue;
         if (mapUserPath.find(btnqNext) == mapUserPath.end())
            mapUserPath[btnqNext] = btnqNext->dTopkMinStaticValue;
         dChildStaticValue = mapUserPath[btnqNext];
         if (dChildStaticValue ==
             I_ALL_NODE_STRINGS_RETRIVED) // has no strings left
            continue;
         if (dChildStaticValue == dTopkStaticValue)
            dChildStaticValue = getMinString(btnqNext, dTopkStaticValue, k);
         if (dChildStaticValue < dNextStaticValue)
            dNextStaticValue = dChildStaticValue;
         if (dChildStaticValue == I_RESULTS_FINISHED) return dChildStaticValue;
      }
      mapUserPath[btn] = dNextStaticValue;
      return dNextStaticValue;
   }

   bool getMinStrings(MatchingTriple* mt, int k) {
      int i = mt->lNextStringNodeIndex;
      for (; i < mt->btnNode->lstSortedStringNodes.size(); i++) {
         if (mt->btnNode->lstSortedStringNodes[i]->dStaticValue ==
             mt->dTopkStaticValue) {
            if (results.find(
                    trie::Dictionary[mt->btnNode->lstSortedStringNodes[i]
                                         ->lStringID]) == results.end()) {
               results.insert(
                   trie::Dictionary[mt->btnNode->lstSortedStringNodes[i]
                                        ->lStringID]);
               if (results.size() == k) return true;
            }
         } else
            break;
      }
      if (i == mt->btnNode->lstSortedStringNodes.size()) return true;
      mt->lNextStringNodeIndex = i;
      mt->dTopkStaticValue = mt->btnNode->lstSortedStringNodes[i]->dStaticValue;
      return false;
   }
};

template <typename K> class DEPTH {
 public:
   static void run(string expr, vector<pair<string, string>>& results,
                   string& q, int k) {

#ifdef __STAT__
      size_t cnt;
      size_t max_heap;
      size_t max_mapp;
#endif
      auto start = std::chrono::high_resolution_clock::now();
      for (size_t i = 0; i < REP; i++) {
         depth<K> d(q, k);
         escape(&d.results);
#ifdef __TEST__
         for (auto x : d.results) cout << "\t\t" << x << endl;
#endif
#ifdef __STAT__
         cnt = d.cnt;
         max_heap = d.max_heap;
         max_mapp = d.max_mapp;
#endif
      }
      auto finish = std::chrono::high_resolution_clock::now();
      string stat = "";
#ifdef __STAT__
      stat = "," + to_string(cnt) + "," + to_string(max_heap) + "," +
             to_string(max_mapp);
#endif
      results.push_back(make_pair(
          expr,
          to_string(chrono::duration<double, nano>(finish - start).count() /
                    REP) +
              stat));
   }
};
