#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
int isprime(int n){
	for (int i=2;i*i<=n;++i) if (n%i==0) return 0;
	return 1;
}
void test(){
	int n,m;
	scanf("%d%d",&n,&m);
	while (!isprime(n)) n++;
	while (!isprime(m)) m++;
	printf("%d %d\n",n,m);
}
struct Data{
	char name[20];
	LL PhoneNumber;
	bool operator ==(const Data &other)const{
		for (int i=0;i<20;++i) if (name[i]!=other.name[i]) return 0;
		return 1;
	}
};
const int Mo=19301,lx=193;
struct Hash{
	int n;
	vector<Data*> a[Mo];
	void init(){
		n=0;
		for (int i=0;i<Mo;++i) a[i].clear();
	}
	int get_key(LL x){ return x*lx%Mo; }
	void ins(Data* x){
		int y=get_key(x->PhoneNumber);
		a[y].push_back(x); ++n;
	}
	void del(LL x){
		int y=get_key(x),len=a[y].size();
		for (int i=0;i<len;++i)
		if (a[y][i]->PhoneNumber==x) {
			delete a[y][i];
			swap(a[y][i],a[y][len-1]);
			a[y].pop_back();
			n--;
			printf("Del OK!\n");
			return;
		}
	}
	Data* find(LL x){
		int y=get_key(x),len=a[y].size();
		for (int i=0;i<len;++i)
		if (a[y][i]->PhoneNumber==x) return a[y][i];
		return NULL;
	}
}H;
int main(){
	//test();
	H.init();
	int n,m,q;
	scanf("%d",&n);
	for (int i=1;i<=n;++i) {
		Data* x=new Data;
		scanf("%s%lld",x->name,&x->PhoneNumber);
		H.ins(x);
	}
	scanf("%d",&m);
	for (int i=1;i<=m;++i) {
		LL x;
		scanf("%lld",&x);
		H.del(x);
	}
	scanf("%d",&q);
	for (int i=1;i<=q;++i) {
		LL x;
		scanf("%lld",&x);
		Data* ret=H.find(x);
		if (ret!=NULL) printf("%s %lld\n",ret->name,ret->PhoneNumber); else printf("no this one!\n");
	}
	return 0;
}

/*
*/
