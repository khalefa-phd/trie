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

ostream &operator<<(ostream &out, const record &s) {
  out << "{";
  out << s.id << ":" << s.value << "  " << s.eof << "}";
  return out;
}

class buffered_meta {

  vector<pair<size_t, double> > buffer;
  meta m;
  string query;
  int k;
  float len;
  int indx;

public:

  buffered_meta(string &query, int k) : m(query, k) {
    this->indx = 0;
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
#ifdef __DEBUG3__
    cerr << "buffered meta next" << indx << "\t" << buffer.size() << "\n";
#endif
    if (indx == buffer.size()) { // buffer.empty()) {
      auto t = m.next();
      buffer.push_back({ t.first, t.second / len });
    }
    auto t = buffer[indx++];
    if (t.first == -1)
      return record(); // return an eof record
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
      return (v[0] + 1) / 2;
    else if (flag == 2)
      return (1 + v[1]) / 2;
    return 1;
  }

  double best() const {
    if (flag == 3)
      return (v[0] + v[1]) / 2;
    else if (flag == 1)
      return (v[0] + high[1]) / 2;
    else if (flag == 2)
      return (high[0] + v[1]) / 2;
    return (high[0] + high[1]) / 2;
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

  static score init(double x, double y) {
    score s;
    s.v[0] = x;
    s.v[1] = y;
    s.flag = 3;
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
#if 0
  vector<StringNode *> v;
  stringiterator(vector<StringNode *> &vv) { v = vv; }
#else
stringiterator(){}
#endif

  record next() {

#ifdef __DEBUG3__
    cerr << "string iterator" << index << "\t"
#if 1
         << trie::root->lstSortedStringNodes.size()
#else
         << v.size()
#endif
         << "\n";
#endif
#if 0
    if (index == v.size())
#else
if (index == trie::root->lstSortedStringNodes.size())
#endif
      return record();
#if 0
StringNode *c =v[index];
#else
    StringNode *c = trie::root->lstSortedStringNodes[index];
#endif

#ifdef __DEBUG3__
    cerr << "\t" << c->lStringID << "\t" << c->dStaticValue << "\n";
#endif
    index++;
    return record(c->lStringID, c->dStaticValue);
  }
};

class meta2 {
  buffered_meta m;
  stringiterator lst;

public:
  meta2(string &query, int k)
      : m(query, k), lst() { // trie::root->lstSortedStringNodes) {

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
    double threshold = 0;
    double worst_score_in_topk = 1;
    score::high[0] = score::high[1] = 0; // the best possible value

     while (threshold< worst_score_in_topk) {
      record r = getnext(i);
#ifdef __DEBUG2__
      cerr << i << " \t " << r << "\n";
#endif
      if (r.eof)break;
      score::high[i] = r.value;

      // compute score
      if (w.find(r.id) == w.end()) {
        w[r.id] = score();
      }

      w[r.id].set(i, r.value);
#ifdef __DEBUG2__
	cerr <<"score" << w[r.id] << "\n";
#endif

    if (w[r.id].best() < worst_score_in_topk) {
        if (topkset.find(r.id) == topkset.end()) {
          topk.push_back(r.id);
          topkset.insert(r.id);
        }
      }

      if (topk.size() >= k) {
        sort(topk.begin(), topk.end(),
             [&](const size_t &x, const size_t &y) { return w[x] < w[y]; });
#ifdef __DEBUG3__
    cerr << "topk";
    for (auto x : topk)
      cerr << "\t" << x << " " << w[x] <<"\n";
#endif
        worst_score_in_topk = w[topk[k - 1]].worst();
      }
      threshold = score().best();
      i = i + 1;
      i = i % 2;
#ifdef __DEBUG3__
      cerr << "threshold " << threshold << "\n";
#endif
    }
#ifdef __DEBUG2__
    cerr << "+++++++++++++++++++++\n";
    for (auto a : w) {
      cerr << a.first << ":" << a.second << endl;
    }

    cerr << "Threshold " << threshold << "\n";
    cerr << "min_k " << worst_score_in_topk << "\n";
    cerr << "topk";
    for (auto x : topk)
      cerr << x << " " << w[x];
    cerr << endl;
#endif

    res.clear();
    for (auto x : topk) {
      res.insert(make_pair(x, w[x].best()));
    }
  }

  size_t cnt;
  size_t max_mapp;
};
