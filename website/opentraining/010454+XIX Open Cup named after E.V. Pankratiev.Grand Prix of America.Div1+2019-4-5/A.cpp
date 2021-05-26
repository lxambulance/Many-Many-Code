#include <bits/stdc++.h>
using namespace std;

const int N = 2505;
int n, m;
double x[N], y[N];
long double p[N];

long double Cross(double x1, double y1, double x2, double y2)
{
    return x1 * y2 - x2 * y1;
}

void Init()
{
    p[m - 2] = 1;
    for (int i = 1; i <= m; i++)
        p[m - 2] = p[m - 2] * (long double)i / (double)(n - i + 1);
    for (int i = m - 1; i <= n - 2; i++)
        p[i] = p[i - 1] * i / (i - (m - 2));
}

double Calc(int i, int j)
{
    if (i < j) return p[j - i - 1];
    else return p[n - i + j - 1];
}

int main()
{
    scanf ("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf ("%lf %lf", &x[i], &y[i]);

    Init();
    double ans =  0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            if (i == j) continue;
            ans += Cross(x[i], y[i], x[j], y[j]) * Calc(i, j);
        }
    printf ("%.8lf",ans / 2);
}
