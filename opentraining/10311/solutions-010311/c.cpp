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

bool prime[MAX];

void eratosfen(){
        memset(prime, 1, sizeof(prime));
        prime[0] = prime[1] = false;
        for(int i = 2; i <= sqrt(MAX); i++)
                if(prime[i]){
                        for(int j = i * i; j < MAX; j += i)
                                prime[j] = false;
                }
}

int get(int n){
        int ans = 0;
        while(n != 0){
                ans = ans * 10 + (n % 10);
                n /= 10;
        }
        return ans;
}

bool check(int val){
        if(!prime[val])
                return false;
        int r = get(val);
        if(r == val)
                return false;
        return prime[r];
}

int main() {

        sync;

#ifdef LOCAL
        srand(time(NULL));
        input;
#else

#endif

        eratosfen();

        int n;
        cin >> n;

        for(int i = 13; i <= 1e6; i++)
                if(check(i)){
                        if(--n == 0){
                                cout << i;
                                return 0;
                        }
                }

        cout << -1;

}