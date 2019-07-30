#include "trie.h"
#include "common.h"

struct BasicTrieNode* trie::root;
vector<BasicTrieNode*> trie::Index[100][ALPHABET_SIZE];
std::map<long, std::string> trie::Dictionary;

bool compareStringNode(StringNode* s1, StringNode* s2) {
   return (s1->dStaticValue < s2->dStaticValue);
}

void sortStringNodeLists(BasicTrieNode* btn) {
   sort(btn->lstSortedStringNodes.begin(), btn->lstSortedStringNodes.end(),
        compareStringNode);
   for (BasicTrieNode* btnqNext : btn->children) {
      if (btnqNext == NULL) continue;
      sortStringNodeLists(btnqNext);
   }
}

int BasicTrieNode::cnt() const { return iMax - iMin; }

void trie::initalize(const string& strFileName) {
   string line, strString;
   int iCommaIndex, iFrequency;
   ifstream myfile(strFileName);
   int iNodeCounter = 1;
   long lStringNumber = 1;
   double dStringTopkStaticValue;
   root = new BasicTrieNode(NULL, iNodeCounter++, '\0', 0);
   root->iMin = root->iMax = 1;
   root->dTopkMinStaticValue = D_TOP_K_MAX_VALUE;
   root->iMinNodeID = 1;
   while (getline(myfile, line)) {
      iCommaIndex = line.find((','));
      strString = line.substr(0, iCommaIndex);
      iFrequency = stoi(line.substr(iCommaIndex + 1, line.length() - 1));
      Dictionary[lStringNumber] = strString;
      dStringTopkStaticValue = 0;
      dStringTopkStaticValue +=
          ((1 - (1.0 / strString.length())) * D_LENGTH_WEIGHT);
      dStringTopkStaticValue += (1 / iFrequency * D_FREQUENCY_WEIGHT);
      //////////////////////Inserting in Trie/////////////////////
      StringNode* snString = new StringNode;
      snString->lStringID = lStringNumber;
      snString->dStaticValue = dStringTopkStaticValue;
      root->lstSortedStringNodes.push_back(snString);
      root->iMax = lStringNumber;
      if (root->dTopkMinStaticValue > dStringTopkStaticValue)
         root->dTopkMinStaticValue = dStringTopkStaticValue;
      struct BasicTrieNode* pbtnParent = root;

#ifdef __TEST__
      cout << "length(" << strString << ")=" << strString.length() << "\n";
#endif

      for (int i = 0; i < strString.length(); i++) {
         int index = strString[i] - 'a';
         if (!pbtnParent->children[index]) {
            BasicTrieNode* n = new BasicTrieNode(pbtnParent, iNodeCounter++,
                                                 strString[i], i + 1);
            pbtnParent->children[index] = n;
            n->iMinNodeID = iNodeCounter - 1;
            n->iMin = n->iMax = lStringNumber;
            n->dTopkMinStaticValue = dStringTopkStaticValue;
            Index[i + 1][index].push_back(n);
         } else {
            pbtnParent->children[index]->iMax = lStringNumber;
            if (pbtnParent->children[index]->dTopkMinStaticValue >
                dStringTopkStaticValue)
               pbtnParent->children[index]->dTopkMinStaticValue =
                   dStringTopkStaticValue;
         }
         pbtnParent = pbtnParent->children[index];
         pbtnParent->lstSortedStringNodes.push_back(snString);
      }

      pbtnParent->isEndOfWord = true;
      pbtnParent = pbtnParent->btnParent;
      while (pbtnParent != root) {
         pbtnParent->iMaxNodeID = iNodeCounter - 1;
         pbtnParent = pbtnParent->btnParent;
      }
      root->iMaxNodeID = iNodeCounter - 1;
      lStringNumber++;
   }

   myfile.close();
   ///////////////////////Sort string nodes lists/////////
   sortStringNodeLists(root);
   //   return 0;
}
void trie::print_stat(ofstream& out) {
   out << root->iMaxNodeID << "\n";
   for (int i = 1; i < 100; i++) {
      bool cont = false;
      out << i;
      for (int j = 0; j < ALPHABET_SIZE; j++) {
         if (Index[i][j].size() > 0) cont = true;
         out << "," << Index[i][j].size();
      }
      out << "\n";
      if (!cont) break;
   }
}
