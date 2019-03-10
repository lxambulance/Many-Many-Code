ll gcd(ll a,ll b){ return b==0?a:gcd(b,a%b); }
ll pollard_rho(ll x,int c){
    ll a=2,b=2;
    do{
        a=(qmul(a,a,x)+c)%x;
        b=(qmul(b,b,x)+c)%x;
        b=(qmul(b,b,x)+c)%x;
        ll p=gcd(abs(a-b),x);
        if (p!=1&&p!=x) return p;
    }while(a!=b);
    return x;
}
vector<ll> ans;
void factorFind(ll x,int c){
    if (x==1) return;
    if (isprime(x)) { ans.push_back(x); return; }
    ll p=x,k=c;
    while (p>=x) p=pollard_rho(p,c--);
    factorFind(p,k); factorFind(x/p,k);
}
void solve(ll x){
    ans.clear();
    factorFind(x,110);
    sort(ans.begin(),ans.end());
    int tot=ans.size();
    for (int i=0;i<tot;++i) {
        printf("%lld ",ans[i]);
        if (i+1<tot) printf("* "); else printf("= ");
    }
    printf("%lld\n",x);
}
