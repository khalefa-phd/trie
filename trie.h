#pragma once

#include "common.h"

// Node
// String node
struct StringNode {
   double dStaticValue;
   long lStringID;
};

// trie node
struct BasicTrieNode {
   struct BasicTrieNode* children[ALPHABET_SIZE];
   // isEndOfWord is true if the node represents
   // end of a word
   bool isEndOfWord;
   int iMinNodeID;
   int iMaxNodeID;
   int iMin;
   int iMax;

   double dTopkMinStaticValue;
   BasicTrieNode* btnParent;
   long iID;
   char btnCh;
   int iDepth;
   vector<StringNode*> lstSortedStringNodes;
   BasicTrieNode(BasicTrieNode* ptn, int iCounter, char ch, int depth)
       : btnParent{ptn}, iID{iCounter}, btnCh{ch}, iDepth{depth}, isEndOfWord{
                                                                      false} {
      for (int i = 0; i < ALPHABET_SIZE; i++) children[i] = NULL;
   }

   int cnt() const;
};

class trie {
 public:
   static std::map<long, std::string> Dictionary;
   static struct BasicTrieNode* root;
   static vector<BasicTrieNode*> Index[100][ALPHABET_SIZE];
   static void initalize(const string& strFileName);
   static void print_stat(ofstream& o);
};
