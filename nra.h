#include <iostream>
#include <vector>
#include<map>
#include<set>
#include <algorithm>
using namespace std;

struct record {
	size_t id;
	double value;

	record(int i, double v) {
		id = i;
		value = v;
	}
	bool operator <(const record &other) const {
		return value < other.value;
	}
};

struct score {
	score() { flag = 0; }
	double v[2];
	int flag = 0;
	//00
	//10 
	//01
	double best() const {
		if (flag == 3) return (v[0] + v[1]) / 2;
		else if (flag == 1) return v[0] / 2;
		else if (flag == 2) return v[1] / 2;
		return 1;
	}

	double worst() const {
		if (flag == 3) return (v[0] + v[1]) / 2;
		else if (flag == 1) return (v[0] + high[1]) / 2;
		else if (flag == 2) return (high[0] + v[1]) / 2;
		return 0;
	}

	void set(int i, double v) {
		if (i == 0)flag |= 1;
		else flag |= 2;
		this->v[i] = v;
	}

	bool operator <(const score &x) const {
		if (worst() == x.worst()) {
			return best() > x.best();
		}
		else
			return worst() < x.worst();
	}
	static double high[2];
};

ostream& operator<<(ostream& out, const score &s) {
	out << "{" << s.worst() << "-" << s.best() << "}";
	return out;
}

double score::high[2];

void nra(vector<record> &a, vector<record> &b, int k) {

	int indx[2];
	indx[0] = indx[1] = 0;
	int i = 0;

	map<size_t, score> w;
	vector<size_t> topk;
	set<size_t> topkset;
	score::high[0] = score::high[1] = 0;

	double threshold;
	double min_k = 0;
	while (true) {

		auto v = (i == 0) ? a : b;
		if (indx[i] == v.size()) {
			cout << "here" << endl;
			break;
		}
		record r = v[indx[i]];
		score::high[i] = r.value;
		//compute score
		if (w.find(r.id) == w.end()) { w[r.id] = score(); }
		w[r.id].set(i, r.value);
		double worstscore = w[r.id].worst();
		double bestscore = w[r.id].best();

		if (topk.size() < k) {
			if (topkset.find(r.id) == topkset.end()) {
				topk.push_back(r.id); topkset.insert(r.id);

				sort(topk.begin(), topk.end(), [&](const size_t &x, const size_t &y) {
					return w[x].worst() < w[y].worst();
				});
				min_k = w[topk[0]].worst();
			}
		}
		else
			if (topk.size() >= k && worstscore > min_k) {
				if (topkset.find(r.id) == topkset.end()) {
					topk.push_back(r.id); topkset.insert(r.id);

				
					sort(topk.begin(), topk.end(), [&](const size_t &x, const size_t &y) {
						return w[x].worst() < w[y].worst();
					});
					topk.erase(topk.begin());
					min_k = w[topk[0]].worst();
				}
			}

		auto me = *max_element(w.begin(), w.end(), [](const pair<size_t, score> &x, const pair<size_t, score> & y) {return x.second.best()<y.second.best(); });
		threshold = me.second.best();

		cout << "+++++++++++++++++++++\n";
		for (auto a : w) {
			cout << a.first << ":" << a.second << endl;
		}

		cout << "Threshold " << threshold << "\n";
		cout << "min_k " << min_k << "\n";
		cout << "topk";
		for (auto x : topk)
			cout << x << " ";
		cout << endl;
		if (threshold >= min_k && topk.size() >= k) {


			cout << "results topk";
			for (auto x : topk) {
				cout << x << "" << w[x] << endl;
			}
			break;
		}

		indx[i]++;

		i = i + 1;
		i = i % 2;
	}

}
#if 0
int main() {
	vector<record> a;
	vector<record> b;
	//d78 0.9  d23 0.8 d10 0.8
	//d64 0.8 d23 0.6 d10 0.6
	a.push_back(record(64, 0.3));
	
	a.push_back(record(23, 0.8));
	a.push_back(record(10, 0.8));
	a.push_back(record(78, 0.9));


	
	
	b.push_back(record(78, 0.1));
	
	b.push_back(record(23, 0.6));
	b.push_back(record(10, 0.6));
	b.push_back(record(64, 0.8));

	nra(a, b, 2);

	sort(a.begin(), a.end());
	cout << a[0].id;
	
	char c;
	cin >> c;
	/*for (auto x : r) {
	cout << x.first << " " << x.second << "\n";
	}*/
}
#endif 