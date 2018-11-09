#include "template-no-main.h"
#include "../content/numerical/NumberTheoreticTransform.h"

// warning: use nmod since this is defined in NTT, while mod was defined for a fast modpow

vl simpleConv(vl a, vl b) {
	if (a.empty() || b.empty()) return {};
	int s = sz(a) + sz(b) - 1;
	vl c(s);
	rep(i,0,sz(a)) rep(j,0,sz(b))
		c[i+j] = (c[i+j] + a[i] * b[j]) % nmod;
	trav(x, c) if (x < 0) x += nmod;
	return c;
}

int main() {
	srand(397862876);
	vl a, b;

	// small samples. (~0.3s)
	rep(it,0,100000) {
		a.resize(1 + (rand() % 10));
		b.resize(1 + (rand() % 10));

		// popoluate a, b
		trav(x, a) x = rand() % 100 - 50;
		trav(x, b) x = rand() % 100 - 50;

		// calculate convolutions:
		vl expected = simpleConv(a, b);
		vl actual = conv(a, b);
	
		assert(expected == actual);
	}

	// big samples (~0.3s)
	rep(it,0,100) {
		a.resize(1 + (rand() % 1000));
		b.resize(1 + (rand() % 1000));

		// popoluate a, b
		trav(x, a) x = rand() % 100000 - 50000;
		trav(x, b) x = rand() % 100000 - 50000;

		// calculate convolutions:
		vl expected = simpleConv(a, b);
		vl actual = conv(a, b);
	
		assert(expected == actual);
	}




	return 0;
}
