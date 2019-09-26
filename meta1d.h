class meta {
public:
  set<pair<string, int> > results() {
    set<pair<string, int> > r;
    for (auto &x : res)
      r.insert({ trie::Dictionary[x.first], x.second });
    return r;
  }

  map<size_t, int> res;
  int k;
  string query;
 map<size_t, int> buffer;
 map<BasicTrieNode *, MatchingTriple *> mapP;
  map<BasicTrieNode *, int> mapH; 
  
#ifdef __STAT__
  size_t cnt = 0;
  size_t max_mapp = 0;
  inline void update_stat(bool inc = true) {
    max_mapp = max(max_mapp, mapP.size());
    if (inc)
      cnt++;
  }
#else
  inline void update_stat(bool inc = true) {}
#endif

  meta(string query, int k) {
    this->k = k;
    this->query = query;
    arrB = new int[query.length() + 1];
    batch();
  }

  ~meta() {
    for (pair<BasicTrieNode *, MatchingTriple *> element : mapP) {
      if (element.second != nullptr)
        delete element.second;
    }
    delete[] arrB;
  }

 

  bool fillbuffer() {
#ifdef __DEBUG3__
    cerr << "********* fill buffer ***********\n";
#endif
    int i = query.length() - 1;
    if (SecondDeducing(i, arrB[i], buffer))
      return true;
    else if (SecondDeducing(i, arrB[i] + 1, buffer)) {
      arrB[i]++;
      return true;
    } else
      return false;
  }

  pair<size_t, int> next() {
    static int cnt = 0;
    cnt++;
#ifdef __DEBUG3__
    cerr << "**** meta _next \n";
#endif

    k++;
    if (buffer.size() == 0) {
      if (!fillbuffer())
        return make_pair(-1, -1);
    }
    auto x = *buffer.begin();
    buffer.erase(buffer.begin());
#ifdef __DEBUG3__
    cerr << "X=" << x.first << "\t" << x.second << "\n";
#endif
    return x;
  }

  int bound() { return arrB[query.length() - 1]; }

protected:
  meta() {}

  int *arrB;
  void batch() {
    arrB[0] = 0;
    MatchingTriple *mtTemp = new MatchingTriple(0, trie::root, 0, false);
    mapP[trie::root] = mtTemp;
    for (int i = 0; i < query.length(); i++) {
      ///////////////First Deducing/////////////////
      res.clear();
      mapH.clear();
      update_stat();
      int iED;
      for (pair<BasicTrieNode *, MatchingTriple *> element : mapP) {
        update_stat();
        MatchingTriple *mtM = element.second;
        mtM->iNextQueryIndex = i;
        for (int d = mtM->btnNode->iDepth + 1;
             d <= (mtM->btnNode->iDepth + 1 + arrB[i]); d++) {
          update_stat();
          auto lst = trie::Index[d][query[i] - 'a'];
#ifdef LOWERBOUND
            vector<BasicTrieNode*>::iterator start =
             std::lower_bound(
                          lst.begin(), lst.end(), mtM->btnNode->iMinNodeID,
                          [](const BasicTrieNode* element, const long
             value) {
                          return element->iID < value;
                  });
#else
          auto start = lst.begin();
#endif
          for (; start != lst.end(); start++) {
            BasicTrieNode *btnNode = *start;
            update_stat();
            if (btnNode->iID < mtM->btnNode->iMinNodeID)
              continue;
            if (btnNode->iID > mtM->btnNode->iMaxNodeID)
              break;

            if ((i - 1 - mtM->iMatchingIndex) >
                (btnNode->iDepth - 1 - mtM->btnNode->iDepth))
              iED = mtM->iED + (i - 1 - mtM->iMatchingIndex);
            else
              iED = mtM->iED + (btnNode->iDepth - 1 - mtM->btnNode->iDepth);
            if (mapH.find(btnNode) != mapH.end()) {
              if (mapH[btnNode] > (iED))
                mapH[btnNode] = iED;
            } else {
              mapH[btnNode] = iED;
            }
          }
        }
      }

      for (pair<BasicTrieNode *, int> entry : mapH) {
        update_stat();
        mtTemp = new MatchingTriple(i + 1, entry.first, entry.second, false);
        if (mapP.find(entry.first) == mapP.end())
          mapP[entry.first] = mtTemp;
        else if ((mapP[entry.first]->iED + i -
                  mapP[entry.first]->iMatchingIndex) > entry.second)
          mapP[entry.first] = mtTemp;
      }

      for (pair<BasicTrieNode *, MatchingTriple *> element : mapP) {
        update_stat();
        MatchingTriple *mtM = element.second;
        if ((mtM->iED + i - (mtM->iMatchingIndex - 1)) < arrB[i]) {
          for (int w = mtM->btnNode->iMin; w <= mtM->btnNode->iMax; w++) {
            if (res.find(w) == res.end())
              res.insert(
                  make_pair(w, mtM->iED + i - (mtM->iMatchingIndex - 1)
                                   /* element.second->dTopkOnlineValue*/
                            ));
            if (res.size() >= k) {
              break;
            }
          }
        }
      }

      map<size_t, int> r;
      if (SecondDeducing(i, arrB[i], r))
        arrB[i + 1] = arrB[i];
      else if (SecondDeducing(i, arrB[i] + 1, r))
        arrB[i + 1] = arrB[i] + 1;
    }
  }

  bool SecondDeducing(int i, int b, map<size_t, int> &r) {
    MatchingTriple *mtTemp;
    map<BasicTrieNode *, int> mapH;
#ifdef __DEBUG2__
    cerr << "SecondDeducing\n";
#endif
    for (pair<BasicTrieNode *, MatchingTriple *> element : mapP) {
#ifdef __DEBUG2__
      {
        MatchingTriple *mt = element.second;
        cerr << "\t" << (*mt) << "\n";
      }
#endif
      update_stat();
      MatchingTriple *mtM = element.second;
      if ((mtM->iED + i - (mtM->iMatchingIndex - 1)) == b) {
        for (int w = mtM->btnNode->iMin; w <= mtM->btnNode->iMax; w++) {
          if (res.find(w) == res.end()) {
            res.insert(make_pair(w, mtM->iED + i - (mtM->iMatchingIndex - 1)));
            r.insert(make_pair(w, mtM->iED + i - (mtM->iMatchingIndex - 1)));
          }
          if (res.size() >= k) {
            return true;
          }
        }
      }

      int iED;
      for (int d = mtM->btnNode->iDepth + 1;
           d <= (mtM->btnNode->iDepth + 1 + b - mtM->iED); d++) {

        auto lst = trie::Index[d][query[i] - 'a'];
#ifdef LOWERBOUND
        vector<BasicTrieNode*>::iterator start =
           std::lower_bound(
                                        lst.begin(), lst.end(),
           mtM->btnNode->iMinNodeID,
                                        [](const BasicTrieNode* element,
           const
           long value) {
                                        return element->iID < value;
                                });
#else
        auto start = lst.begin();
#endif

        for (; start != lst.end(); start++) {
          BasicTrieNode *btnNode = *start;
          update_stat();
          if (btnNode->iID < mtM->btnNode->iMinNodeID)
            continue;
          if (btnNode->iID > mtM->btnNode->iMaxNodeID)
            break;

          if ((i - 1 - mtM->iMatchingIndex) >
              (btnNode->iDepth - 1 - mtM->btnNode->iDepth))
            iED = mtM->iED + (i - 1 - mtM->iMatchingIndex);
          else
            iED = mtM->iED + (btnNode->iDepth - 1 - mtM->btnNode->iDepth);
          if (iED == b) {
            if (mapH.find(btnNode) != mapH.end()) {
              if (mapH[btnNode] > (iED))
                mapH[btnNode] = iED;
            } else {
              mapH[btnNode] = iED;
            }
          }
#ifdef __DEBUG2__
          cerr << "\t\t" << (*btnNode) << "---" << iED << "\n";
#endif
        }
      }
    }
    for (pair<BasicTrieNode *, int> entry : mapH) {
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

 
};