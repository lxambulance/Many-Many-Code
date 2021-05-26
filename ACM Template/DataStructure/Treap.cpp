mt19937 rng((uint64_t) new char);
struct TreapNode{
	int l,r; //该节点左右儿子
	int val,rnd; //该节点的值和随机堆值
	int ns,sz; //分别记录当前值val有几个（ns->nowsize），以及已该节点为根的子树大小（sz->size）
}T[MAXN];
int root,top,pool[MAXN];
void rturn(int &k){
	int t=T[k].l; T[k].l=T[t].r; T[t].r=k;
	T[t].sz=T[k].sz; T[k].sz=T[T[k].l].sz+T[T[k].r].sz+T[k].ns;
	k=t;
}
void lturn(int &k){
	int t=T[k].r; T[k].r=T[t].l; T[t].l=k;
	T[t].sz=T[k].sz; T[k].sz=T[T[k].l].sz+T[T[k].r].sz+T[k].ns;
	k=t;
}
void Tree_ins(int &k,int x){
	if (k==0) { 
		k=pool[top--];
		T[k].l=T[k].r=0; T[k].sz=T[k].ns=1; T[k].val=x; T[k].rnd=(int)rng();
		return;
	}
	T[k].sz++;
	if (T[k].val==x)T[k].ns++;
	else if (x>T[k].val) {
		Tree_ins(T[k].r,x);
		if (T[T[k].r].rnd<T[k].rnd) lturn(k);
	}
	else {
		Tree_ins(T[k].l,x);
		if (T[T[k].l].rnd<T[k].rnd) rturn(k);
	}
}
void Tree_del(int &k,int x){
	if (k==0) return; 
	if (T[k].val==x) {
		if (T[k].ns>1) { T[k].ns--; T[k].sz--; return; }
		if (T[k].l*T[k].r==0) { pool[++top]=k; k=T[k].l+T[k].r; }
		else if (T[T[k].l].rnd<T[T[k].r].rnd) rturn(k),Tree_del(k,x);
		else lturn(k),Tree_del(k,x);
	}
	else if (x>T[k].val) T[k].sz--,Tree_del(T[k].r,x);
	else T[k].sz--,Tree_del(T[k].l,x);
}
int query_rank(int k,int x){
	if (k==0) return 0;
	if (T[k].val==x) return T[T[k].l].sz+1;
	else if(x>T[k].val) return T[T[k].l].sz+T[k].ns+query_rank(T[k].r,x);
	else return query_rank(T[k].l,x);
}
int query_num(int k,int x){
	if (k==0) return 0;
	if (x<=T[T[k].l].sz) return query_num(T[k].l,x);
	else if(x>T[T[k].l].sz+T[k].ns) return query_num(T[k].r,x-T[T[k].l].sz-T[k].ns);
	else return T[k].val;
}
int ans;
void query_pro(int k,int x){
	if (k==0) return;
	if (T[k].val<x) { ans=k; query_pro(T[k].r,x); }
	else query_pro(T[k].l,x);
}
//result in ans
void query_sub(int k,int x){
	if (k==0) return;
	if (T[k].val>x) { ans=k; query_sub(T[k].l,x); }
	else query_sub(T[k].r,x);
}
//result in ans
int query_max(int k){
	while (T[k].r>0) k=T[k].r;
	return T[k].val;
}
int query_min(int k){
	while (T[k].l>0) k=T[k].l;
	return T[k].val;
}