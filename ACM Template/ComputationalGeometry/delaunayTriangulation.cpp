namespace delaunay{
const int MAXN=1003;
Point p[MAXN];
int n,esize,u[MAXN],q[MAXN];
struct edge{ int v,nt,pr; }e[MAXN*10];
void clear(){
	sort(p+1,p+1+n);
	esize=0; memset(u,-1,sizeof(u));
}
void addEdge(int x,int y){
	e[esize]=(edge){y,u[x],-1}; e[u[x]].pr=esize; u[x]=esize++;
	e[esize]=(edge){x,u[y],-1}; e[u[y]].pr=esize; u[y]=esize++;
}
void delEdge(int w){
	if (~e[w].pr) e[e[w].pr].nt=e[w].nt;
	if (~e[w].nt) e[e[w].nt].pr=e[w].pr;
	if (u[e[w^1].v]==w) u[e[w^1].v]=e[w].nt;
}
bool inCir(Point p,Point a,Point b,Point c){
	Point o=lineIntersect((a+b)/2,Rot(b-a,PI/2),(a+c)/2,Rot(c-a,PI/2));
	return Dist(o,p)<=Dist(o,a)+eps;
}
void triangulation(int l,int r){
	if (r-l<=2) {
		if (l!=r)
			FOR(i,l,r-1) addEdge(i,i+1);
		if (r-l==2) addEdge(l,r);
		return;
	}
	int mid=(l+r)/2;
	triangulation(l,mid),triangulation(mid+1,r);
	int h=0;
	FOR(i,l,r) {
		while (h>1&&Cross(p[q[h]],p[i],p[q[h-1]])<=eps) h--;
		q[++h]=i;
	}
	int ld=0,rd=0;
	FOR(i,1,h) {
		if (q[i]<=mid) ld=q[i];
		if (!rd&&q[i]>mid) rd=q[i];
	}
	addEdge(ld,rd);
	while (1) {
		int d=0;
		for (int i=u[ld];~i;i=e[i].nt)
		if ((Cross(p[rd],p[e[i].v],p[ld])>eps)&&(!d||inCir(p[e[i].v],p[d],p[ld],p[rd]))) d=e[i].v;
		for (int i=u[rd];~i;i=e[i].nt)
		if ((Cross(p[ld],p[e[i].v],p[rd])<-eps)&&(!d||inCir(p[e[i].v],p[d],p[ld],p[rd]))) d=e[i].v;
		if (!d) break;//return;
		if (d<=mid) {
			addEdge(d,rd);
			for (int i=u[ld];~i;i=e[i].nt)
			if (segIntersect(p[ld],p[e[i].v],p[d],p[rd])==1) delEdge(i),delEdge(i^1);
			ld=d;
		}
		else {
			addEdge(ld,d);
			for (int i=u[rd];~i;i=e[i].nt)
			if (segIntersect(p[rd],p[e[i].v],p[ld],p[d])==1) delEdge(i),delEdge(i^1);
			rd=d;
		}
	}
	// printf("working(%d,%d)\n",l,r);
	// FOR(i,l,r) {
		// printf("%d:",i);
		// for (int j=u[i];~j;j=e[j].nt) printf("%d,",e[j].v);
		// printf("\n");
	// }
}
}