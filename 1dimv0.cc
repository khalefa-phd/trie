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
   outfile.open(file_csv + std::to_string(iCount) + "_1dim.csv",
                std::ofstream::out | std::ofstream::app);
   outfile << "****************************************************************"
              "************************** "
           << endl;
   vector<int> Ks{1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 10240, 20480};

   for (string& r : randoms) {
      query = r.substr(0, iCount);
      for (auto k : Ks) {
         vector<pair<string, string>> results;
         cout << query << "\t" << k << endl;

         META::run("meta0", results, query, k);

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
