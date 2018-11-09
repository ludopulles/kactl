#include "template-no-main.h"
#include "../content/numerical/BerlekampMassey.h"

template<class F>
void gen(vector<ll>& v, int at, F f) {
	if (at == sz(v)) f();
	else {
		rep(i,0,5) {
			v[at] = i;
			gen(v, at+1, f);
		}
	}
}

int main() {
	// a_n = a_{n-1} + 2a_{n-2}
	vector<ll> v{0, 1, 1, 3, 5, 11}, rec{ 1LL, 2LL};
	auto v2 = BerlekampMassey(v);
	assert(v2 == rec);

	int nequal = 0;

	rep(n,1,5) {
		vector<ll> start(n), coef(n), coef2, full(2*n);
		gen(start, 0, [&]() {
			gen(coef, 0, [&]() {
				rep(i,0,n) full[i] = start[i];
				rep(i,n,2*n) full[i] = 0;
				rep(i,n,2*n) rep(j,0,n)
					full[i] = (full[i] + coef[j] * full[i-1 - j]) % mod;
				coef2 = BerlekampMassey(full);
				if (sz(coef2) == n) assert(coef == coef2), nequal++;
				rep(i,n,2*n) {
					ll x = 0;
					rep(j,0,sz(coef2))
						x = (x + coef2[j] * full[i-1 - j]) % mod;
					assert(x == full[i]);
				}
			});
		});
	}

	// check that this test did not succeed just because it made no assertions (see line 32), but because it actually worked :).
	assert(nequal >= 1e5);

	return 0;
}
