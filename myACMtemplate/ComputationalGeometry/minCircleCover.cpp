//三点定圆心，保证不共线
Point threePointConfirmCentre(Point a,Point b,Point c){
	return lineIntersect((a+b)/2,Rot(b-a,PI/2),(a+c)/2,Rot(c-a,PI/2));
}
//最小圆覆盖
void minCircleCover(Point p[],int n){
	random_shuffle(p+1,p+1+n);
	Point o=p[1]; double r=0; int i,j,k;
	for (i=2;i<=n;++i)
	if (Dist(o,p[i])>r)
		for (o=p[i],r=0,j=1;j<i;++j)
		if (Dist(o,p[j])>r)
			for (o=(p[i]+p[j])/2,r=Dist(o,p[i]),k=1;k<j;++k)
			if (Dist(o,p[k])>r) o=threePointConfirmCentre(p[i],p[j],p[k]),r=Dist(o,p[j]);
	printf("%.2f %.2f %.2f\n",o.x,o.y,r);
}