#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<vector>
using namespace std;
typedef long long LL;
#define ll long long 
#define re register
#define gc getchar
#define pc putchar
#define puts put_s
#define cs const

namespace Linear_sieves{
	cs int P=300005;
	int prime[P],pcnt;
	bool mark[P];
	
	inline void init(int len=P-5){
		mark[1]=true;
		for(int re i=2;i<=len;++i){
			if(!mark[i])prime[++pcnt]=i;
			for(int re j=1;j<=pcnt&&i*prime[j]<=len;++j){
				mark[i*prime[j]]=true;
				if(i%prime[j]==0)break;
			}
		}
	}
}

namespace Find_root{
	#define complex COMPLEX
	using namespace Linear_sieves;
	
	inline ll mul(cs ll &a,cs ll &b,cs ll &mod){
		return (a*b-(ll)((long double)a/mod*b)*mod+mod)%mod;
	}
	inline ll quickpow(ll a,ll b,cs ll &mod,ll res=1){
		for(;b;b>>=1,a=mul(a,a,mod))if(b&1)res=mul(res,a,mod);
		return res;
	}
	
	inline ll ex_gcd(cs ll &a,cs ll &b,ll &x,ll &y){
		if(!b){
			y=0;
			x=1;
			return a;
		}
		ll t=ex_gcd(b,a-a/b*b,y,x);
		y-=(a/b)*x;
		return t;
	}
	inline ll inv(cs ll a,cs ll mod){
		ll x,y;
		ll t=ex_gcd(a,mod,x,y);
		return (x%mod+mod)%mod;
	}
	
	ll W,Mod;
	class complex{
		public:
			ll x,y;
			complex(cs ll &_x=0,cs ll &_y=0):x(_x),y(_y){}
			inline friend complex operator*(cs complex &a,cs complex &b){
				return complex(
					(mul(a.x,b.x,Mod)+mul(mul(a.y,b.y,Mod),W,Mod))%Mod,
					(mul(a.x,b.y,Mod)+mul(a.y,b.x,Mod))%Mod);
			}
	};
	
	complex quickpow(complex a,ll b){
		complex res(1,0);
		for(;b;b>>=1,a=a*a)if(b&1)res=res*a;
		return res;
	}
	
	inline bool isprime(ll x){
		if(x<=P-5)return !mark[x];
		if(x%2==0||x%3==0||x%5==0||x%7==0||x%31==0||x%24251==0)return false;
		re ll t=x-1,s;
		t>>=(s=__builtin_ctzll(t));
		for(int re i=1;i<=5;++i){
			re ll p=prime[rand()%pcnt+1];
			re ll num=quickpow(p,t,x),pre=num;
			for(int re j=0;j<s;++j){
				num=mul(num,num,x);
				if(num==1&&pre!=x-1&&pre!=1)return false;
				pre=num;
				if(num==1)break;
			}
			if(num^1)return false;
		}
		return true;
	}
	
	inline ll Pollard_rho(ll x){
		if(x%2==0)return 2;
		if(x%3==0)return 3;
		if(x%5==0)return 5;
		if(x%7==0)return 7;
		if(x%31==0)return 31;
		if(x%24251==0)return 24251;
		re ll n=0,m=0,t=1,q=1,c=rand()%(x-2)+2;
		for(int re k=2;;k<<=1,m=n,q=1){
			for(int re i=1;i<=k;++i){
				n=(mul(n,n,x)+c)%x;
				q=mul(q,abs(n-m),x);
			}
			if((t=__gcd(q,x))>1)return t;
		}
	}
	
	ll fact[60],cntf;
	inline void sieves(ll x){
		if(x==1)return ;
		if(isprime(x)){fact[++cntf]=x;return;}
		re ll p=x;
		while(p==x)p=Pollard_rho(p);
		sieves(p);
		while(x%p==0)x/=p;
		sieves(x);
	}
	
	inline ll solve_2k(ll a,ll k){
		if(a%(1<<k)==0)return 0;
		a%=(1<<k);
		re ll t=0,res=1;
		a>>=(t=__builtin_ctzll(a));
		if((a&7)^1)return -1;
		if(t&1)return -1;
		k-=t;
		for(int re i=4;i<=k;++i){
			res=(res+(a%(1<<i)-res*res)/2)%(1<<k);
		}
		res%=1<<k;
		if(res<0)res+=1<<k;
		return res<<(t>>1); 
	}
	
	inline ll solve_p(ll a,ll p){
		a%=p;
		if(quickpow(a,(p-1)>>1,p)==p-1)return -1;
		re ll b;
		Mod=p;
		while(true){
			b=rand()%p;
			W=(mul(b,b,p)-a+p)%p;
			if(quickpow(W,(p-1)>>1,p)==p-1)break;
		}
		re ll ans=quickpow(complex(b,1),(p+1)>>1).x;
		return min(ans,p-ans);
	}
	
	inline ll solve_pk(ll a,ll k,ll p,ll mod){
		if(a%mod==0)return 0;
		re ll t=0,hmod=1;
		while(a%p==0)a/=p,++t,hmod*=(t&1)?p:1;
		if(t&1)return -1;
		k-=t;
		mod/=hmod*hmod;
		re ll res=solve_p(a,p);
		if(res==-1)return -1;
		complex tmp(res,1);
		W=a;
		Mod=mod;
		tmp=quickpow(tmp,k);
		res=mul(tmp.x,inv(tmp.y,Mod),Mod);
		return res*hmod;
	}
	
	ll remain[20],mod[20],p;
	inline ll CRT(){
		re ll ans=0;
		for(int re i=1;i<=cntf;++i){
			ans=(ans+mul(mul(p/mod[i],inv(p/mod[i],mod[i]),p),remain[i],p))%p;
		}
		return ans;
	}
	
	inline ll solve(ll a,ll pmod){
		a%=pmod;
		cntf=0;
		p=pmod;
		sieves(pmod);
		if(cntf>1)sort(fact+1,fact+cntf+1);
		if(cntf>1)cntf=unique(fact+1,fact+cntf+1)-fact-1;
		for(int re i=1;i<=cntf;++i){
			re ll now=0,rmod=1;
			while(pmod%fact[i]==0)pmod/=fact[i],++now,rmod*=fact[i];
			mod[i]=rmod;
			if(fact[i]==2)remain[i]=solve_2k(a,now);
			else remain[i]=solve_pk(a,now,fact[i],rmod);
			if(remain[i]==-1)return -1;
		}
		return CRT();
	}
	
	#undef complex
}


//取模,返回非负数 
LL realmod(LL a,LL M){
	a%=M;
	if(a<0) a+=M;
	return a;
}
//快速幂,用普通乘法实现 
LL quickpow(LL a,LL n,LL M){
	a=realmod(a,M);
	LL ans=1;
	while(n){
		if(n&1) ans=ans*a%M;
		a=a*a%M;
		n>>=1;
	}
	return ans;
}
//乘法逆元 
LL inverse(LL a,LL p){//a对p的乘法逆元,p是素数 
	return quickpow(a,p-2,p);
}
//勒让德符号 
LL Legendre_symbol(LL a,LL p){//p是奇素数 
	//1代表a是平方剩余,-1代表a不是平方剩余,0代表a=0 
	//a^((p-1)/2)
	LL flg=quickpow(a,(p-1)/2,p);
	if(flg==0||flg==1) return flg;
	return -1;
}
//模意义平方根 
LL sqrt_mod(LL n,LL p){//解方程组x^2=n(mod p),Tonelli-Shanks算法,p是奇素数
	n=realmod(n,p);//保证n非负 
	//返回方程的一个根 
	if(Legendre_symbol(n,p)!=1) return -1;//无解
	LL S=0,Q=p-1; 
	while(!(Q&1)){
		S++;
		Q>>=1;
	}
	//现在Q是奇数,p-1=Q*2^S
	LL z;//选择一个二次非剩余z 
	while(true){
		z=rand()%p;//随机一个数,这个rand有可能太小,不知道会不会出问题 
		if(Legendre_symbol(z,p)==-1) break;
	}
	LL c=quickpow(z,Q,p),R=quickpow(n,(Q+1)/2,p),t=quickpow(n,Q,p),M=S,i,tmp,b;
	while(true){
		if(t==1) return R;
		for(i=0,tmp=t;tmp!=1;i++,tmp=tmp*tmp%p);
		b=quickpow(c,1LL<<(M-i-1),p),R=R*b%p,c=b*b%p,t=t*c%p,M=i;
	}
}
//二次同余方程 
bool quadratic_mod(LL a,LL b,LL c,LL p,LL &x1,LL &x2){//解同余方程ax^2+bx+c=0(mod p),p是奇素数 
	a=realmod(a,p),b=realmod(b,p),c=realmod(c,p);
	LL dlt=realmod(b*b%p-4*a%p*c%p,p);
	LL sd=sqrt_mod(dlt,p);
	if(sd==-1) return false;//无解
	LL inv2a=inverse(2*a,p);
	x1=realmod((-b+sd)%p*inv2a,p);
	x2=realmod((-b-sd)%p*inv2a,p);
	return true;
}
//扩展欧几里得算法 
void extend_gcd(LL a,LL b,LL &x,LL &y,LL &d){
	if(b==0){d=a;x=1;y=0;}
	else{extend_gcd(b,a%b,y,x,d);y-=(a/b)*x;}
}
vector<pair<LL,LL> > suspects;
LL C,P,ans;
void update(LL n){
	ll tmp=Find_root::solve(n,P-1);
	if (tmp==-1) return;
	if (ans==-1||ans>tmp) ans=tmp;
}
const int HSIZE=3233983;
class Node{
public:
	int s;
	LL a;
	int nxt;
};
class Hash_Map{
public:
	int head[HSIZE];
	Node lis[HSIZE];
	int tot;
	void clear(void){
		memset(head,0,sizeof(head));
		tot=0;
	}
	bool count(int s){
		int key=s%HSIZE;
		for(int x=head[key];x;x=lis[x].nxt){
			if(lis[x].s==s) return true;
		}
		return false;
	}
	LL& operator [] (int s){
		int key=s%HSIZE,x;
		for(x=head[key];x;x=lis[x].nxt){
			if(lis[x].s==s) return lis[x].a;
		}
		lis[++tot]=(Node){s,-1,head[key]};
		head[key]=tot;
		return lis[tot].a;
	}
};
Hash_Map base;
//求离散对数,大步小步算法 
void dclog(LL a,LL MOD){//求解方程:a^x=b(mod MOD),返回最小解,无解返回-1
	//采用大步小步法
	a=realmod(a,MOD);
	base.clear();
	LL m=(LL)sqrt(MOD+0.5),e=1,i,v;
	v=inverse(quickpow(a,m,MOD),MOD);
	base[1]=0;
	for(i=1;i<m;i++){
		e=(e*a)%MOD;
		if(!base.count(e)) base[e]=i;
	}
	for(i=0;i<=MOD/m;i++){
		for(LL j=0;j<suspects.size();j++){
			LL &b=suspects[j].first;
			if(base.count(b)){
				update((i*m+base[b])*2+suspects[j].second);
			}
			b=(b*v)%MOD;
		}
	}
}
void test_even(LL y,LL u){//y^n=u(mod P),n为偶数 
	LL v=sqrt_mod(u,P);
	if(v==-1) return;
	suspects.push_back(make_pair(realmod(v,P),0));
	suspects.push_back(make_pair(realmod(-v,P),0));
}
void test_odd(LL y,LL u){//y^n=u(mod P),u为奇数 
	LL v=sqrt_mod(u*inverse(y,P),P);
	if(v==-1) return;
	suspects.push_back(make_pair(realmod(v,P),1));
	suspects.push_back(make_pair(realmod(-v,P),1));
}
void work(void){
	LL x=sqrt_mod(5,P);//根号5 
	LL y=realmod((x+1)*inverse(2,P),P);
	ans=-1;
	suspects.clear();
	LL d=C*x%P,u1,u2;
	//y^n-(-1/y)%n=d
	//情况1:n是偶数 
	if(quadratic_mod(1,-d,-1,P,u1,u2)){
		test_even(y,u1);
		test_even(y,u2);
	}
	//情况2:n是奇数
	if(quadratic_mod(1,-d,+1,P,u1,u2)){
		test_odd(y,u1);
		test_odd(y,u2);
	}
	dclog(y,P);
	cout<<ans<<endl;
}
int main(void){
	int *x=new int[5];
	srand((unsigned long long)x);
	delete [] x;
	
	Linear_sieves::init();
	P=1e9+9;
	cin>>C;
	work();
	return 0;
}
