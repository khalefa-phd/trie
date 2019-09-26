class meta_threshold {

public:
	set<pair<string, int> > results() {
		set<pair<string, int> > r;
		for (auto &x : res)
			r.insert({ trie::Dictionary[x.first], x.second });
		return r;
	}

	map<size_t, int> res;
	string query;
	map<size_t, int> buffer;
	int iThreshold;
    map<BasicTrieNode *, MatchingTriple *> mapP;
  map<BasicTrieNode *, int> mapH; 
 

	meta_threshold(string query, int iThreshold) {
		this->query = query;
		this->iThreshold=iThreshold;
		batch();
	}

	~meta_threshold() {
		for (pair<BasicTrieNode *, MatchingTriple *> element : mapP) {
			if (element.second != nullptr)
				delete element.second;
		}
	}


#ifdef __STAT__
	size_t cnt = 0;
	size_t max_mapp = 0;
	inline void update_stat(bool inc = true) {
		max_mapp = max(max_mapp, mapP.size());
		if (inc)
			cnt++;
	}
#else
	inline void update_stat(bool inc = true) {}
#endif

protected:
	
	void batch() {
#ifdef __DEBUG__
		cout << "Threshold META (" << iThreshold <<")\n";
#endif		


		MatchingTriple *mtTemp = new MatchingTriple(0, trie::root, 0, false);
		map<BasicTrieNode *, MatchingTriple *> mapPNew;
		mapP[trie::root] = mtTemp;
		for (int i = 0; i < query.length(); i++) {
			///////////////First Deducing/////////////////
			res.clear();
			mapH.clear();
			update_stat();
			int iED;
			for (pair<BasicTrieNode *, MatchingTriple *> element : mapP) {
				update_stat();
				MatchingTriple *mtM = element.second;
				mtM->iNextQueryIndex = i;
				for (int d = mtM->btnNode->iDepth + 1;
					d <= (mtM->btnNode->iDepth + 1 + iThreshold); d++) {
					update_stat();
					auto lst = trie::Index[d][query[i] - 'a'];
#ifdef LOWERBOUND
					vector<BasicTrieNode*>::iterator start =
						std::lower_bound(
							lst.begin(), lst.end(), mtM->btnNode->iMinNodeID,
							[](const BasicTrieNode* element, const long
								value) {
						return element->iID < value;
					});
#else
					auto start = lst.begin();
#endif
					
					for (; start != lst.end(); start++) {
						BasicTrieNode *btnNode = *start;
						update_stat();
						if (btnNode->iID < mtM->btnNode->iMinNodeID)
							continue;
						if (btnNode->iID > mtM->btnNode->iMaxNodeID)
							break;

						if ((i - 1 - mtM->iMatchingIndex) >
							(btnNode->iDepth - 1 - mtM->btnNode->iDepth))
							iED = mtM->iED + (i - 1 - mtM->iMatchingIndex);
						else
							iED = mtM->iED + (btnNode->iDepth - 1 - mtM->btnNode->iDepth);
						if(iED <=iThreshold){
						if (mapH.find(btnNode) != mapH.end()) {
							if (mapH[btnNode] > (iED))
								mapH[btnNode] = iED;
						}
						else {
							mapH[btnNode] = iED;
						}
					}
					}
				}
			}
			mapPNew.clear();
			for (pair<BasicTrieNode *, int> entry : mapH) {
				update_stat();
				mtTemp = new MatchingTriple(i + 1, entry.first, entry.second, false);
				mapPNew[entry.first] = mtTemp;
			}
			for (pair<BasicTrieNode *, MatchingTriple *> element : mapP) {
				update_stat();
				MatchingTriple *mtM = element.second;
				if ((mtM->iED + i - (mtM->iMatchingIndex - 1)) < iThreshold)
					mapPNew[element.first] = mtTemp;
			}
			mapP.clear();
			mapP = mapPNew;
		}
		for (pair<BasicTrieNode *, MatchingTriple *> element : mapP) {
			update_stat();
			int i=query.length()-1;
			MatchingTriple *mtM = element.second;
			for (int w = mtM->btnNode->iMin; w <= mtM->btnNode->iMax; w++) {
				if (res.find(w) == res.end())
					res.insert(
						make_pair(w, mtM->iED + i - (mtM->iMatchingIndex - 1)
							/*	element.second->dTopkOnlineValue*/
						));
			}
		}
	}
};

