#define _DEBUG_HEAP_IMPL { }

#include <vector>
#include <queue>
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef vector<int> vi;

struct heap_item
{
	long long value;
	int seq_idx;
	heap_item(long long v_, int si_) : value(v_), seq_idx(si_) { } ;
	bool operator < (const heap_item &that) const {
		return this->value > that.value;
	}
};

class sequence
{
	vi coefs;
	int curr_n;
	long long curr_value;
public:
	sequence(istream &in) {
		coefs.resize(8);
		for(int i=7; i>=0; i--)
			in >> coefs[i];
		curr_n = 0;
		get_next_value();
	}
	long long get_next_value() {
		long long old_value = curr_value;
		curr_n++;
		curr_value = 0LL;
		for(int i=7; i>=0; i--)	{
			curr_value *= curr_n;
			curr_value += coefs[i];
		}
		return old_value;
	}
};

vector<sequence> seqs;
priority_queue<heap_item> wait_for_min;

int main(int argc, char* argv[])
{
//#ifdef _DEBUG
//	freopen("input.txt", "rt", stdin);
//	freopen("output.txt", "wt", stdout);
//#endif
	int k, N;
	cin >> k;
	seqs.clear();
	seqs.reserve(k);
	for(int i=0; i<k; i++) {
		seqs.push_back(sequence(cin));
		wait_for_min.push(heap_item(seqs[i].get_next_value(), i));
	}
	cin >> N;

	long long curr_min_value;
	for(int idx=0; idx<N; idx++) {
		heap_item curr_min_item = wait_for_min.top();
		curr_min_value = curr_min_item.value;
		wait_for_min.pop();
		wait_for_min.push(heap_item(seqs[curr_min_item.seq_idx].get_next_value(), curr_min_item.seq_idx));
//		if(idx % 1000 == 0) {
//			cerr << curr_min_value << "\t" << idx << endl;
//		}
	}

	cout << curr_min_value << endl;
	return 0;
}
