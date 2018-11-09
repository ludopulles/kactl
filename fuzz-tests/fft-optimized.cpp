#include "template-no-main.h"
#include "../content/numerical/FFTOptimized.h"

// As a comparison:
#include "../content/numerical/FastFourierTransform.h"

// just one big test should be enough.
const int maxtests = 1;

/**
 * The FFT supports up to 1 << 19
 * but calculating the convolution naively is O(N^2)
 * thus we have to settle for a smaller value.
 */
const int maxn = 1 << 10;

const ll maxa = 1000 * 1000;

ll nextrand()
{
	return maxa + rand() % (maxa * 2 + 1);
}

void run()
{
	vector<ll> la(maxn), lb(maxn);
	for (int i = 0; i < maxn; i++)
		la[i] = nextrand(), lb[i] = nextrand();
	
	vector<ll> expected(maxn + maxn, 0);
	rep(i,0,maxn) rep(j,0,maxn) expected[i+j] += la[i] * lb[j];

	cpx *a = new cpx[MAXN], *b = new cpx[MAXN];

	rep(i, 0, MAXN)
		a[i] = cpx(i<maxn ? la[i] : 0, 0), b[i] = cpx(i<maxn ? lb[i] : 0, 0);

	multiply(a, b);

	ld max_abs_diff = 0.0;
	ld max_rel_diff = 0.0;
	rep(i, 0, maxn + maxn - 1) {
		ld err = fabs(expected[i] - a[i].real());
		max_abs_diff = max(max_abs_diff, err);
		max_rel_diff = max(max_rel_diff, err / (ld) expected[i]);
	}

	cerr << "Max absolute difference: " << max_abs_diff << endl;
	cerr << "Max relative difference: " << max_rel_diff << endl;

	assert(max_abs_diff < 5.0);
	assert(max_rel_diff < 1e-10);


	// compare to other FFT

	vd alta(maxn + 100, 0), altb(maxn + 100, 0); // add some padding so we get some zeros at the end.
	rep(i, 0, maxn) alta[i] = (ld) la[i], altb[i] = (ld) lb[i];
	vd altc = conv(alta, altb);

	max_rel_diff = 0.0;
	rep(i, 0, maxn + maxn - 1) {
		ld err = fabs(altc[i] - a[i].real());
		max_rel_diff = max(max_rel_diff, err / altc[i]);
	}

	assert(max_rel_diff < 1e-12);

	// Past maxn+maxn-1, everything should be zero, except that,
	// well, FFT is just FFT. There is some random noise after the main-coefficient of the product
	// If you use the FFT, do NEVER read anything from the output after the leading-coefficient. Please don't.
	rep(i, maxn + maxn - 1, 1 << 19)
		if (fabs(a[i].real()) > 1.5 || fabs(a[i].imag()) > 1.5) assert(false);
	
	delete[] a;
	delete[] b;
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
