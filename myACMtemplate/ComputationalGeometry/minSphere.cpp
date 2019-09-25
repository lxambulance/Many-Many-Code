//三点定球心，保证不共线
P3 threeP3ConfirmSphere(P3 a,P3 b,P3 c){
	V3 f=Cross(b,c,a);
	P3 abm=(a+b)/2,acm=(a+c)/2,ret;
	lineIntersect(abm,f*(b-a),acm,f*(c-a),ret);
	return ret;
}
//四点定球心
P3 fourP3ConfirmSphere(P3 a,P3 b,P3 c,P3 d){
	if (!sgn(mixP(a,b,c,d))) return threeP3ConfirmSphere(a,b,c);
	P3 o=threeP3ConfirmSphere(a,b,c),f=Cross(b,c,a),adm=(a+d)/2;
	double tmp=-((o-adm)^(d-a))/(f^(d-a));
	return o+f*tmp;
}
//最小球覆盖
void minSphere(P3 p[],int n){
	random_shuffle(p+1,p+1+n);
	P3 o=p[1]; double r=0; int i,j,k,l;
	for (i=2;i<=n;++i)
	if (Dist(o,p[i])>r+eps)
		for (o=p[i],r=0,j=1;j<i;++j)
		if (Dist(o,p[j])>r+eps)
			for (o=(p[i]+p[j])/2,r=Dist(o,p[i]),k=1;k<j;++k)
			if (Dist(o,p[k])>r+eps)
				for (o=threeP3ConfirmSphere(p[i],p[j],p[k]),r=Dist(o,p[j]),l=1;l<k;++l)
				if (Dist(o,p[l])>r+eps) o=fourP3ConfirmSphere(p[i],p[j],p[k],p[l]),r=Dist(o,p[k]);
	printf("%.5f\n",r);
}
