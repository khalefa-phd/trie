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

  pair<size_t, int> next() {
    static int cnt = 0;
    cnt++;
    int i = query.length() - 1;
    k++;
    map<size_t, int> r;
    if (SecondDeducing(i, arrB[i], r))
      ;
    else if (SecondDeducing(i, arrB[i] + 1, r))
      arrB[i]++;
    else
      return make_pair(-1, -1);

    return *r.begin();
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
        mtM->i
          QueryIndex = i;
        for (int d = mtM->btnNode->iDepth + 1;
             d <= (mtM->btnNode->iDepth + 1 + arrB[i]); d++) {
          update_stat();
          auto lst = trie::Index[d][query[i] - 'a'];

          /*	vector<BasicTrieNode*>::iterator start =
             std::lower_bound(
                          lst.begin(), lst.end(), mtM->btnNode->iMinNodeID,
                          [](const BasicTrieNode* element, const long
             value) {
                          return element->iID < value;
                  });
*/

          auto start = lst.begin();
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
                                   /*	element.second->dTopkOnlineValue*/
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
    cout << "SecondDeducing\n";
#endif
    for (pair<BasicTrieNode *, MatchingTriple *> element : mapP) {
#ifdef __DEBUG2__
      {
        MatchingTriple *mt = element.second;
        cout << "\t" << (*mt) << "\n";
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
        /*			vector<BasicTrieNode*>::iterator start =
           std::lower_bound(
                                        lst.begin(), lst.end(),
           mtM->btnNode->iMinNodeID,
                                        [](const BasicTrieNode* element,
           const
           long value) {
                                        return element->iID < value;
                                });
                                */
        auto start = lst.begin();
        for (; start != lst.end(); start++) {
          BasicTrieNode *btnNode = *start;
          update_stat();
          if (btnNode->iID < mtM->btnNode->iMinNodeID)
            continue;
          if (btnNode->iID > mtM->btnNode->iMaxNodeID)
            break;

          //					if (btnNode->iID >
          // mtM->btnNode->iMaxNodeID)
          // break;
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
          cout << "\t\t" << (*btnNode) << "---" << iED << "\n";
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

  map<BasicTrieNode *, MatchingTriple *> mapP;
  map<BasicTrieNode *, int> mapH;
};

struct record {
  size_t id;
  double value;
  bool eof;
  record(size_t i, double v) {
    id = i;
    value = v;
    eof = false;
  }
  bool operator<(const record &other) const { return value < other.value; }
  record() { eof = true; }
};

class buffered_meta {

  vector<pair<size_t, double> > buffer;
  meta m;
  string query;
  int k;
  float len;
  int indx;

public:
  buffered_meta(string &query, int k) : m(query, k) {
    this->query = query;
    this->k = k;
    this->len = (float)query.length();
    for (auto x : m.res) {
      buffer.push_back(make_pair(x.first, x.second / len));
    }
    sort(buffer.begin(), buffer.end(),
         [](const pair<size_t, double> &x,
            const pair<size_t, double> &y) { return x.second < y.second; });
  }
  record next() {
    if (indx == buffer.size()) { // buffer.empty()) {
      auto t = m.next();
      buffer.push_back({ t.first, t.second / len });
    }
    auto t = buffer[indx++];
    if(t.first==-1 && t.second==-1)
        return record();// return an eof record
    // buffer.erase(buffer.begin());
    return record(t.first, t.second);
  }
};

struct score {
  score() { flag = 0; }
  double v[2];
  int flag = 0;
  // 00
  // 10
  // 01
  double worst() const {
    if (flag == 3)
      return (v[0] + v[1]) / 2;
    else if (flag == 1)
      return (v[0]+1) / 2;
    else if (flag == 2)
      return (1+v[1]) / 2;
    return 1;
  }

  double best() const {
    if (flag == 3)
      return (v[0] + v[1]) / 2;
    else if (flag == 1)
      return (v[0] + high[1]) / 2;
    else if (flag == 2)
      return (high[0] + v[1]) / 2;
    return (high[0]+high[1])/2;
  }

  void set(int i, double v) {
    if (i == 0)
      flag |= 1;
    else
      flag |= 2;
    this->v[i] = v;
  }

  bool operator<(const score &x) const {
    if (worst() == x.worst()) {
      return best() < x.best();
    } else
      return worst() < x.worst();
  }

  static score init(double x, double y){
  
   score s;
    s.v[0]=x;
  s.v[1]=y;
  s.flag=3;
  return s;
}
  static double high[2];
};

ostream &operator<<(ostream &out, const score &s) {
  out << "{";
  out << s.best() << "-" << s.worst() << "}";
  return out;
}

double score::high[2];

struct stringiterator {
  size_t index = 0;
  vector<StringNode *> v;
  stringiterator(vector<StringNode *> &vv) { v = vv; }
  record next() {
    if(index==v.size()) return record();
    StringNode *c = v[index];
    
    index++;
    return record(c->lStringID, c->dStaticValue);
  }
};

class meta2 {
  buffered_meta m;
  stringiterator lst;

public:
  meta2(string &query, int k)
      : m(query, k), lst(trie::root->lstSortedStringNodes) {

    nra(k);
  }

  record getnext(int i) {
    if (i == 0)
      return m.next();
    else
      return lst.next();
  }

  set<pair<string, double> > results() {
    set<pair<string, double> > r;
    for (auto &x : res)
      r.insert({ trie::Dictionary[x.first], x.second });
    return r;
  }
  map<size_t, double> res;

  void nra(int k) {

    int i = 0; //
    map<size_t, score> w;
    set<size_t> topkset;
    vector<size_t> topk;
    double threshold=0;
    double worst_score_in_topk = 1;
    score::high[0] = score::high[1] = 0;//the best possible value
    while (threshold>worst_score_in_topk) {
      record r = getnext(i);
      if(r.eof) break;
      score::high[i] = r.value;

      // compute score
      if (w.find(r.id) == w.end()) {
        w[r.id] = score();
      }

      w[r.id].set(i, r.value);
      
      if(w[r.id].best() < worst_score_in_topk){
      if (topkset.find(r.id) == topkset.end()) {
        if(threshold>)
          topk.push_back(r.id);
          topkset.insert(r.id);
      } 
      }
      
      if (topk.size() >= k ) {
          sort(topk.begin(), topk.end(), [&](const size_t &x, const size_t &y) {
            return w[x] < w[y];
          });
      worst_score_in_topk=topk[k-1].worst();
      }

      threshold = score().best();
      i = i + 1;
      i = i % 2;
    }

#ifdef __DEBUG2__
      cout << "+++++++++++++++++++++\n";
      for (auto a : w) {
        cout << a.first << ":" << a.second << endl;
      }

      cout << "Threshold " << threshold << "\n";
      cout << "min_k " << worst_score_in_topk << "\n";
      cout << "topk";
      for (auto x : topk)
        cout << x << " "<<w[x];
      cout << endl;
#endif
      
        res.clear();
        for (auto x : topk) {
          res.insert(make_pair(x, w[x].best()));
        }
      
  }

  size_t cnt;
  size_t max_mapp;
};

class META {
public:
  static void run(string expr, vector<pair<string, string> > &results,
                  string &q, int k) {

#ifdef __STAT__
    size_t cnt;
    size_t max_mapp;
#endif

    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < REP; i++) {
#ifdef __1DIM__
      meta m(q, k);
#else
      meta2 m(q, k);
#endif
      auto r = m.results();

      escape(&r);
#ifdef __TEST__
      for (auto x : m.results())
        cout << "\t\t*" << x.first << " " << x.second << endl;
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
        expr, to_string(chrono::duration<double, nano>(finish - start).count() /
                        REP) +
                  stat));
  }
};
