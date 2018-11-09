#include "template-no-main.h"
#include "../content/numerical/FastFourierTransform.h"

// just one big test should be enough.
const int maxtests = 2;
const int maxn = 1 << 10;

const ll maxa = 1000 * 1000;

ll nextrand() {
	return maxa + rand() % (maxa * 2 + 1);
}

void run()
{
	vector<ll> la(maxn), lb(maxn);
	for (int i = 0; i < maxn; i++)
		la[i] = nextrand(), lb[i] = nextrand();
	
	vector<ll> expected(maxn + maxn, 0);
	rep(i,0,maxn) rep(j,0,maxn) expected[i+j] += la[i] * lb[j];

	vd alta(maxn + 100, 0), altb(maxn + 100, 0); // add some padding so we get some zeros at the end.
	rep(i, 0, maxn) alta[i] = (ld) la[i], altb[i] = (ld) lb[i];

	vd found = conv(alta, altb);

	ld max_abs_diff = 0.0;
	ld max_rel_diff = 0.0;
	rep(i, 0, maxn + maxn - 1) {
		ld err = fabs(expected[i] - found[i]);
		max_abs_diff = max(max_abs_diff, err);
		max_rel_diff = max(max_rel_diff, err / (ld) expected[i]);
	}

	cerr << "Max absolute difference: " << max_abs_diff << endl;
	cerr << "Max relative difference: " << max_rel_diff << endl;

	assert(max_abs_diff < 5.0);
	assert(max_rel_diff < 1e-10);
}

int main()
{
	cerr.precision(10);
	srand(87645412);

	// our test should not give overflows
	assert(maxa * maxa * maxn < LLINF);

	for (int i = 0; i < maxtests; i++) run();
	return 0;
}
