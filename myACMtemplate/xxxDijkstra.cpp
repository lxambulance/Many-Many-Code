struct list{
	LL l,lt[MAXN],nt[MAXN<<1],x[MAXN<<1],y[MAXN<<1];
	inline void clear() { l=0; memset(lt,0,sizeof(lt)); }
	inline void addedge(LL u,LL v,LL w) { nt[++l]=lt[u]; lt[u]=l; x[l]=v; y[l]=w; }
}E;
struct Heap {  
	LL d,u;
	bool operator <(const Heap &tmp)const{ return d>tmp.d; }
};
void Dijkstra(LL st) { 
	memset(done,0,sizeof(done));  
	for (int i=1;i<=n;++i) d[i]=n*1000000LL; d[st]=0;
	priority_queue<Heap> Q; Q.push((Heap){0,st});
	while (!Q.empty()) {
		Heap t=Q.top(); Q.pop();
		LL u=t.u;
		if (done[u]) continue;
		done[u]=true;
		for (LL i=E.lt[u];i;i=E.nt[i]) {
			LL v=E.x[i],tmp=d[u]+E.y[i];
			if (d[v]>tmp) {
				d[v]=tmp;
				Q.push((Heap){tmp,v});
			}
		}
	}
}