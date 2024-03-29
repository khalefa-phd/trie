#include "common.h"
#include "trie.h"
// DO NOT DELETE
#include "matchingtriple.h"

#if defined(WINDOWS)
const char *gitversion = "000";
#endif

#include "depth.h"
#include "meta.h"

ostream &operator<<(ostream &out, const MatchingTriple &t) {
  out << "(" << *(t.btnNode) << "," << t.iED << "," << t.iMatchingIndex << ")";
  return out;
}

void readRandomFiles(string fileRandoms, vector<string> &randoms) {
  ifstream file;
  string strRecord;
  file.open(fileRandoms);
  while (getline(file, strRecord)) {
    if (strRecord == "")
      break;
    randoms.push_back(strRecord.substr(0, strRecord.length() - 1));
  }
  file.close();
}

int main(int argc, char **args) {

#ifdef __STAT__
  cout << "stat gathering mode\n";
#endif
#ifdef __EXPR__
  cout << "EXPR  mode\n";
#endif
#ifdef __TEST__
  cout << "Test  mode\n";
#endif

#ifdef __1DIM__
  cout << "1 dim is defined\n";
#endif

#ifdef __2DIM__
  cout << "2 dim is defined\n";
#endif

  cout << "1. Start" << endl;
#ifdef __TEST__
#ifdef WINDOWS
  string dir = "../../";
#else
  string dir = "./";
#endif
  string fileRecords = dir + "test";
  string file_csv = dir + "output";
  string fileRandoms = dir + "random";
  int iCount = 3;
#else
  string fileRecords = args[1];
  string file_csv = args[2];
  string fileRandoms = args[3];
  int iCount = stoi(args[4]);
#endif

  trie::initalize(fileRecords);

  cout << "2. Tree index created" << endl;

  vector<string> randoms;
  readRandomFiles(fileRandoms, randoms);
  auto start = 0;
  auto end = randoms.size();

  if (argc > 5) {
    start = stoi(args[5]);
    end = stoi(args[6]);
  }

#ifdef __STAT__
  ofstream triefile("trie.csv");
  trie::print_stat(triefile);
  triefile.close();
#endif
  ofstream outfile;
#ifdef __1DIM__
  outfile.open(file_csv + std::to_string(iCount) + "_1dim.csv",
               std::ofstream::out | std::ofstream::app);
#else
  outfile.open(file_csv + std::to_string(iCount) + "_2dim.csv",
               std::ofstream::out | std::ofstream::app);
#endif

  outfile << "****************************************************************"
             "************************** " << endl;

#ifndef __TEST__
  vector<int> Ks{ 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024 };
#else
  vector<int> Ks{ 4 };
#endif
  string old_query = "";
  for (size_t i = start; i < end; i++) {
    string r = randoms[i];
    string query = r.substr(0, iCount);
    if (query == old_query)
      continue;
    old_query = query;
    for (auto k : Ks) {
      vector<pair<string, string> > results;
      cout << query << "\t" << k << endl;
      if (query.length() == 0)
        continue;
      META::run("meta_nra0", results, query, k);

      DEPTH<mtcompare0>::run("depth0", results, query, k);
      DEPTH<mtcompare0>::irun("idepth0", results, query, k);

      auto header =
          query + "," + to_string(k) + "," + to_string(query.length());
      for (auto x : results) {
        auto str = x.first + "," + x.second;
        outfile << __FILENAME__ << "," << gitversion << ","
                << "," << EXPR << "," << header << "," << str << endl;
      }
      outfile.flush();
    }
  }

  outfile.close();
  cout << ("3. Finished Successfully") << endl;
  cout << endl;
#ifdef _WIN32
  char x;
  cin >> x;
#endif
  return 0;
}
