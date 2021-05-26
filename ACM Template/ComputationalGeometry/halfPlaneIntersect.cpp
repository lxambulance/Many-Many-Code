struct line{
	Point p;
	Vector v;
}l[MAXN];
Point lI(line l1,line l2){ return lineIntersect(l1.p,l1.v,l2.p,l2.v); }
bool onRight(Point p,line l){ return sgn(l.v*(p-l.p))<0; }
//相同极角保留最靠左的，排序中体现为相同极角的第一个
int cmp(line l1,line l2){
	int f1=(l1.v.x>=-eps),f2=(l2.v.x>=-eps);
	if (f1!=f2) return f1==1;
	int tmp=sgn(l1.v*l2.v);
	return (tmp==0&&sgn(l1.v*(l2.p-l1.p))<0)||tmp>0;
}
void checkCounterclockwise(Point p[],int n){
	double area=0;
	p[n+1]=p[1];
	FOR(i,1,n) area+=p[i+1]*p[i];
	if (sgn(area)==1)
		FOR(i,1,n/2) swap(p[i],p[n+1-i]);
}
int head,tail;
line que[MAXN];
bool HPI(Point p[],int n){
	p[n+1]=p[1];
	FOR(i,1,n) l[i].p=p[i],l[i].v=p[i+1]-p[i];
	sort(l+1,l+1+n,cmp);
	int N=n; n=0;
	FOR(i,1,N) {
		if (i>1&&sgn(l[i].v*l[i-1].v)==0) continue;
		l[++n]=l[i];
	}
	head=1,tail=0;
	//FOR(i,1,n) printf("(%.8f,%.8f) vector(%.8f,%.8f)\n",l[i].p.x,l[i].p.y,l[i].v.x,l[i].v.y);
	FOR(i,1,n) {
		while (tail>head&&onRight(lI(que[tail],que[tail-1]),l[i])) tail--;
		while (tail>head&&onRight(lI(que[head],que[head+1]),l[i])) head++;
		que[++tail]=l[i];
	}
	while (tail>head&&onRight(lI(que[tail],que[tail-1]),que[head])) tail--;
	while (tail>head&&onRight(lI(que[head],que[head+1]),que[tail])) head++;
	if (tail-head+1>=3) return true;
	return false;
}