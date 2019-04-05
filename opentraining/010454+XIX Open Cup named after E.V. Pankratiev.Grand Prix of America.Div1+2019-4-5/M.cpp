#include<bits/stdc++.h>
using namespace std;
const int N=100010,mod=1000000007;
int a[N],n,m;
int calc(int l,int r){
	if(l==r)return 1;
	int mid=l+r>>1,f=0,g=0;
	for(int i=l,j=mid+1;i<=mid;i++,j++){
		if(a[i]==a[j])f=1;
		else g=1;
	}
	if(f&&g)return 0;
	if(f)return 2ll*calc(l,mid)%mod;
	if(g)return (long long)calc(l,mid)*calc(mid+1,r)%mod;
}
int main(){
	//freopen("xxx.in","r",stdin);
	scanf("%d%d",&m,&n);
	m=1<<m;
	for(int i=0;i<m;i++)scanf("%d",&a[i]);
	printf("%d\n",calc(0,m-1));
}