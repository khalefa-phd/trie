class meta {
 public:
   set<string> setMetaResults;

#ifdef __STAT__
   size_t cnt = 0;
   size_t max_mapp = 0;
   inline void update_stat(bool inc = true) {
      max_mapp = max(max_mapp, mapP.size());
      if (inc) cnt++;
   }
#else
   inline void update_stat(bool inc = true) {}
#endif

   meta(string strPrefixQeury, int k) {
      int* arrB = new int[strPrefixQeury.length() + 1];
      arrB[0] = 0;
      MatchingTriple* mtTemp = new MatchingTriple(0, trie::root, 0, false);
      mapP[trie::root] = mtTemp;
      for (int i = 0; i < strPrefixQeury.length(); i++) {
         ///////////////First Deducing/////////////////
         setMetaResults.clear();
         mapH.clear();
         update_stat();
         int iED;
         for (pair<BasicTrieNode*, MatchingTriple*> element : mapP) {
            update_stat();
            MatchingTriple* mtM = element.second;
            mtM->iNextQueryIndex = i;
            for (int d = mtM->btnNode->iDepth + 1;
                 d <= (mtM->btnNode->iDepth + 1 + arrB[i]); d++) {
               update_stat();

               if (trie::Index[d][strPrefixQeury[i] - 'a'].size() == 0)
                  continue;
               for (BasicTrieNode* btnNode :
                    trie::Index[d][strPrefixQeury[i] - 'a']) {

                  update_stat();

                  if ((btnNode->iID < mtM->btnNode->iMinNodeID) ||
                      (btnNode->iID > mtM->btnNode->iMaxNodeID))
                     continue;
                  if ((i - 1 - mtM->iMatchingIndex) >
                      (btnNode->iDepth - 1 - mtM->btnNode->iDepth))
                     iED = mtM->iED + (i - 1 - mtM->iMatchingIndex);
                  else
                     iED = mtM->iED +
                           (btnNode->iDepth - 1 - mtM->btnNode->iDepth);
                  if (mapH.find(btnNode) != mapH.end()) {

                     if (mapH[btnNode] > (iED)) mapH[btnNode] = iED;
                  } else {
                     mapH[btnNode] = iED;
                  }
               }
            }
         }
         for (pair<BasicTrieNode*, int> entry : mapH) {
            update_stat();
            mtTemp =
                new MatchingTriple(i + 1, entry.first, entry.second, false);
            if (mapP.find(entry.first) == mapP.end())
               mapP[entry.first] = mtTemp;
            else if ((mapP[entry.first]->iED + i -
                      mapP[entry.first]->iMatchingIndex) > entry.second)
               mapP[entry.first] = mtTemp;
         }
         for (pair<BasicTrieNode*, MatchingTriple*> element : mapP) {
            update_stat();
            MatchingTriple* mtM = element.second;
            if ((mtM->iED + i - (mtM->iMatchingIndex - 1)) < arrB[i - 1]) {
               for (int w = mtM->btnNode->iMin; w <= mtM->btnNode->iMax; w++) {
                  if (setMetaResults.find(trie::Dictionary[w]) ==
                      setMetaResults.end())
                     setMetaResults.insert(trie::Dictionary[w]);
                  if (setMetaResults.size() >= k) { break; }
               }
            }
         }
         if (SecondDeducing(strPrefixQeury, i, arrB[i], k))
            arrB[i + 1] = arrB[i];
         else if (SecondDeducing(strPrefixQeury, i, arrB[i] + 1, k))
            arrB[i + 1] = arrB[i] + 1;
      }
      // clear memory
      delete[] arrB;
      for (pair<BasicTrieNode*, MatchingTriple*> element : mapP) {
         if (element.second != nullptr) delete element.second;
      }
      return;
   }

 private:
   bool SecondDeducing(string strPrefixQeury, int i, int b, int k) {
      MatchingTriple* mtTemp;
      map<BasicTrieNode*, int> mapH;
      for (pair<BasicTrieNode*, MatchingTriple*> element : mapP) {
         update_stat();
         MatchingTriple* mtM = element.second;
         if ((mtM->iED + i - (mtM->iMatchingIndex - 1)) == b) {
            for (int w = mtM->btnNode->iMin; w <= mtM->btnNode->iMax; w++) {
               if (setMetaResults.find(trie::Dictionary[w]) ==
                   setMetaResults.end())
                  setMetaResults.insert(trie::Dictionary[w]);
               if (setMetaResults.size() >= k) { return true; }
            }
         }
         int iED;
         for (int d = mtM->btnNode->iDepth + 1;
              d <= (mtM->btnNode->iDepth + 1 + b - mtM->iED); d++) {

            auto lst = trie::Index[d][strPrefixQeury[i] - 'a'];
            vector<BasicTrieNode*>::iterator start = std::lower_bound(
                lst.begin(), lst.end(), mtM->btnNode->iMinNodeID,
                [](const BasicTrieNode* element, const long value) {
                   return element->iID < value;
                });

            for (; start != lst.end(); start++) {
               BasicTrieNode* btnNode = *start;
               update_stat();
               if (btnNode->iID > mtM->btnNode->iMaxNodeID) break;
               if ((i - 1 - mtM->iMatchingIndex) >
                   (btnNode->iDepth - 1 - mtM->btnNode->iDepth))
                  iED = mtM->iED + (i - 1 - mtM->iMatchingIndex);
               else
                  iED = mtM->iED + (btnNode->iDepth - 1 - mtM->btnNode->iDepth);
               if (iED == b) {
                  if (mapH.find(btnNode) != mapH.end()) {

                     if (mapH[btnNode] > (iED)) mapH[btnNode] = iED;
                  } else {
                     mapH[btnNode] = iED;
                  }
               }
            }
         }
      }
      for (pair<BasicTrieNode*, int> entry : mapH) {
         update_stat();

         mtTemp = new MatchingTriple(i + 1, entry.first, entry.second, false);
         if (mapP.find(entry.first) == mapP.end())
            mapP[entry.first] = mtTemp;
         else if ((mapP[entry.first]->iED + i -
                   mapP[entry.first]->iMatchingIndex) > entry.second)
            mapP[entry.first] = mtTemp;
      }
      return false;
   }

   map<BasicTrieNode*, MatchingTriple*> mapP;
   map<BasicTrieNode*, int> mapH;
};

class META {
 public:
   static void run(string expr, vector<pair<string, string>>& results,
                   string& q, int k) {

#ifdef __STAT__
      size_t cnt;
      size_t max_mapp;
#endif

      auto start = std::chrono::high_resolution_clock::now();
      for (size_t i = 0; i < REP; i++) {
         meta m(q, k);
         escape(&m.setMetaResults);
#ifdef __TEST__
         for (auto x : m.setMetaResults) cout << "\t\t*" << x << endl;
         cout << endl;
#endif
#ifdef __STAT__
         cnt = m.cnt;
         max_mapp = m.max_mapp;
#endif
      }
      string stat = "";
#ifdef __STAT__
      stat = "," + to_string(cnt) + "," + to_string(max_mapp);
#endif
      auto finish = std::chrono::high_resolution_clock::now();
      results.push_back(make_pair(
          expr,
          to_string(chrono::duration<double, nano>(finish - start).count() /
                    REP) +
              stat));
   }
};
