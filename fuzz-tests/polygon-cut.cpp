#include "template-no-main.h"
#include "../content/geometry/PolygonArea.h"
#include "../content/geometry/PolygonCut.h"
#include "../content/geometry/sideOf.h"
#include "../content/geometry/insidePolygon.h"
#include "../content/geometry/SegmentIntersection.h"

typedef Point<double> P;

const int nruns = 500;
const double accuracy = 0.05;

// returns if I make it to the end
bool run()
{
	int N = rand() % 10 + 3;
	vector<P> ps;
	rep(i,0,N) ps.emplace_back(rand() % 10 - 5, rand() % 10 - 5);
	P p(rand() % 10 - 5), q(rand() % 10 - 5);
	rep(i,0,N) rep(j,i+1,N) {
		P a = ps[i], b = ps[(i+1)%N];
		P c = ps[j], d = ps[(j+1)%N];
		P r1, r2;
		int r = segmentIntersection(a, b, c, d, r1, r2);
		if (r == 2) return false;
		if (r == 1) {
			if (i+1 == j || (j+1) % N == i) ;
			else return false;
		}
	}
	if (p == q) return false;

	int count = 0;
	const int ITS = 400000;
	rep(it,0,ITS) {
		double x = rand() / (RAND_MAX + 1.0) * 10 - 5;
		double y = rand() / (RAND_MAX + 1.0) * 10 - 5;
		if (!insidePolygon(all(ps), P{x,y}, true)) continue;
		if (sideOf(p, q, P{x,y}) > 0) continue;
		count++;
	}
	double expected = (double)count / ITS * 100;

	ps = polygonCut(ps, p, q);
	double actual = ps.empty() ? 0.0 : abs(polygonArea2(ps) / 2.0);

	double abserror = abs(expected - actual);
	double relerror = abserror / expected;
	double err = min(abserror, relerror);

	if (err >= accuracy) {
		(cerr << fixed).precision(5);
		cerr << "BAD ACCURACY: expected: " << expected << ", actual: " << actual << " (err = " << err << ")" << endl;
	}

	assert(err < accuracy);
	return true;
}

int main() {
	rep(_, 0, nruns) run();
}
