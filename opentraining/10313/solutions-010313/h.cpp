/**
 * Correct solution (must be OK).
 * Author: stgatilov
 * Dynamic programming with presorted items in O(N S) time and O(S) space.
 */

//#pragma comment(linker, "/STACK:20000000")
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <ctime>

using namespace std;
typedef long long int64;
#ifdef HOME
	#define E(c) cerr<<#c
	#define Eo(x) cerr<<#x<<" = "<<(x)<<endl
	#define Ef(...) fprintf(stderr, __VA_ARGS__)
#else
	#define E(c) ((void)0)
	#define Eo(x) ((void)0)
	#define Ef(...) ((void)0)
#endif

const int MAXN = 100<<10;	//note: more than necessary
const int MAXW = 100<<10;

struct Item {
	int type;
	int cost;
	int name;
};

int n, w;
Item arr[MAXN];

int res[2][MAXW][2];

int main(int argc, char **argv) {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	scanf("%d%d", &n, &w);
	for (int i = 0; i < n; i++) {
		scanf("%d%d", &arr[i].type, &arr[i].cost);
		arr[i].name = i+1;
	}

	sort(arr, arr+n, [](const Item &a, const Item &b) { return a.type < b.type; });
	arr[n].type = -1;

	memset(res, -63, sizeof(res));
	res[0][0][false] = 0;
	for (int i = 0; i < n; i++) {
		memset(res[(i+1)&1], -63, sizeof(res[0]));
		for (int s = 0; s <= w; s++)
			for (int f = 0; f < 2; f++) {
				int tres = res[i&1][s][f];
				if (tres < 0) continue;
//				Ef("%d %d %d -> %d\n", i, s, f, tres);

				for (int a = 0; a < 2; a++) {
					int ni = i+1;
					int ns = s + (a ? arr[i].cost : 0);
					int nf = f;
					int nres = tres;
					if (a) {
						nf = true;
						nres += !f;
					}
					if (arr[i+1].type != arr[i].type)
						nf = false;

					if (ns > w)
						continue;
					if (res[ni&1][ns][nf] < nres)
						res[ni&1][ns][nf] = nres;
				}
			}
	}

	int ans = res[n&1][w][0];

	if (ans < 0) {
		printf("Impossible\n");
		return 0;
	}
	printf("%d\n", ans);
	return 0;
}
