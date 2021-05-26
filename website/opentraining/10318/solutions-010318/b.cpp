#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cassert>
#include <bitset>
#include <unordered_map>
#include <cstring>
#include <ctime>

#define mp make_pair
#define pb push_back
#define LOCAL 1
#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

#if ((_WIN32 || __WIN32__) && __cplusplus < 201103L)
#define LLD "%I64d"
#else
#define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "connection-probability"

#ifdef LOCAL
static struct __timestamper {
    string what;
    __timestamper(const char* what) : what(what){};
    __timestamper(const string& what) : what(what){};
  ~__timestamper(){
        TIMESTAMPf("%s", what.data());
  }
} __TIMESTAMPER("end");
#else
struct __timestamper {
};
#endif

typedef long long ll;
typedef long double ld;

const int MAXN = 200;
const int inv100 = 570000004;
const int MOD = 1000000007;


int r, c;
int hor[MAXN][MAXN];
int ver[MAXN][MAXN];
int invans = 0;

#define GETMASK(pos) ((mask >> (4*pos)) & 15)
#define SETMASK(pos, val) mask = (mask & ~(15LL << (4*pos))) | (((ll)val) << (4*pos))

inline bool norm(ll &mask) {
  static int used[100];
  static int mapped[100];
  static int usedptr = 1;
  usedptr++;
  int cnt = 0;
  for (int i = 0; i < r; i++) {
    int col = GETMASK(i);
    if (used[col] != usedptr) {
      used[col] = usedptr;
      mapped[col] = cnt++;
    }
    SETMASK(i, mapped[col]);
  }
  if (used[GETMASK(r)] != usedptr)
    return false;
  SETMASK(r, mapped[GETMASK(r)]);
  return true;
}

inline bool set_to_new(ll &mask, int id) {
  SETMASK(id, 15);
  return norm(mask);
}

inline bool set_same_as(ll &mask, int id, int from) {
  SETMASK(id, GETMASK(from));
  return norm(mask);
}

inline bool set_and_join(ll &mask, int id, int from) {
  int col = GETMASK(id);
  int tocol = GETMASK(from);
  for (int i = 0; i <= r; i++)
    if (GETMASK(i) == col)
      SETMASK(i, tocol);
  return norm(mask);
}


inline void mult(int &a, int b) {
  a = (a * 1LL * b) % MOD;
}


inline void add(int &a, int b) {
  if ((a += b) >= MOD) a -= MOD;
}

inline void push_none(ll s, unordered_map<ll, int> &v, int i, int j, int cur) {
  if (set_to_new(s, i)) {
    mult(cur, MOD + 1 - hor[i][j]);
    if (i) {
      mult(cur, MOD + 1 - ver[i - 1][j]);
    }
    if (cur) {
      add(v[s], cur);
    }
  }
}

inline void push_left(ll s, unordered_map<ll, int> &v, int i, int j, int cur) {
  mult(cur, hor[i][j]);
  if (i) {
    mult(cur, MOD + 1 - ver[i - 1][j]);
  }
  if (cur) {
    add(v[s], cur);
  }
}

inline void push_up(ll s, unordered_map<ll,int>& v, int i, int j, int cur) {
  if (set_same_as(s, i, i - 1)) {
    mult(cur, MOD + 1 - hor[i][j]);
    mult(cur, ver[i - 1][j]);
    if (cur) {
      add(v[s], cur);
    }
  }
}

inline void push_both(ll s, unordered_map<ll, int> &v, int i, int j, int cur) {
  if (set_and_join(s, i, i - 1)) {
    mult(cur, hor[i][j]);
    mult(cur, ver[i - 1][j]);
    if (cur) {
      add(v[s], cur);
    }
  }
}

int solve() {
  unordered_map<ll, int> v;
  v[0] = 1;

  for (int j = 0; j < c - 1; j++) {
    for (int i = 0; i < r; i++) {
      unordered_map<ll, int> nv;
//      cerr<<v.size()<<endl;
      nv.rehash(v.size());
      for (const auto &s : v) {
        push_none(s.first, nv, i, j, s.second);
        push_left(s.first, nv, i, j, s.second);
        if (i) {
          push_up(s.first, nv, i, j, s.second);
          push_both(s.first, nv, i, j, s.second);
        }
      }
      v = nv;
    }
  }
  int ans = 0;
  for (const auto &s : v)
    add(ans, s.second);
  return ans;
}


void trans(int a[MAXN][MAXN], int r, int c) {
  static int temp[MAXN][MAXN];
  memset(temp, 0, sizeof(temp));
  for (int i = 0; i < r; i++)
    for (int j = 0; j < c; j++)
      temp[j][i] = (MOD + 1 - a[i][j]) % MOD;
  for (int i = 0; i < r; i++)
    for (int j = 0; j < c; j++)
      a[i][j] = 0;
  for (int i = 0; i < c; i++)
    for (int j = 0; j < r; j++)
      a[i][j] = temp[i][j];
}


int main() {
#ifndef NOFILES
  assert(freopen(TASKNAME".in", "r", stdin));
  assert(freopen(TASKNAME".out", "w", stdout));
#endif
  assert((inv100 * 100LL) % MOD == 1);
  scanf("%d%d", &r, &c);
  for (int i = 0; i < r; i++)
    for (int j = 0; j < c - 1; j++) {
      scanf("%d", &hor[i][j]);
      mult(hor[i][j], inv100);
    }
  for (int i = 0; i < r - 1; i++)
    for (int j = 0; j < c - 2; j++) {
      scanf("%d", &ver[i][j]);
      mult(ver[i][j], inv100);
    }

  if (c - 1 <= r) {
    trans(hor, r, c-1);
    trans(ver, r - 1, c-2);
    swap(r, c);
    r--;
    c++;
    invans = 1;
  }

  for (int i = 0; i < r; i++)
    ver[i][c - 2] = 1;

  int ans = solve();

  if (invans) {
    ans = (1 - ans + MOD) % MOD;
  }
  printf("%d\n", ans);
  return 0;
}
