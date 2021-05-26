#include <bits/stdc++.h>
using namespace std;

const int N = 305;
const int mod = 1e9 + 7;
int n;
long long b[N], p;
long long x[N][N], num[N], q[N];
long long summ[N];
long long minb[N];

struct Edge
{
    int num;
    int next;
}edge[N];
int tot, last[N];
long long inv[N];

void Add(int i, int j)
{
    tot++;
    edge[tot].num = j;
    edge[tot].next = last[i];
    last[i] = tot;
}

void Init()
{
    inv[1] = 1;
	for(int i = 2; i < N;i++)
        inv[i] = (mod - (mod / i)) * inv[mod % i] % mod;
}

long long Pow(long long a, int b)
{
    long long ans = 1;
    while (b != 0)
    {
        if (b % 2) ans = (ans * a) % mod;
        a = (a * a) % mod;
        b/=2;
    }
    return ans;
}

void dfs(int i)
{
    if (last[i] == 0)
    {
        x[i][0] = 1;
        num[i] = 1;
        minb[i] = b[i];
        return ;
    }
    minb[i] = b[i];
    for (int k = last[i]; k != 0; k = edge[k].next)
    {
        dfs(edge[k].num);
        minb[i] = min(minb[i], minb[edge[k].num]);
    }
    x[i][0] = 1;
    num[i] = 1;

    for (int k = last[i]; k != 0; k = edge[k].next)
    {
        int v = edge[k].num;
        long long sum = 0, t = minb[v];
        long long invb = Pow(b[v], mod - 2);

        for (int j = 0; j < num[v]; j++)
        {
            sum = (sum + t * x[v][j] % mod * inv[j + 1] % mod) % mod;
            t = t * minb[v] % mod;
            q[j + 1] = - x[v][j] * inv[j + 1] % mod * invb % mod;
        }
        q[0] = sum * invb % mod;

        memset(summ, 0, sizeof(summ));
        for (int j = 0; j < num[i]; j++)
            for (int r = 0; r <= num[v]; r++)
                summ[j + r] = (summ[j + r] + q[r] * x[i][j]) % mod;
        for (int j = 0; j < num[i] + num[v]; j++)
            x[i][j] = summ[j];
        num[i] = num[i] + num[v];
    }
}

int main()
{
    scanf ("%d", &n);
    Init();
    int root;
    for (int i = 1; i <= n; i++)
    {
        scanf ("%d %d",&b[i], &p);
        if (p == 0) root = i;
        else Add(p, i);
    }
    dfs(root);
    long long sum = 0, t = minb[root];
    for (int j = 0; j < num[root]; j++)
    {
        sum = (sum + t * x[root][j] % mod * inv[j + 1] % mod) % mod;
        t = t * minb[root] % mod;
    }
    printf ("%lld", (sum * Pow(b[root], mod - 2) % mod + mod) % mod);
}
