#include <stdio.h>

int gcd(int a, int b)
{
    return b ? gcd(b, a % b) : a;
}

int main()
{
    //freopen("solitaire.in", "r", stdin);
    //freopen("solitaire.out", "w", stdout);

    int N, K;
    scanf("%d %d", &N, &K);

    printf("%d\n", gcd(N, K));
}
