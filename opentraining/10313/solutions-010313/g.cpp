/*
 *  Task:    Ant
 *  Author:  George Beloshapko
 *  Verdict: Accepted
 *  Comment: analytical solution in O(1) time and space
 */
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>
using namespace std;
#if defined(ILIKEGENTOO)
void E(){}template<class A,class...B>void E(A _,B...$){cerr<<' '<<_;E($...);}
#define E($...) E(#$,'=',$,'\n')
#else
#define E($...) ;
#endif
#define all(x) begin(x), end(x)
struct ${$(){cin.sync_with_stdio(false);cin.tie(nullptr);
#if !defined(ILIKEGENTOO)
freopen("input.txt", "r", stdin);freopen("output.txt", "w", stdout);
#endif
}}$;

using flt = double;

// length of parabolic arc between x=0 and x=x0
flt arc(flt a, flt x0) {
	assert(a > 0 && x0 >= 0);
	flt f = 1 / (4 * a), h = x0 / 2, q = hypot(f, h);
	return h * q / f + f * log((h + q) / f);
}

// length of parabolic arc between x=x0 and x=x1
flt arc(flt a, flt x0, flt x1) {
	assert(x1 >= x0);
	return arc(a, x1) - arc(a, x0);
}

// length of path following arc on the first parabola, then straight line, finally arc on the second parabola
flt arcLineArc(const flt (&a)[2], const flt (&bx)[2], flt h, flt v) {
	/* a: parabolic coeffs, bx: parabolic x-halfsizes,
	 * h: x-distance between parabola vertices, v: y-distance between parabola vertices
	 * line must be tangental to both parabolas (derivatives at tangency points equal to each other and line lean)
	 * let q[i] be the x-distance from parabola vertex to tangency point
	 * we have the following equations:
	 * 2 * a[0] * q[0] = 2 * a[1] * q[1] = (a[0] * q[0] * q[0] + a[1] * q[1] * q[1] + v) / (q[0] + q[1] - h)
	 * substitute z = a[0] * q[0] and A = 1 / a[0] + 1 / a[1]:
	 * A * z * z - 2 * h * z - v = 0
	 */
	flt A = 1 / a[0] + 1 / a[1];
	flt D = h * h + A * v;
	if (D <= 0)
		// parabolas intersect: no path
		return numeric_limits<flt>::infinity();
	flt z = (h + sqrt(D)) / A;
	flt q[2] = {z / a[0], z / a[1]};
	if (q[0] >= bx[0] || q[1] >= bx[1])
		// one of the arcs is negative: path should be arcLine
		return numeric_limits<flt>::infinity();
	return arc(a[0], q[0], bx[0]) + hypot(A * z - h, A * z * z + v) + arc(a[1], q[1], bx[1]);
}

// length of path following arc on the parabola and then straight line
flt arcLine(const flt (&a)[2], const flt (&bx)[2], flt h, flt v) {
	/* a: parabolic coeffs, bx: parabolic x-halfsizes,
	 * h: x-distance between parabola vertex and endpoint, v: y-distance between parabola vertex and endpoint
	 * line must be tangental to the parabola (derivative at tangency point equal to line lean)
	 * let q be the x-distance from parabola vertex to tangency point
	 * we have the following equation:
	 * 2 * a[0] * q = (a[0] * q * q + v) / (q - h)
	 * substitute z = a[0] * q and A = 1 / a[0]:
	 * A * z * z - 2 * h * z - v = 0
	 */
	flt A = 1 / a[0];
	flt D = h * h + A * v;
	assert(D > 0); // endpoint is outside the parabola
	flt z = (h + sqrt(D)) / A;
	flt q = z / a[0];
	if (z <= a[1] * bx[1] || q >= bx[0])
		// line intersects second parabola or arc is negative: path should be arcLineArc or line
		return numeric_limits<flt>::infinity();
	return arc(a[0], q, bx[0]) + hypot(A * z - h, A * z * z + v);
}

// length of path which is straight line between endpoints
flt line(const flt (&a)[2], const flt (&bx)[2], flt h, flt v) {
	/* a: parabolic coeffs, bx: parabolic x-halfsizes,
	 * h: x-distance between endpoints, v: y-distance between endpoints
	 */
	flt z = v / -h / 2;
	if (z <= a[0] * bx[0] || z <= a[1] * bx[1])
		// line intersects one of the parabolas: path should be arcLine
		return numeric_limits<flt>::infinity();
	return hypot(h, v);
}

// length of shortest path from the start of the first parabola to the end of the second
flt path(const flt (&a)[2], const flt (&bx)[2], flt h, flt v) {
	// a, bx, h, v: as in arcLineArc
	const flt ra[2] = {a[1], a[0]}, rbx[2] = {bx[1], bx[0]};
	return min({
		arcLineArc(a, bx, h, v),
		arcLine(a, bx, h - bx[1], v + a[1] * bx[1] * bx[1]),
		arcLine(ra, rbx, h - bx[0], v + a[0] * bx[0] * bx[0]),
		line(a, bx, h - bx[0] - bx[1], v + a[0] * bx[0] * bx[0] + a[1] * bx[1] * bx[1]),
	});
}

// length of the shortest path in the general case
flt solve(const flt (&as)[2], const flt (&bs)[2], const flt (&cs)[2], flt d) {
	const flt a[2] = {-as[0], as[1]}, bx[2] = {sqrt(cs[0] / a[0]), sqrt((1 - cs[1]) / a[1])};
	flt h = abs(bs[0] - bs[1]), v = cs[1] - cs[0];
	h -= floor(h / d) * d;
	assert(a[0] > 0 && a[1] > 0 && bx[0] > 0 && bx[1] > 0 && 0 <= h && h < d && -1 < v && v < 1);

	if (2 * bx[0] >= d || 2 * bx[1] >= d)
		// parabolas fully cover one of the sides
		return numeric_limits<flt>::infinity();
	if (h >= bx[0] + bx[1] || d - h >= bx[0] + bx[1])
		// straight vertical path
		return 1;
	return min(path(a, bx, h, v), path(a, bx, d - h, v));
}

int main() {
	flt a[2], b[2], c[2], d;
	cin >> d;
	for (int i = 0; i < 2; ++i)
		cin >> a[i] >> b[i] >> c[i];
	flt ans = solve(a, b, c, d);
	if (isinf(ans))
		ans = -1;
	cout << fixed << setprecision(9) << ans << '\n';
	return 0;
}
