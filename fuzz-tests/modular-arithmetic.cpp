#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < int(b); ++i)
#define trav(it, v) for(auto& it : v)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

#include "../content/number-theory/ModularArithmetic.h"

const int maxtests = 10000;

#define TESTMOD(m) { rep(_,0,maxtests) { \
			ll a = rand() % (m), b = rand() % (m); \
			if (maxtests < 100) \
				a = ((_ / 10) + (m) - 5) % (m), \
				b = ((_ % 10) + (m) - 5) % (m); \
			Mod<(m)> ma(a), mb(b); \
			Mod<(m)> addsub = ma - mb + ma + mb - ma; \
			assert(("add and subtract", addsub.x == ma.x)); \
			if (b == 0LL) continue; \
			Mod<(m)> mc = ma / mb; \
			assert(("check division", (mc * mb).x == a)); \
			mc = mc * mb; \
			assert(("check going back", mc.x == ma.x)); \
			mc = mc + Mod<(m)>(135); \
			Mod<(m)> found = mc * (mb * mb) * mb / mb / (mb * mb); \
			assert(("check lots", found.x == mc.x)); \
		} \
		Mod<(m)> base = 2; \
		ll expected = 1; \
		rep(i, 0, 100) { \
			Mod<(m)> actual = base ^ i; \
			assert(("check power", actual.x == expected)); \
			expected = (expected + expected) % (m); \
		} \
	}

const ll commonmod = 1e9 + 7;

int main() {
	srand(2938271);

	TESTMOD(2);
	TESTMOD(3);
	TESTMOD(17);
	TESTMOD(962592769);
	TESTMOD(970592641);
	TESTMOD(commonmod);
	TESTMOD(commonmod + 2);

	return 0;
}
