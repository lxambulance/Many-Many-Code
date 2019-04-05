#include<bits/stdc++.h>
using namespace std;
const int N=400010;
struct Q{
	int x1,x2,y1,y2;
}q[N];
int ls[N],cnt,c[N],n;
vector<int>add[N],del[N];
vector<pair<int,int>>p[N];
void ad(int x,int v){
	for(;x<N;x+=x&-x)c[x]+=v;
}
int gt(int x){
	int ret=0;
	for(;x;x-=x&-x)ret+=c[x];
	return ret;
}
void get(int&x){
	int l=1,r=cnt+1;
	while(l!=r){
		int mid=l+r>>1;
		if(ls[mid]<x)l=mid+1;
		else r=mid;
	}
	x=l;
}
int main(){
	//freopen("xxx.in","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d%d%d",&q[i].x1,&q[i].y1,&q[i].x2,&q[i].y2);
		ls[++cnt]=q[i].x1;
		ls[++cnt]=q[i].y1;
		ls[++cnt]=q[i].x2;
		ls[++cnt]=q[i].y2;
	}
	sort(ls+1,ls+cnt+1);
	for(int i=1;i<=n;i++){
		get(q[i].x1),get(q[i].y1),get(q[i].x2),get(q[i].y2);
		add[q[i].x1].push_back(q[i].y1);
		del[q[i].x2].push_back(q[i].y1);
		add[q[i].x1].push_back(q[i].y2);
		del[q[i].x2].push_back(q[i].y2);
		p[q[i].x1].push_back(make_pair(q[i].y1,q[i].y2));
		p[q[i].x2].push_back(make_pair(q[i].y1,q[i].y2));
	}
	for(int i=1;i<=cnt;i++){
		for(auto x:del[i])ad(x,-1);
		for(auto x:p[i]){
			if(gt(x.second)!=gt(x.first-1)){
				puts("1");
				exit(0);
			}
		}
		for(auto x:add[i])ad(x,1);
	}
	puts("0");
}