#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
inline ll read() {
	ll x=0,s=1; char ch=getchar();
	while (ch<'0'||ch>'9') { if (ch=='-') s=-1; ch=getchar(); }
	while (ch>='0'&&ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	return s*x;
}

ll qpow(ll a,ll b,ll c){
	ll ans=1;
	while (b) {
		if (b&1) ans=ans*a%c;
		a=a*a%c; b>>=1;
	}
	return ans;
}
int phim;
vector<int> a;
bool prTest(int g,int m){
	for (int i=0;i<a.size();++i) 
	if (qpow(g,phim/a[i],m)==1) return 0;
	return 1;
}
int getPrimitiveRoot(int m,int st){
	int tmp=phim;
	for (int i=2;i*i<=tmp;++i)
	if (!(tmp%i)) {
		a.push_back(i);
		while (!(tmp%i)) tmp/=i;
	}
	if (tmp>1) a.push_back(tmp);
	for (;;st++) if (prTest(st,m)) return st;
}
/*
1、有正整数m有原根的充要条件是m=2|4|p^e|2*p^e，p为奇素数，e为正整数。
2、每个正整数m都有phi(phi(m))个原根。
3、g^0,g^1,...,g^(phi(m)-1)各数mod m即为小于m且与m互质的phi(m)个数的排列。
*/
int getPhi(int n) {
	int i,j=n,k=n;
	for (i=2;i*i<=k;++i) 
	if (!(k%i)) {
		j=j/i*(i-1);
		while (!(k%i)) k/=i;
	}
	if (k>1) { j=j/k*(k-1); k=1; }
	return j;
}
int main() {
    int n;
	while (scanf("%d",&n)!=EOF) {
        phim=getPhi(n);
        int m=1,num=phim;
        while (m<n) {
            int tmp=getPrimitiveRoot(n,m);
            if (!~tmp) {
                printf("-1");
                break;
            }
            m=tmp+1; num--;
            printf("%d",tmp);
            if (num) putchar(' ');
        }
        puts("");
    }

	return 0;
}

/*
*/

