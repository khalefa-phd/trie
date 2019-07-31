struct MatchingTriple {
   int iMatchingIndex;
   BasicTrieNode* btnNode;
   int iED;
   bool bFinished;
   int iNextQueryIndex;
   double dTopkStaticValue;
   double dTopkOnlineValue;
   long lNextStringNodeIndex;

#ifdef __1DIM__
   inline double cost() const { return dTopkOnlineValue; }
#endif
#ifdef __2DIM__
   inline double cost() const { return dTopkOnlineValue + dTopkStaticValue; }
#endif

   MatchingTriple(int MatchingIndex, BasicTrieNode* node, int ed, bool finished)
       : bFinished{finished}, dTopkStaticValue{0},
         dTopkOnlineValue{D_TOP_K_MAX_VALUE}, iMatchingIndex{MatchingIndex},
         btnNode{node}, iED{ed}, lNextStringNodeIndex{0} {}
};

struct mtcompare0 {
   bool operator()(const MatchingTriple* mt, const MatchingTriple* o) const {
      if (mt->cost() == o->cost()) {
         if (mt->iNextQueryIndex == o->iNextQueryIndex) {
            if (mt->btnNode->cnt() > o->btnNode->cnt()) return true;
            return false;
         } else if (mt->iNextQueryIndex > o->iNextQueryIndex)
            return true;
         else
            return false;
      } else if (mt->cost() < o->cost())
         return true;
      else
         return false;
   }
};
