#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;

struct Resume
{
    int a, c, s;
} man[200111];

bool cmp(Resume x, Resume y)
{
    return (x.c > y.c || (x.c == y.c && x.a < y.a));
}

long long dp0[501][501], dp1[501][501];

int main()
{
    int n, k;
    scanf("%d%d", &n, &k);

    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d%d", &man[i].a, &man[i].c, &man[i].s);
        if (man[i].a == 2) man[i].a = 3;
        else
        if (man[i].a == 3) man[i].a = 2;
    }

    sort(man + 1, man + n + 1, cmp);

   for (int i=1;i<=n;i++)
    {
    fprintf(stderr,"%d %d %d\n",man[i].a,man[i].c,man[i].s);
    }


    for (int x = 0; x <= k; x++)
        for (int y = 0; y <= k; y++)
            dp0[x][y] = dp1[x][y] = 1e18;
    dp0[0][0] = 0;

    for (int i = 1; i <= n; i++)
    {

        for (int x = 0; x <= k; x++)
            for (int y = 0; y <= x; y++)
            {
                if (dp0[x][y] == 1e18) continue;

                dp1[x][y] = min(dp1[x][y], dp0[x][y]);

                if (man[i].a == 1 || man[i].a == 2)
                    dp1[x + 1][y + 1] = min(dp1[x + 1][y + 1],
                                            dp0[x][y] + man[i].s);

                if ((y > 0) &&
                    (man[i].a == 3 || man[i].a == 2))
                        dp1[x][y - 1] = min(dp1[x][y - 1],
                                            dp0[x][y] + man[i].s);
            }

        for (int x = 0; x <= k; x++)
            for (int y = 0; y <= k; y++)
            {
                dp0[x][y] = dp1[x][y];
                dp1[x][y] = 1e18;
            }
    }

    cout << dp0[k][0]<< endl;
}
