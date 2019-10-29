/*
 *  Task:    Bets
 *  Author:  Vadim Zaytsev
 *  Verdict: ACCEPTED
 */
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long int64;

const int kPrecision = int(1e5);
const double eps = 1e-6;

bool checkInt(int64 a, int64 b, int64 c) {
    return (b * c + a * c + a * b) * kPrecision < a * b * c;
}

int64 readDouble() {
    double a;
    scanf("%lf", &a);
    return int64(a * kPrecision + eps);
}

int main() {
#ifndef ILIKEGENTOO
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int q; 
    scanf("%d", &q);
    for (int i = 0; i < q; ++i) {
        const int64 w = readDouble();
        const int64 d = readDouble();
        const int64 l = readDouble();
        const bool vilka = checkInt(w, d, l);
        puts(vilka ? "YES" : "NO");
    }

    return 0;
}
