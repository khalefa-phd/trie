#include "meta1d.h"
#include "meta2d.h"
#include "metat.h"

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
    #ifdef __TOPK__  
      meta m(q, k);
    #endif 
    #ifdef __THRESHOLD__
      meta_threshold m(q,k);
    #endif  
    

#else
      meta2 m(q, k);
#endif
      auto r = m.results();

      escape(&r);
#ifdef __TEST__
      for (auto x : m.results())
        cerr << "\t\t*" << x.first << " " << x.second << endl;
      cerr << endl;

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