#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <cstdio>

#define MOD 1000003
#define MAX 200000
#define MAXDEPTH 20

typedef long long int64;

struct Polinom {
  int n;
  int a[2 * MAX];
};

Polinom x1[MAXDEPTH], x0[MAXDEPTH];
Polinom y1[MAXDEPTH], y0[MAXDEPTH];
Polinom z2[MAXDEPTH], z1[MAXDEPTH], z0[MAXDEPTH];

#define GRANICA 30
int64 tmp[2 * GRANICA];

void Mult(int depth, Polinom& A, Polinom& B, Polinom& C) {
  if (A.n <= GRANICA) {
    C.n = A.n + B.n - 1;
    for (int i = 0; i < C.n; ++i) tmp[i] = 0;
    for (int i = 0; i < A.n; ++i) {
      for (int j = 0; j < B.n; ++j) {
        tmp[i + j] += (int64)A.a[i] * B.a[j];
      }
    }
    for (int i = 0; i < C.n; ++i) C.a[i] = tmp[i] % MOD;
    return;
  }

  if (A.n & 1) {
    A.a[A.n++] = 0;
    B.a[B.n++] = 0;
  }

  int m = A.n / 2;

  Polinom &X0 = x0[depth];
  Polinom &X1 = x1[depth];
  Polinom &Y0 = y0[depth];
  Polinom &Y1 = y1[depth];
  Polinom &Z0 = z0[depth];
  Polinom &Z1 = z1[depth];
  Polinom &Z2 = z2[depth];

  for (X0.n = 0; X0.n < m; ++X0.n) X0.a[X0.n] = A.a[X0.n];
  for (X1.n = 0; X1.n < m; ++X1.n) X1.a[X1.n] = A.a[m + X1.n];
  for (Y0.n = 0; Y0.n < m; ++Y0.n) Y0.a[Y0.n] = B.a[Y0.n];
  for (Y1.n = 0; Y1.n < m; ++Y1.n) Y1.a[Y1.n] = B.a[m + Y1.n];
  Mult(depth + 1, X1, Y1, Z2);
  Mult(depth + 1, X0, Y0, Z0);
  for (int i = 0; i < m; ++i) {
    X0.a[i] += X1.a[i];
    if (X0.a[i] >= MOD) X0.a[i] -= MOD;
  }
  for (int i = 0; i < m; ++i) {
    Y0.a[i] += Y1.a[i];
    if (Y0.a[i] >= MOD) Y0.a[i] -= MOD;
  }

  Mult(depth + 1, X0, Y0, Z1);

  for (C.n = 0; C.n < A.n + B.n - 1; ++C.n) C.a[C.n] = 0;
  for (int i = 0; i < 2 * m - 1; ++i) {
    C.a[i] += Z0.a[i];
    C.a[m + i] += Z1.a[i] - Z0.a[i] - Z2.a[i];
    C.a[2 * m + i] += Z2.a[i];
  }
  for (int i = 0; i < C.n; ++i) {
    if (C.a[i] < 0) {
      C.a[i] += MOD;
      if (C.a[i] < 0) C.a[i] += MOD;
    } else if (C.a[i] >= MOD) {
      C.a[i] -= MOD;
      if (C.a[i] >= MOD) C.a[i] -= MOD;
    }
  }
}

int A[MAX];
int B[MAX];
int row0[MAX];
int col0[MAX];
int f[2 * MAX];
int inv_f[2 * MAX];

int FastPow(int a, int n) {
  if (n == 0) return 1;
  if (n & 1) return (int64)a * FastPow(a, n - 1) % MOD;
  int x = FastPow(a, n >> 1);
  return (int64)x * x % MOD;
}

int Mult(int a, int b) { return (int64)a * b % MOD; }
int Mult(int a, int b, int c) { return Mult(Mult(a, b), c); }
int Mult(int a, int b, int c, int d) { return Mult(Mult(a, b), Mult(c, d)); }
int Add(int a, int b) {
  int t = a + b;
  if (t >= MOD) t -= MOD;
  return t;
}

int main() {
  int n, a, b, c;
  scanf("%d%d%d%d", &n, &a, &b, &c);
  for (int i = 0; i < n; ++i) scanf("%d", &row0[i]);
  for (int i = 0; i < n; ++i) scanf("%d", &col0[i]);

  A[0] = B[0] = f[0] = 1;
  for (int i = 1; i < n; ++i) A[i] = (int64)A[i - 1] * a % MOD;
  for (int i = 1; i < n; ++i) B[i] = (int64)B[i - 1] * b % MOD;
  for (int i = 1; i < 2 * n; ++i) f[i] = (int64)f[i - 1] * i % MOD;
  for (int i = 0; i < 2 * n; ++i) inv_f[i] = FastPow(f[i], MOD - 2);

  int result = 0;
  for (int i = 1; i < n; ++i) {
    int x = n - 1;
    int y = n - i - 1;
    int comb = Mult(f[x + y - 1], inv_f[x - 1], inv_f[y]);
    result = Add(result, Mult(row0[i], comb, A[x], B[y]));
  }
  for (int i = 1; i < n; ++i) {
    int x = n - i - 1;
    int y = n - 1;
    int comb = Mult(f[x + y - 1], inv_f[x], inv_f[y - 1]);
    result = Add(result, Mult(col0[i], comb, A[x], B[y]));
  }

  Polinom x;
  Polinom y;
  x.n = n - 1;
  y.n = n - 1;
  for (int i = 0; i < n - 1; ++i) {
    x.a[i] = Mult(A[i], inv_f[i]);
    y.a[i] = Mult(B[i], inv_f[i]);
  }
  Polinom z;
  Mult(0, x, y, z);
  for (int i = 0; i <= 2 * n - 4; ++i) {
    result = Add(result, Mult(c, z.a[i], f[i]));
  }
  printf("%d\n", result);
  return 0;
}
