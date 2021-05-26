#include <stdlib.h>
#include <string.h>
#include <algorithm>
#define IO_FILES
#include <cstdio>

#define PROBLEM_NAME "abtower"

int const BIG_MOD = 100;
int const BASE    =  10;

int powmod (int a, int b, int m)
{
	int res = 1;
	bool much = false;
	for (int i = 0; i < b; i++)
	{
		res = res * a;
		if (res >= m)
		{
			much = true;
			res %= m;
		}
	}
	return res + much * m;
}

int solve_mod (int a, int b)
{
	int cur = b;
	while (a < b)
	{
		b--;
		cur = powmod (b, cur, BIG_MOD);
	}
	return cur % BASE;
}

int main (void)
{
#ifdef IO_FILES
	freopen (PROBLEM_NAME ".in",  "rt", stdin);
	freopen (PROBLEM_NAME ".out", "wt", stdout);
#endif

	int a, b;
	while (scanf (" %d %d", &a, &b) > 0)
	{
		printf ("%d\n", solve_mod (a, b));
	}

	return 0;
}
