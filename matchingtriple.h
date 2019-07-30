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
