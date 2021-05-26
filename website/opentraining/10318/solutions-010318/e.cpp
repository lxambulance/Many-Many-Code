#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

#define all(c) (c).begin(),(c).end()
#define sz(c) (int)(c).size()
#define pb push_back
#define mp make_pair
#define x first
#define y second
#define image(a) {sort(all(a)),a.resize(unique(all(a))-a.begin());}
#define taskname "make-a-row"
int n;
const int maxn = (int)1e5;
int a[maxn * 2];
ld f(ld x) {
  ld res = 0;
  for (int i = 0; i < n; i++) {
    res += sqrt(1 + (a[i] - x - i) * (a[i] - x - i));
  }
  return res;
}
int main(){
  #ifndef NOFILES
  assert(freopen(taskname ".out","wt",stdout));
  assert(freopen(taskname ".in","rt",stdin));
  #endif
  scanf("%d", &n);
  n *= 2;
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }
  sort(a, a + n);
  ld l = a[0] - n;
  ld r = a[n - 1];
  for (int it = 0; it < 100; it++) {
    ld m1 = (l * 2 + r) / 3;
    ld m2 = (l + r * 2) / 3;
    ld f1 = f(m1);
    ld f2 = f(m2);
    if (f1 < f2) {
      r = m2;
    } else {
      l = m1;
    }
  }
  printf("%.18lf\n", (double)f((l + r) / 2));
  #ifdef home
  cerr.precision(18);
  cerr<<(l + r) / 2 << endl;
  #endif
  return 0;
}
