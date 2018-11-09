#include "template-no-main.h"
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
