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
#define taskname "hamilton-clique"
int n;
int main(){
  #ifndef NOFILES
  assert(freopen(taskname ".out","wt",stdout));
  assert(freopen(taskname ".in","rt",stdin));
  #endif
  scanf("%d", &n);
  printf("Yes\n");
  vector<int> ls;
  int curl = 2;
  int curr = n;
  ls.pb(curl);
  for (int i = 0; i < n / 2; i++) {
    ls.pb(curl + 1);
    ls.pb(curr);
    curl++;
    curr--;
  }
  ls.pop_back();
  for (int i = 0; i < (n - 1) / 2; i++) {
    printf("1");
    for (int j = 0; j < sz(ls); j++) {
      printf(" %d", (ls[j] - 2 + i) % (n - 1) + 2);
    }
    printf("\n");
  }
  return 0;
}
