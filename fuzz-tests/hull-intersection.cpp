#include "template-no-main.h"
#include "../content/geometry/Point.h"

#include "../content/geometry/ConvexHull.h"
#include "../content/geometry/SegmentIntersectionQ.h"
// #include "../content/geometry/PointInsideHull.h"
#include "../content/geometry/LineHullIntersection.h"

typedef Point<double> PD;
PD toPD(P p) { return PD(p.x, p.y); }

int segmentIntersection(const P& s1, const P& e1,
		const P& s2, const P& e2, PD& r1, PD& r2) {
	if (e1 == s1) {
		if (e2 == s2) {
			if (e1 == e2) {
				r1 = toPD(e1); //all equal
				return 1;
			} else return 0; //different point segments
		} else return segmentIntersection(s2,e2,s1,e1,r1,r2);//swap
	}
	//segment directions and separation
	P v1 = e1-s1, v2 = e2-s2, d = s2-s1;
	auto a = v1.cross(v2), a1 = v1.cross(d), a2 = v2.cross(d);
	if (a == 0) { //if parallel
		auto b1=s1.dot(v1), c1=e1.dot(v1),
		     b2=s2.dot(v1), c2=e2.dot(v1);
		if (a1 || a2 || max(b1,min(b2,c2))>min(c1,max(b2,c2)))
			return 0;
		r1 = toPD(min(b2,c2)<b1 ? s1 : (b2<c2 ? s2 : e2));
		r2 = toPD(max(b2,c2)>c1 ? e1 : (b2>c2 ? s2 : e2));
		return 2-(r1==r2);
	}
	if (a < 0) { a = -a; a1 = -a1; a2 = -a2; }
	if (0<a1 || a<-a1 || 0<a2 || a<-a2)
		return 0;
	r1 = toPD(s1) - toPD(v1*a2)/(double)a;
	return 1;
}

int main() {
	srand(2);
	rep(it,0,1000000) {
		// if (it % 100 == 0) cerr << '.';
		int N = rand() % 15;
		vector<P> ps, ps2;
		rep(i,0,N) ps2.emplace_back(rand() % 20 - 10, rand() % 20 - 10);
		trav(i, convexHull(ps2)) ps.push_back(ps2[i]);
		if (ps.empty()) continue;
		P p{rand() % 20 - 10, rand() % 20 - 10};
		P q{rand() % 20 - 10, rand() % 20 - 10};

		HullIntersection hi(ps);
		N = sz(ps);

		P delta = q - p, farp = p - delta * 50, farq = p + delta * 50;

		pii r = hi.isct(p, q);

		if (p == q) continue;

		auto fail = [&](int line) {
			cerr << sz(ps) << endl;
			trav(pt, ps) cout << pt.x << ' ' << pt.y << endl;
			cout << p.x << ' ' << p.y << ' ' << q.x << ' ' << q.y << endl << endl;
			cout << "-> " << r.first << ' ' << r.second << endl;
			cout << "@line " << line << endl;
			abort();
		};
#define FAIL() fail(__LINE__)

		int any = 0, gen = 0, corner = -1, waspar = 0;
		vector<pair<PD, int>> hits;
		rep(iter,0,2) rep(i,0,N) {
			PD r1, r2;
			int j = (i+1) % N;
			int qu = segmentIntersection(farp, farq, ps[i], ps[j], r1, r2);
			if (qu && (q - p).cross(ps[j] - ps[i]) == 0) { // parallel
				if (N != 2) {
					if (!(r.first == i || r.second == i)) FAIL();
				}
				// cerr << i << ' ' << j << ' ' << r.first << ' ' << r.second << endl;
				// assert(r.first == i && r.second == j);
				any = 1;
				if (iter == 0) gen = 10;
				waspar = 1;
			} else if (qu) {
				assert(qu != 2);
				if (r1 == toPD(ps[i])) {
					int k = (i-1+N) % N;
					if (!(r.first == i || r.second == i || r.first == k || r.second == k)) FAIL();
					if (iter == 1 && !waspar && !(r.first == i || r.second == i)) FAIL();
					if (iter == 0) corner = i;
					if (iter == 0) gen++;
					if (iter == 0) hits.emplace_back(r1, i);
				} else if (r1 == toPD(ps[j])) {
					if (!(r.first == i || r.second == i || r.first == j || r.second == j)) FAIL();
					if (iter == 1 && !waspar && !(r.first == j || r.second == j)) FAIL();
					if (iter == 0) corner = j;
					if (iter == 0) gen++;
				} else {
					if (!(r.first == i || r.second == i)) FAIL();
					if (iter == 0) gen = 10;
					if (iter == 0) hits.emplace_back(r1, i);
				}
				any = 1;
			}
		}

		if (!any) {
			assert(r.first == -1 && r.second == -1);
			continue;
		}
		if (!waspar) assert(r.first != r.second);
		if (gen == 2) {
			assert(r.first == corner);
			if (r.second != -1) FAIL();
		}
		if (N > 2 && (sz(hits) == 1) != (r.second == -1 || r.first == r.second)) FAIL();
		assert(sz(hits) <= 2);
		if (r.first != r.second && sz(hits) == 2) {
			assert(r.second != -1);
			assert(hits[0].second != hits[1].second);
			assert(hits[0].second == r.first || hits[0].second == r.second);
			assert(hits[1].second == r.first || hits[1].second == r.second);
			double dist0 = (hits[0].first - toPD(p)).dot(toPD(delta));
			double dist1 = (hits[1].first - toPD(p)).dot(toPD(delta));
			if (hits[0].second == r.first) {
				if (!(dist0 <= dist1)) FAIL();
			}
			else {
				if (!(dist0 >= dist1)) FAIL();
			}
		}

		pii R = hi.isct(q, p);
		if (r.second == -1) {
			assert(R == r);
		}
		else if (N == 2 && r.first == r.second) {
			assert(R.first == R.second);
		}
		else {
			assert(R.first == r.second);
			assert(R.second == r.first);
		}
	}
}
