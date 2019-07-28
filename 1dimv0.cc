#include "common.h"
#include "trie.h"

struct MatchingTriple {
   int iMatchingIndex;
   BasicTrieNode* btnNode;
   int iED;
   bool bFinished;
   int iNextQueryIndex;
   double dTopkStaticValue;
   double dTopkOnlineValue;
   long lNextStringNodeIndex;

   MatchingTriple(int MatchingIndex, BasicTrieNode* node, int ed, bool finished)
       : bFinished{finished}, dTopkStaticValue{0},
         dTopkOnlineValue{D_TOP_K_MAX_VALUE}, iMatchingIndex{MatchingIndex},
         btnNode{node}, iED{ed}, lNextStringNodeIndex{0} {}
};

struct mtcompare0 {
   bool operator()(const MatchingTriple* mt, const MatchingTriple* o) const {
      if (mt->dTopkOnlineValue == o->dTopkOnlineValue) {
         if (mt->iNextQueryIndex == o->iNextQueryIndex) {
            if (mt->btnNode->cnt() > o->btnNode->cnt()) return true;
            return false;
         } else if (mt->iNextQueryIndex > o->iNextQueryIndex)
            return true;
         else
            return false;
      } else if (mt->dTopkOnlineValue < o->dTopkOnlineValue)
         return true;
      else
         return false;
   }
};

struct mtcompare1 {
   inline bool operator()(const MatchingTriple* mt,
                          const MatchingTriple* o) const {
      if (mt->iMatchingIndex > o->iMatchingIndex)
         return true;
      else
         return false;
   }
};
struct mtcompare2 {
   inline bool operator()(const MatchingTriple* mt,
                          const MatchingTriple* o) const {
      if (mt->iNextQueryIndex > o->iNextQueryIndex)
         return true;
      else
         return false;
   }
};

struct mtcompare3 {
   inline bool operator()(const MatchingTriple* mt,
                          const MatchingTriple* o) const {
      if (mt->dTopkOnlineValue < o->dTopkOnlineValue)
         return true;
      else
         return false;
   }
};

struct mtcompare4 {
   inline bool operator()(const MatchingTriple* mt,
                          const MatchingTriple* o) const {
      if (mt->iNextQueryIndex + o->dTopkOnlineValue >
          o->iNextQueryIndex + mt->dTopkOnlineValue)
         return true;
      else
         return false;
   }
};
struct mtcompare5 {
   inline bool operator()(const MatchingTriple* mt,
                          const MatchingTriple* o) const {
      if (mt->iNextQueryIndex > o->iNextQueryIndex)
         return true;
      else if (mt->iNextQueryIndex == o->iNextQueryIndex)
         return false;
   }
};

#include "depth.h"
#include "meta.h"

void readRandomFiles(string fileRandoms, vector<string>& randoms) {
   ifstream file;
   string strRecord;
   file.open(fileRandoms);
   while (getline(file, strRecord)) {
      if (strRecord == "") break;
      randoms.push_back(strRecord.substr(0, strRecord.length() - 1));
   }
   file.close();
}

int main(int argc, char** args) {
   cout << "1. Start" << endl;
   string fileRecords = args[1];
   string file_csv = args[2];
   string fileRandoms = args[3];
   int iCount = stoi(args[4]);

   vector<string> randoms;
   readRandomFiles(fileRandoms, randoms);
   trie::initalize(fileRecords);
   cout << "2. Tree index created" << endl;
   srand(time(NULL));

   string query;

   ofstream outfile;
   outfile.open(file_csv + std::to_string(iCount) + "_m1dim_free.csv",
                std::ofstream::out | std::ofstream::app);
   // outfile << ("K; Q Length ; (Meta) Duration; (Depth)Duration") << endl;
   vector<int> Ks{1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 10240, 20480};

   for (string& r : randoms) {
      query = r.substr(0, iCount);
      for (auto k : Ks) {
         vector<pair<string, string>> results;
         cout << query << "\t" << k << endl;
         auto start = std::chrono::high_resolution_clock::now();
         for (size_t i = 0; i < REP; i++) {
            MatchingBasedMethodForTopK(query, k);
            escape(&setMetaResults);
            setMetaResults.clear();
         }
         auto finish = std::chrono::high_resolution_clock::now();
         results.push_back(make_pair(
             "meta0",
             to_string(chrono::duration<double, nano>(finish - start).count() /
                       REP)));
         DEPTH<mtcompare0>::run("depth0", results, query, k);
         DEPTH<mtcompare1>::run("depth1", results, query, k);
         DEPTH<mtcompare3>::run("depth3", results, query, k);
         DEPTH<mtcompare4>::run("depth4", results, query, k);

         auto header =
             query + "," + to_string(k) + "," + to_string(query.length());
         for (auto x : results) {
            auto str = x.first + "," + x.second;
            outfile << __FILENAME__ << "," << gitversion << "," << header << ","
                    << str << endl;
         }
         outfile.flush();
      }
   }

   outfile.close();
   cout << ("3. Finished Successfully") << endl;
   cout << endl;
   return 0;
}
