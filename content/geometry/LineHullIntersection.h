/**
 * Author: Johan Sannemo
 * Date: 2017-05-15
 * License: CC0
 * Source: thin air
 * Description: Line-convex polygon intersection. The polygon must be ccw and have no colinear points.
 *  isct(a, b) returns a pair describing the intersection of a line with the polygon:
 *  \begin{myitemize}
 *    \item $(-1, -1)$ if no collision,
 *    \item $(i, -1)$ if touching the corner $i$,
 *    \item $(i, i)$ if along side $(i, i+1)$,
 *    \item $(i, j)$ if crossing sides $(i, i+1)$ and $(j, j+1)$.
 *  \end{myitemize}
 *  In the last case, if a corner $i$ is crossed, this is treated as happening on side $(i, i+1)$.
 *  The points are returned in the same order as the line hits the polygon.
 * Status: fuzz-tested
 * Time: O(N + Q \log n)
 */
#pragma once

#include "Point.h"

ll sgn(ll a) { return (a > 0) - (a < 0); }
typedef Point<ll> P;
struct HullIntersection {
	int N;
	vector<P> p;
	vector<pair<P, int>> a;

	HullIntersection(const vector<P>& ps) : N(sz(ps)), p(ps) {
		p.insert(p.end(), all(ps));
		int b = 0;
		rep(i,1,N) if (P{p[i].y,p[i].x} < P{p[b].y, p[b].x}) b = i;
		rep(i,0,N) {
			int f = (i + b) % N;
			a.emplace_back(p[f+1] - p[f], f);
		}
	}

	int qd(P q) {
		return (q.y < 0) ? (q.x >= 0) + 2
		     : (q.x <= 0) * (1 + (q.y <= 0));
	}

	int bs(P dir) {
		int lo = -1, hi = N;
		while (hi - lo > 1) {
			int mid = (lo + hi) / 2;
			if (make_pair(qd(dir), dir.y * a[mid].first.x) <
				make_pair(qd(a[mid].first), dir.x * a[mid].first.y))
				hi = mid;
			else lo = mid;
		}
		return a[hi%N].second;
	}

	bool isign(P u, P v, int x, int y, int s) {
		return sgn(u.cross(p[x], v)) * sgn(u.cross(p[y], v)) == s;
	}

	int bs2(int lo, int hi, P u, P v) {
		int L = lo;
		if (hi < lo) hi += N;
		while (hi - lo > 1) {
			int mid = (lo + hi) / 2;
			if (isign(u, v, mid, L, -1)) hi = mid;
			else lo = mid;
		}
		return lo;
	}

	pii isct(P u, P v) {
		int f = bs(u - v), j = bs(v - u);
		if (isign(u, v, f, j, 1)) return {-1, -1};
		int x = bs2(f, j, u, v) % N,
		    y = bs2(j, f, u, v) % N;
		if (u.cross(p[x], v) == 0 &&
		    u.cross(p[x+1], v) == 0) return {x, x};
		if (u.cross(p[y], v) == 0 &&
		    u.cross(p[y+1], v) == 0) return {y, y};
		if (u.cross(p[f], v) == 0) return {f, -1};
		if (u.cross(p[j], v) == 0) return {j, -1};
		return {x, y};
	}
};
