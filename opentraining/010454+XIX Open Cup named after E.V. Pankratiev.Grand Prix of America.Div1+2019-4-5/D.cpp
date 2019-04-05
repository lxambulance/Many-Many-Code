#include <bits/stdc++.h>
using namespace std;

struct Data
{
    long long f,g,h;
};

Data Calc(long long a,long long b,long long c,long long n)
{
    Data tmp;
    if (a==0)
    {
        tmp.f=tmp.g=tmp.h=0;
        return tmp;
    }
    if (a>=c || b>=c)
    {
        tmp = Calc(a%c,b%c,c,n);
        tmp.h = tmp.h + n*(n+1)*(2*n+1)/6*(a/c)*(a/c) + (n+1)*(b/c)*(b/c) + 2*(a/c)*tmp.g + 2*(b/c)*tmp.f + n*(n+1)*(a/c)*(b/c);
        tmp.f = tmp.f + n*(n+1)/2*(a/c) + (n+1)*(b/c);
        tmp.g = tmp.g + n*(n+1)*(2*n+1)/6*(a/c) + n*(n+1)/2*(b/c);
        return tmp;
    }
    long long m=(a*n+b)/c;
    Data nxt=Calc(c,c-b-1,a,m-1);
    tmp.f = n*m - nxt.f;
    tmp.g = (n*(n+1)*m-nxt.f-nxt.h)/2;
    tmp.h = m*(m+1)*n - 2*(nxt.g+nxt.f) - tmp.f;
    return tmp;
}


int main()
{
    int T, p, q, n;
    scanf ("%d",&T);
    while (T--)
    {
        scanf ("%d %d %d", &p, &q, &n);
        Data tmp = Calc(p, 0, q, n);
        long long ans = tmp.f;
        printf ("%lld\n", 1ll * (1 + n) * n / 2 * p - ans * q);
    }
}
