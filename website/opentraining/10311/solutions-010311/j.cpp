#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>

#pragma warning ( disable : 4996 )

using namespace std;
typedef unsigned long long uLL;
typedef pair<uLL,uLL> pLL;

const uLL _1e17_uLL = 100uLL*1000uLL*1000uLL*1000uLL*1000uLL*1000uLL;
const double _1e17_plus_EPS = 1e17*(1+1e-6);
const double log_1e17_plus_EPS = log(_1e17_plus_EPS);
vector<int> a;

uLL pow_(uLL a, int n, bool do_try_in_double = false) // guaranteed 2\<n\<63
{
	if(do_try_in_double)
		if(n * log((double)a) > log_1e17_plus_EPS)
			return _1e17_uLL + 1000;
	if(n < 15) {
		uLL res = 1uLL;
		for(int i=0; i<n; i++)
			res *= a;
		return res;
	} else {
		uLL res = pow_(a, n/2, false); // try_in_double already done
		res *= res;
		if(n%2!=0)
			res *= a;
		return res;
	}
}

int gcd(int a, int b)
{
	while(a>0 && b>0)
		if(a>b)
			a%=b;
		else
			b%=a;
	return a+b;
}

int lcm(int a, int b)
{
	return (a / gcd(a,b)) * b;
}

int idx_by_value_1(uLL value, int ex_) 
// guaranteed: 2\<ex_\<50;
// guaranteed: result fits int32
{
	int root = (int)(1e-3 + pow((double)value, 1.0/ex_));
	uLL po_;
	while((po_=pow_((uLL)root, ex_)) > value)
		root--;
	return root;
}

/*
pLL idx_by_value_2(uLL num, int p1, int p2)
{
	pLL p1e19_1 = idx_by_value_1(num, p1);
	pLL p1e19_2 = idx_by_value_1(num, p2);
	uLL res = (p1e19_1.first - idx_by_value_1(num, lcm(p1,p2)).first) + p1e19_2.first;
	return make_pair(res, max(p1e19_1.second, p1e19_2.second));
}
*/

int calc_only_subset(uLL num, int curr_pow, size_t idx_in_a)
{
	if(curr_pow > 60 || (1LL << curr_pow) > num)
		return 0;
	int res = idx_by_value_1(num, curr_pow);
	for(size_t j = idx_in_a + 1;  j < a.size(); j++)
		res -= calc_only_subset(num, lcm(curr_pow, a[j]), j);
	return res-1; // "-1" because 1 is calculated separately
}

int calc_idx_by_value(uLL num)
{
	int res = 1; // value 1, common for all possible sequences
	for(size_t i=0; i<a.size(); i++)
		res += calc_only_subset(num, a[i], i);
	return res;
}

int main(int argc, char* argv[])
{
//	freopen("input.txt", "rt", stdin);
//	freopen("output.txt", "wt", stdout);
	int TEST_NUM;
	cin >> TEST_NUM;
	
	for(int the_test=0; the_test<TEST_NUM; the_test++)
	{
		uLL n;
		int k;
		cin >> n >> k;
		a.resize(k);
		for(int i=0; i<k; i++)
			cin >> a[i];

		cerr << "started the_test = " << the_test << " (n = " << n << ", k = " << k << ")\n";

		sort(a.begin(), a.end());
		for(int j=(int)a.size()-1; j>0; j--) {
			for(int i=0; i<j; i++) {
				if(a[j] % a[i] == 0) {
					a.erase(a.begin() + j);
					break; // breaks loop by i, but not loop by j
				}
			}
		}
		if(a[0]==1)
			cout << n << endl;
		else if(a.size()==1)
			cout << pow_((uLL)n, a[0]) << endl;
		else {
			uLL left_value = max(1uLL, pow_(n/a.size(), a[0], true)), 
				right_value = pow_(n, a[0], true);  // dangerous if double overflow
			while(right_value > left_value)
			{
				uLL mid_value = left_value + (right_value - left_value) / 2;
				int mid_res = calc_idx_by_value(mid_value);
				if(mid_res < n)
					left_value = mid_value + 1;
				else
					right_value = mid_value;
			}
			cout << left_value << endl;
		}
	}
	return 0;
}
