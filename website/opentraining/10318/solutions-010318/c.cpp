#include <stdlib.h>
#include <string.h>
#include <cstdio>
#include <vector>
#include <cassert>
#include <algorithm>
#include <map>
using namespace std;

typedef vector<int> perm;

perm operator*(const perm &a, const perm &b) {
  perm c(12);
  assert(a.size() == b.size() && a.size() == 12);
  for (int i = 0; i < 12; i++) {
    c[i] = a[b[i]];
  }
  return c;
}


// (0, 1, 2) -> (1, 0, 4)
// (0, 2, 3) -> (1, 4, 10)

// (0, 1)
// (2, 5)
// (3, 10)
// (4, 6)
// (11, 7)
// (8, 9)



const perm ZERO = {1, 0, 5, 10, 6, 2, 4, 11, 9, 8, 3, 7};

// (0 1 2)
// (6 3 5)
// (7 4 10)
// (11 8 9)
                  //0  1  2  3  4   5  6  7  8  9  10 11
const perm ONE = {1, 2, 0, 5, 10, 6, 3, 4, 9, 11, 7, 8};
            
void print(perm p) {
  for (int i = 0; i < 12; i++)
    printf("%d ", p[i]);
  printf("\n");
}

perm identy() {
  perm E(12);
  for (int i = 0; i < 12; i++)
    E[i] = i;
  return E;
}

void testPerms() {
  perm E = identy();
  assert(ZERO * ZERO == E);
  assert(ONE * ONE * ONE == E);
  assert(ZERO * ONE * ZERO * ONE * ZERO * ONE* ZERO * ONE * ZERO * ONE == E);

  vector<perm> v;
  v.push_back(ZERO);
  v.push_back(ONE);

  while (true) {
    vector<perm> nv;
    for (perm s : v)
      for (perm t : v)
        nv.push_back(s * t);
    sort(nv.begin(), nv.end());
    nv.erase(unique(nv.begin(), nv.end()), nv.end());
    if (v == nv) break;
    v = nv;
  }
  assert(v.size() == 60);
}

map<perm, vector<int>> c;
//map<perm, string> first;

int main() {
#ifndef NOFILES
  freopen("equivalence.in", "r", stdin);
  freopen("equivalence.out", "w", stdout);
#endif
  testPerms();

  int n;
  scanf("%d",&n);
  static char buf[100000];

  for (int i = 0; i < n; i++) {
    scanf("%s", buf);
    perm x = identy();
    for (int j = 0; buf[j]; j++)
      x = x * (buf[j] == '0' ? ZERO : ONE);
    c[x].push_back(i + 1);
//    if (first.find(x) == first.end() || first[x].size() > string(buf).size())
//      first[x] = buf;
  }
  vector<vector<int>> v;
  for (const auto &x : c)
    v.push_back(x.second);
  sort(v.begin(), v.end());
  printf("%d\n", (int)v.size());
  for (const auto& x : v) {
    printf("%d", (int)x.size());
    for (int id : x)
      printf(" %d", id);
    printf("\n");
  }
  //for (auto x: first)
  //  printf("%s\n", x.second.c_str());
}

