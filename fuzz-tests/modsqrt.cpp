#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < int(b); ++i)
#define trav(a, v) for(auto& a : v)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

ll modpow(ll a, ll e, ll mod) {
	assert(e >= 0);
	if (e == 0) return 1;
	ll x = modpow(a * a % mod, e >> 1, mod);
	return e & 1 ? x * a % mod : x;
}

#include "../content/number-theory/ModSqrt.h"

const int MAXN = 10 * 1000;
bitset<MAXN> isprime;

int main() {
	isprime.set();
	rep(p, 2, MAXN) {
		if (!isprime.test(p)) continue;

		// unset all multiples of p
		for (int j = p * p; j < MAXN; j += p) isprime.set(j, false);

		rep(a, 0, p) {
			int sq = a * a % p;
			ll found = sqrt(sq, p);
			assert(0 <= found && found < p && (found == a || found == p - a));
		}
	}
}
