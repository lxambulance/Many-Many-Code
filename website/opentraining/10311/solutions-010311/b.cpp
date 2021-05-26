#include <bits/stdc++.h>
using namespace std;
#define files(x) freopen(x ".in", "r", stdin); freopen(x ".out", "w", stdout);
#define input freopen("input.txt", "r", stdin)
#define output freopen("output.txt", "w", stdout)
#define sync ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define ms(x) memset(x, 0, sizeof(x));
#define sqr(a) ((a) * (a))
#define endl "\n"
#define mod % 1000000007
#define y1 Y1
typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ii, ii> iii;
typedef vector<ii>::iterator vit;
typedef double ld;
typedef int** matrix;
const ld E = 1e-11;

#ifdef LOCAL
const ll MAX = 101;
///#define DEBUG
#else
const ll MAX = 1e6 + 1;
#endif

int get(int i, int n) {
        if (i >= n) {
                int q = i - (n - 1);
                i -= q * 2;
        }
        return i + 1;
}

int p(int n, int m){
        int ans = 0;
        for(int i = 0; i < n; i++){
                for(int j = 0; j < m; j++){
                        int a1 = j * n + i;
                        int b1 = i * m + j;
                        if(a1 == b1)
                                ans++;
                }
        }
        return ans;
}

void p(){
        cout << "  ";
                for(int i = 1; i <= 9; i++)
                        cout << i << " ";
                cout << endl;

                for(int i = 1; i <= 9; i++){
                        cout << i << " ";
                        for(int j = 1; j <= 9; j++)
                                cout << p(i, j) - 1 << " ";
                        cout << endl;
                }

}

int main() {

        sync;

#ifdef LOCAL
        input;
#else

#endif


        int n;
        cin >> n;

        bool a[n * 2 - 1], b[n * 2 - 1];
        ms(a);
        ms(b);

        int m;
        cin >> m;

        while(m--) {
                int x, y;
                cin >> x >> y;
                x--, y--;
                a[x + y] = true;
                b[y - x + n - 1] = true;
        }

        ll ans = 0;
        for(int i = 0; i < n * 2 - 1; i++)
                if(a[i])
                        ans += get(i, n);
        for(int i = 0; i < n * 2 - 1; i++)
                if(b[i])
                        ans += get(i, n);

        int *res = new int[n * 2 + 1];
        res[0] = res[1] = 0;
        res += 2;

        for(int i = 0; i < n * 2 - 1; i++) {
                res[i] = res[i - 2] + a[i];
        }

        for(int i = 0; i < n * 2 - 1; i++) {
                if(b[i]) {
                        int x1 = (i <= n - 1 ? n - 1 - i : 0);
                        int y1 = (i <= n - 1 ? 0 : i - (n - 1));
                        int x2 = (i <= n - 1 ? n - 1 : n - 1 - (i - (n - 1)));
                        int y2 = (i <= n - 1 ? i : n - 1);
                        ans -= res[x2 + y2] - res[x1 + y1 - 2];
                }
        }

        cout << (ll) n * n - ans;

}