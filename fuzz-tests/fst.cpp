#include "template-no-main.h"
#include "../content/numerical/FastSubsetTransform.h"

const int maxk = 10, reps = 25;
const int minval = -100, maxval = 100;

int nextrand() {
	return minval + rand() % (maxval - minval + 1);
}

int main() {
	srand(987632163);

	// -1: AND, 0: OR, 1: XOR
	for (int op : { -1, 0, 1 }) {
		rep(_, 0, reps) rep(k, 0, maxk) {
			int sz = 1 << k;
			vi a(sz), b(sz);

			// initialize with random data:
			rep(i,0,sz) a[i] = nextrand(), b[i] = nextrand();

			// do it the brute-force way:
			vi expected(sz, 0);
			rep(i,0,sz) rep(j,0,sz) {
				int ij = op < 0 ? (i&j) : op ? (i|j) : i^j;
				expected[ij] += a[i] * b[j];
			}

			// test the function
			vi c = conv(a, b, op);

			// compare results.
			assert(c == expected);
		}
	}
}
