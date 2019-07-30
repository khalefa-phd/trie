#include "common.h"
#include "trie.h"
// DO NOT DELETE
#include "matchingtriple.h"

#ifndef __linux__
const char* gitversion = "000";
#endif

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

#ifdef __STAT__
   cout << "stat gathering mode\n";
#endif
   cout << "1. Start" << endl;
#ifdef __TEST__
#ifdef __linux__
   string dir = "./";
#else
   string dir = "../../";
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
   outfile.open(file_csv + std::to_string(iCount) + "_1dim.csv",
                std::ofstream::out | std::ofstream::app);

   outfile << "****************************************************************"
              "************************** "
           << endl;

#ifndef __TEST__
   vector<int> Ks{1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 10240, 20480};
#else
   vector<int> Ks{1, 2, 4};
#endif

   for (size_t i = start; i < end; i++) {
      string r = randoms[i];
      string query = r.substr(0, iCount);
      for (auto k : Ks) {
         vector<pair<string, string>> results;
         cout << query << "\t" << k << endl;

         META::run("meta0", results, query, k);

         DEPTH<mtcompare0>::run("depth0", results, query, k);

#if 0
         DEPTH<mtcompare1>::run("depth1", results, query, k);
         DEPTH<mtcompare3>::run("depth3", results, query, k);
         DEPTH<mtcompare4>::run("depth4", results, query, k);
#endif
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
