#include "template-no-main.h"
#include "../content/numerical/FastFourierTransform.h"

int main() {
	int n = 8;
	carray a(n), av(n), roots(n);
	rep(i,0,n) a[i] = rand() % 10 - 5;
	rep(i,0,n) roots[i] = polar(1.0, -2 * M_PI * i / n);
	av = a;
	fft(av, roots);
	rep(k,0,n) {
		complex<double> sum{};
		rep(x,0,n) {
			sum += a[x] * polar(1.0, -2 * M_PI * k * x / n);
		}
		cout << sum << ' ' << av[k] << endl;
	}
}
