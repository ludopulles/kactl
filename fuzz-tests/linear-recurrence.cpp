#include "template-no-main.h"
#include "../content/numerical/LinearRecurrence.h"

const int nsamples = 100;
const int maxn = 20;
const int maxk = 1000;

int main() {
	srand(314398763);

	// check the fibonacci sequence:
	ll a = 0, b = 1;
	for (ll k = 0; k < 10000; k++) {
		ll found = linearRec({0, 1}, {1, 1}, k);
		assert(found == a);

		if ((a += b) >= mod) a -= mod;
		swap(a, b);
	}

	int ntimes = nsamples;
	while (ntimes--) {
		// generate a sequence
		int n = rand() % maxn;
		// first n start values and multiplication coefficients
		vector<ll> start(n), coef(n);
		// populate with random values.
		rep(i,0,n) start[i] = rand() % mod, coef[i] = rand() % mod;

		vector<ll> expected(maxk, 0);
		vector<ll> actual(maxk, 0);

		rep(i, 0, n) expected[i] = start[i];
		rep(k, n, maxk)
			for (int j = 0; j < n; j++) {
				expected[k] += expected[k - j - 1] * coef[j] % mod;
				if (expected[k] >= mod) expected[k] -= mod;
			}

		rep(i, 0, maxk) actual[i] = linearRec(start, coef, i);

		vi different;
		rep(i, 0, maxk) {
			if (expected[i] != actual[i]) different.push_back(i);
		}

		if (!different.empty()) {
			cerr << "Recurrence different on " << different.size() << " places:\n";
			int nth = 0;
			bool first = true;
			cerr << " (k: actual/expected) { ";
			for (int i : different) {
				if (first) first = false; else cerr << ", ";
				cerr << i << ": " << actual[i] << "/" << expected[i];
				if (++nth >= 10) break;
			}
			if (nth >= 10) cerr << ", ...";
			cerr << " }" << endl;
		}
		assert(different.empty());
	}
	return 0;
}
