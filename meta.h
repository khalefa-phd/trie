
struct score {
 private:
   int editdistance = 0;
   double staticvalue = 0;

 public:
   char flag = 0; // 0,1 ,2, 3
   static int ed;
   static double sv;

 public:
   score() { flag = 0; }
   score(int ed, double sv) {
      if (ed != -1) set_ed(ed);
      if (sv != -1) set_sv(sv);
   }

   void set_ed(int ed) {
      flag |= 1;
      this->editdistance = ed;
   }

   void set_sv(double staticvalue) {
      flag |= 2;
      this->staticvalue = staticvalue;
   }

   double getscore() const {
      double e = (flag & 1) ? this->editdistance : ed;
      double v = (flag & 2) ? this->staticvalue : sv;
      e = e * D_TAU_WEIGHT;
      return e + v;
   }
   bool complete() const { return flag == 3; }
};

int score::ed;
double score::sv;

bool operator<(const score& a, const score& b) {
   return a.getscore() < b.getscore();
}

class meta {
 public:
   map<size_t, int> res; // index, and tau
   set<string> results;
   int k;
   string query;
   size_t last_indeserted_id = -1;
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

   meta(string query, int k) : meta() {
      this->query = query;
      this->k = k;
      initialbatch(k);
      //   getstrings();
   }

   void getstrings() {
      results.clear();
      for (auto& x : res) results.insert(trie::Dictionary[x.first]);
   }

   ~meta() {
      for (pair<BasicTrieNode*, MatchingTriple*> element : mapP) {
         if (element.second != nullptr) delete element.second;
      }
      delete[] arrB;
   }

   pair<size_t, int> getnext() {
      static int cnt = 0;
      cnt++;
      int i = query.length() - 1;
      k++;

      if (SecondDeducing(i, arrB[i], k))
         ;
      else if (SecondDeducing(i, arrB[i] + 1, k))
         arrB[i]++;
      else
         return make_pair(-1, -1);
      getstrings();
      return make_pair(last_indeserted_id, arrB[i]);
   }

   int bound() { return arrB[query.length() - 1]; }

 protected:
   meta() { arrB = new int[query.length() + 1]; }

   void initialbatch(int k) {
      arrB[0] = 0;
      MatchingTriple* mtTemp = new MatchingTriple(0, trie::root, 0, false);
      mapP[trie::root] = mtTemp;
      for (int i = 0; i < query.length(); i++) {
         ///////////////First Deducing/////////////////
         res.clear();
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
               auto lst = trie::Index[d][query[i] - 'a'];

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
            if ((mtM->iED + i - (mtM->iMatchingIndex - 1)) < arrB[i]) {
               for (int w = mtM->btnNode->iMin; w <= mtM->btnNode->iMax; w++) {
                  if (res.find(w) == res.end()) res[w] = arrB[i];
                  if (res.size() >= k) { break; }
               }
            }
         }
         if (SecondDeducing(i, arrB[i], k))
            arrB[i + 1] = arrB[i];
         else if (SecondDeducing(i, arrB[i] + 1, k))
            arrB[i + 1] = arrB[i] + 1;
      }
   }

   bool SecondDeducing(int i, int b, int k) {
      MatchingTriple* mtTemp;
      map<BasicTrieNode*, int> mapH;
      for (pair<BasicTrieNode*, MatchingTriple*> element : mapP) {
         update_stat();
         MatchingTriple* mtM = element.second;
         if ((mtM->iED + i - (mtM->iMatchingIndex - 1)) == b) {
            for (int w = mtM->btnNode->iMin; w <= mtM->btnNode->iMax; w++) {
               if (res.find(w) == res.end()) {
                  last_indeserted_id = w;
                  res.insert(make_pair(w, b));
               }
               if (res.size() >= k) { return true; }
            }
         }
         int iED;
         for (int d = mtM->btnNode->iDepth + 1;
              d <= (mtM->btnNode->iDepth + 1 + b - mtM->iED); d++) {

            auto lst = trie::Index[d][query[i] - 'a'];
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

 private:
   int* arrB;
};

class meta2d {
 public:
   meta m;
   int k;
   meta2d(string& query, int k) : m(query, k) {
      cerr << "HERE\n";
      this->k = k;
      nra();
      getstrings();
   }
   set<string> results;
   void getstrings() {
      // results.clear();
      // for (auto& x : m.res) results.insert(trie::Dictionary[x.first]);
   }

 private:
   void nra() {

      int left = k;
      auto lst2 = trie::root->lstSortedStringNodes;

      // NRA
      score::ed = 0;
      score::sv = 0;
      map<size_t, score> scores;
      vector<pair<score, size_t>> l;
      set<size_t> seen;

      for (auto& x : m.res) {
         score s(x.second, -1);
         scores[x.first] = s;
         l.push_back({s, x.first});
      }
      // return;
      for (int i = 0; i < k; i++) {
         StringNode* item = lst2[i];
         if (scores.find(item->lStringID) == scores.end()) {
            scores[item->lStringID] = score(-1, item->dStaticValue);
         } else
            scores[item->lStringID].set_sv(item->dStaticValue);

         auto ss = scores[item->lStringID];
         l.push_back({ss, item->lStringID});
      }

      sort(l.begin(), l.end());
      cout << "sorting l  os size " << l.size() << endl;
      cout << "left" << left << endl;
      int i = 0;
      for (i = 0; i < l.size(); i++) {
         if (l[i].first.flag == 0) continue;
         if (l[i].first.complete() == false) break;
         left--;
         l[i].first.flag = 0; // delete it
         seen.insert(l[i].second);
         results.insert(trie::Dictionary[l[i].second]);
      }
      if (left <= 0) return;

      size_t j = k;
      for (;;) {
         cout << "left " << left << endl;
         // NRA loop
         auto t = m.getnext();
         size_t indx = t.first;
         cout << indx << "\n";
         if (indx == -1) break;
         int e_ = t.second;
         // add
         if (scores.find(indx) == scores.end()) {
            scores[indx] = score(e_, -1);
         } else {
            scores[indx].set_ed(e_);
         }

         auto ss = scores[indx];
         l.push_back({ss, indx});

         // add from list
         size_t indx2 = lst2[j]->lStringID;
         if (scores.find(indx2) == scores.end()) {
            scores[indx2] = score(-1, lst2[j]->dStaticValue);
         } else {
            scores[indx2].set_sv(lst2[j]->dStaticValue);
         }

         auto ss1 = scores[indx2];
         l.push_back({ss1, indx2});

         sort(l.begin(), l.end());

         int i = 0;
         for (i = 0; i < l.size(); i++) {
            if (l[i].first.flag == 0) continue;
            if (l[i].first.complete() == false) break;
            left--;
            l[i].first.flag = 0; // delete it
            seen.insert(l[i].second);
            results.insert(trie::Dictionary[l[i].second]);
            if (left <= 0) return;
         }

         vector<pair<score, size_t>> l2;
         for (int i = 0; i < l.size(); i++) {
            if (l[i].first.flag == 0) continue;
            l2.push_back(l[i]);
         }
         l = l2;

         j++;
         if (j == lst2.size()) break;
         score::ed = m.bound();
         score::sv = lst2[j - 1]->dStaticValue;
         double stopping = score::sv + score::ed * D_TAU_WEIGHT;
         if (l[0].first.getscore() > stopping || left == 0) break;
      }
      cerr << "DONE";
   }
   /*
         vector<pair<long, double>> r;
         for (pair<BasicTrieNode*, MatchingTriple*> element : mapP) {
            MatchingTriple* mtCurrent = element.second;
            double v = mtCurrent->dTopkOnlineValue =
                (mtCurrent->iED + mtCurrent->iNextQueryIndex -
                 mtCurrent->iMatchingIndex) *
                D_TAU_WEIGHT;
            BasicTrieNode* n = mtCurrent->btnNode;

            for (auto i = n->iMin; i < n->iMax; i++) {
               r.push_back(make_pair(i, lst[i]->dStaticValue + v));
            }
         }
         auto it = r.begin();
         for (int i = 0; i < k; i++) {
            results.insert(trie::Dictionary[it->first]);
            it++;
         }*/
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
#ifdef __1DIM__
         cerr << "1 dim\n*********************************************";
         meta m(q, k);
#else
         cerr << "2 dim\n*********************************************";

         meta2d m(q, k);
#endif
         escape(&m.results);
#ifdef __TEST__
         for (auto x : m.results) cout << "\t\t*" << x << endl;
         cout << endl;
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
