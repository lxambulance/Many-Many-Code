#include<bits/stdc++.h>
using namespace std;
const int N=100010;
char s[N],t[N];
int nxt[N][26];
int main(){
	//freopen("xxx.in","r",stdin);
	scanf("%s%s",s+1,t+1);
	int n=strlen(s+1),m=strlen(t+1);
	for(int i=0;i<26;i++)nxt[n][i]=nxt[n+1][i]=n+1;
	for(int i=n-1;i>=0;i--){
		memcpy(nxt[i],nxt[i+1],sizeof(nxt[i]));
		nxt[i][s[i+1]-'a']=i+1;
	}
	long long ans=0;
	for(int i=1;i<=n;i++){
		int now=i-1;
		for(int j=1;j<=m;j++){
			now=nxt[now][t[j]-'a'];
		}
		ans+=n-now+1;
	}
	cout<<ans<<endl;
}