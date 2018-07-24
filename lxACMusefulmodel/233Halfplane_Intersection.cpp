#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;

struct point {
	double x, y;
}p[105], tmp[105], q[105];

double a, b, c;
void get_line(point p1, point p2) {
	a = p2.y - p1.y;
	b = p1.x - p2.x;
	c = p2.x * p1.y - p2.y * p1.x;
}
point intersect(point p1, point p2)
{
	double u = fabs(a * p1.x + b * p1.y + c);
	double v = fabs(a * p2.x + b * p2.y + c);
	point ret;
	ret.x = (v * p1.x + u * p2.x) / (u + v);
	ret.y = (v * p1.y + u * p2.y) / (u + v);
	return ret;
}
int n, m;
void cut() {
	int i, tm = 0;
	for(i = 1; i <= m; i++)
	{
		if(a * q[i].x + b * q[i].y + c >= 0)
			tmp[++tm] = q[i];
		else
		{
			if(a * q[i-1].x + b * q[i-1].y + c > 0)
				tmp[++tm] = intersect(q[i-1], q[i]);
			if(a * q[i+1].x + b * q[i+1].y + c > 0)
				tmp[++tm] = intersect(q[i], q[i+1]);
		}
	}
	for(i = 1; i <= tm; i++)
		q[i] = tmp[i];
	q[0] = q[tm];
	q[tm+1] = q[1];
	m = tm;
}
void solve() {
	int i, j;
	for(i = 1; i <= n; i++)
		q[i] = p[i];
	q[0] = q[n];
	q[n+1] = q[1];
	p[n+1] = p[1];
	m = n;
	for(i = 1; i <= n; i++)
	{
		get_line(p[i], p[i+1]);
		cut();
	}
}

int main() {
	int i, j, cas;
	scanf("%d", &cas);
	while( cas--)
	{
		scanf("%d", &n);
		for(i = 1; i <= n; i++)
			scanf("%lf%lf", &p[i].x, &p[i].y);

		solve();
		puts(m ? "YES" : "NO");
	}
	return 0;
}
