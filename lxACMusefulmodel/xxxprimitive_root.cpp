#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
inline LL read() {
	LL x=0,s=1; char ch=getchar();
	while (ch<'0'||ch>'9') { if (ch=='-') s=-1; ch=getchar(); }
	while (ch>='0'&&ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	return s*x;
}

LL pow_mod(LL a,LL b,LL c) {
	LL ans=1;
	while (b) {
		if (b&1) ans=ans*a%c;
		a=a*a%c; b>>=1;
	}
	return ans;
}
vector<LL> a;
bool g_test(LL g,LL p) {
	for (LL i=0;i<a.size();++i) 
	if (pow_mod(g,(p-1)/a[i],p)==1) return 0;
	return 1;
}
LL primitive_root(LL p) {
	LL tmp=p-1;
	for (LL i=2;i*i<=tmp;++i)
	if (!(tmp%i)) {
		a.push_back(i);
		while (!(tmp%i)) tmp/=i;
	}
	if (tmp>1) a.push_back(tmp);
	for (LL g=1;;g++) if (g_test(g,p)) return g;
}
int main() {
	LL p=read();
	cout<<primitive_root(p)<<endl;
	
	return 0;
}

/*
*/

