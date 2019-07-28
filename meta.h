set<string> setMetaResults;
bool SecondDeducing(string strPrefixQeury,
                    map<BasicTrieNode*, MatchingTriple*>& mapP, int i, int b,
                    int k) {
   MatchingTriple* mtTemp;
   map<BasicTrieNode*, int> mapH;
   for (pair<BasicTrieNode*, MatchingTriple*> element : mapP) {
      MatchingTriple* mtM = element.second;
      if ((mtM->iED + i - (mtM->iMatchingIndex - 1)) == b) {
         for (int w = mtM->btnNode->iMin; w <= mtM->btnNode->iMax; w++) {
            if (setMetaResults.find(trie::Dictionary[w]) ==
                setMetaResults.end())
               setMetaResults.insert(trie::Dictionary[w]);
            if (setMetaResults.size() >= k) { return true; }
         }
      }
      int iED;
      for (int d = mtM->btnNode->iDepth + 1;
           d <= (mtM->btnNode->iDepth + 1 + b - mtM->iED); d++) {
         if (trie::Index[d][strPrefixQeury[i] - 'a'].size() == 0) continue;
         for (BasicTrieNode* btnNode :
              trie::Index[d][strPrefixQeury[i] - 'a']) {
            if ((btnNode->iID < mtM->btnNode->iMinNodeID) ||
                (btnNode->iID > mtM->btnNode->iMaxNodeID))
               continue;
            if ((i - 1 - mtM->iMatchingIndex) >
                (btnNode->iDepth - 1 - mtM->btnNode->iDepth))
               iED = mtM->iED + (i - 1 - mtM->iMatchingIndex);
            else
               iED = mtM->iED + (btnNode->iDepth - 1 - mtM->btnNode->iDepth);
            if (iED == b) {
               if (mapH.find(btnNode) != mapH.end()) {

                  if (mapH[btnNode] > (iED)) mapH[btnNode] = iED;
               } else {
                  mapH[btnNode] = iED;
               }
            }
         }
      }
   }
   for (pair<BasicTrieNode*, int> entry : mapH) {
      mtTemp = new MatchingTriple(i + 1, entry.first, entry.second, false);
      if (mapP.find(entry.first) == mapP.end())
         mapP[entry.first] = mtTemp;
      else if ((mapP[entry.first]->iED + i -
                mapP[entry.first]->iMatchingIndex) > entry.second)
         mapP[entry.first] = mtTemp;
   }
   return false;
}

void MatchingBasedMethodForTopK(string strPrefixQeury, int k) {
   setMetaResults.clear();
   int* arrB = new int[strPrefixQeury.length() + 1];
   arrB[0] = 0;
   map<BasicTrieNode*, MatchingTriple*> mapP;
   map<BasicTrieNode*, int> mapH;
   MatchingTriple* mtTemp = new MatchingTriple(0, trie::root, 0, false);
   mapP[trie::root] = mtTemp;
   for (int i = 0; i < strPrefixQeury.length(); i++) {
      ///////////////First Deducing/////////////////
      mapH.clear();
      int iED;
      for (pair<BasicTrieNode*, MatchingTriple*> element : mapP) {
         MatchingTriple* mtM = element.second;
         mtM->iNextQueryIndex = i;
         for (int d = mtM->btnNode->iDepth + 1;
              d <= (mtM->btnNode->iDepth + 1 + arrB[i]); d++) {
            if (trie::Index[d][strPrefixQeury[i] - 'a'].size() == 0) continue;
            for (BasicTrieNode* btnNode :
                 trie::Index[d][strPrefixQeury[i] - 'a']) {
               if ((btnNode->iID < mtM->btnNode->iMinNodeID) ||
                   (btnNode->iID > mtM->btnNode->iMaxNodeID))
                  continue;
               if ((i - 1 - mtM->iMatchingIndex) >
                   (btnNode->iDepth - 1 - mtM->btnNode->iDepth))
                  iED = mtM->iED + (i - 1 - mtM->iMatchingIndex);
               else
                  iED = mtM->iED + (btnNode->iDepth - 1 - mtM->btnNode->iDepth);
               if (mapH.find(btnNode) != mapH.end()) {

                  if (mapH[btnNode] > (iED)) mapH[btnNode] = iED;
               } else {
                  mapH[btnNode] = iED;
               }
            }
         }
      }
      for (pair<BasicTrieNode*, int> entry : mapH) {
         mtTemp = new MatchingTriple(i + 1, entry.first, entry.second, false);
         if (mapP.find(entry.first) == mapP.end())
            mapP[entry.first] = mtTemp;
         else if ((mapP[entry.first]->iED + i -
                   mapP[entry.first]->iMatchingIndex) > entry.second)
            mapP[entry.first] = mtTemp;
      }
      for (pair<BasicTrieNode*, MatchingTriple*> element : mapP) {
         MatchingTriple* mtM = element.second;
         if ((mtM->iED + i - (mtM->iMatchingIndex - 1)) < arrB[i]) {
            for (int w = mtM->btnNode->iMin; w <= mtM->btnNode->iMax; w++) {
               if (setMetaResults.find(trie::Dictionary[w]) ==
                   setMetaResults.end())
                  setMetaResults.insert(trie::Dictionary[w]);
               if (setMetaResults.size() >= k) { break; }
            }
         }
      }
      if (SecondDeducing(strPrefixQeury, mapP, i, arrB[i], k))
         arrB[i + 1] = arrB[i];
      else if (SecondDeducing(strPrefixQeury, mapP, i, arrB[i] + 1, k))
         arrB[i + 1] = arrB[i] + 1;
   }
   // clear memory
   delete[] arrB;
   for (pair<BasicTrieNode*, MatchingTriple*> element : mapP) {
      if (element.second != nullptr) delete element.second;
   }
   return;
}
