#include <stdlib.h>
#include <string.h>
#define IO_FILES
#include <algorithm>
#include <cstdio>

#define PROBLEM_NAME "pqknight"

using namespace std;

struct Res
{
	int d;
	int x;
	int y;
	Res (int nd, int nx, int ny) : d (nd), x (nx), y (ny) {}
};

Res euclid (int p, int q)
{
	if (p == 0)
	{
		return Res (q, 0, 1);
	}
	Res cur = euclid (q % p, p);
	return Res (cur.d, cur.y - (q / p) * cur.x, cur.x);
}

int solve_euclid (int p, int q)
{
	Res res = euclid (p, q);
	if (res.d != 1 || ((p & 1) == (q & 1)))
	{
		return -1;
	}
	if ((res.x & 1) != (p & 1) || (res.y & 1) != (q & 1))
	{
		int mult = (res.y <= 0) ? 1 : -1;
		res.x -= q * mult;
		res.y += p * mult;
	}
	return max (abs (res.x), p) + max (abs (res.y), q);
}

int main (void)
{
#ifdef IO_FILES
	freopen (PROBLEM_NAME ".in",  "rt", stdin);
	freopen (PROBLEM_NAME ".out", "wt", stdout);
#endif

	int p, q;
	while (scanf (" %d %d", &p, &q) > 0)
	{
		printf ("%d\n", solve_euclid (p, q));
	}

	return 0;
}
