/**
 * Author: Ludo Pulles
 * Date: 2018-11-07
 * License: GNU Free Documentation License 1.2
 * Source: http://neerc.ifmo.ru/trains/toulouse/2017/fft2.pdf
 * Description: Computes the coefficients of $(a_n x^n + \dots + a_0) \cdot (b_n x^n + \dots + b_0) = \sum_{k=0}^{2n} \left( \sum_{i=0}^{k} a_i b_{k-i} \right) x^k$.
 * For convolutions of integers, consider using a number-theoretic transform instead, to avoid rounding issues.
 * This destroys $a$ and $b$ and stores the result in $a$.
 * Time: O(N \log N), but roughly 0.8s for $N = 2^{18}$.
 * Usage: cpx testa[MAXN] = {}, testb[MAXN] = {}; multiply(testa, testb);
 * Status: tested on golfbot
 */
#pragma once

typedef complex<double> cpx;
const int LOGN = 19, MAXN = 1 << LOGN;
int rev[MAXN]; cpx rt[MAXN];

void fft(cpx *A) {
	rep(i, 0, MAXN) if (i < rev[i]) swap(A[i], A[rev[i]]);
	for (int k = 1; k < MAXN; k *= 2)
		for (int i = 0; i < MAXN; i += 2*k) rep(j,0,k) {
				cpx t = rt[j + k] * A[i + j + k];
				A[i + j + k] = A[i + j] - t;
				A[i + j] += t;
			}
}
// Computes convolution of a, b assuming they are of size MAXN.
void multiply(cpx *a, cpx *b) {
	rev[0] = 0; rt[1] = cpx(1, 0);
	rep(i, 0, MAXN) rev[i] = (rev[i/2] | (i&1)<<LOGN)/2;
	for (int k = 2; k < MAXN; k *= 2) {
		cpx z(cos(PI/k), sin(PI/k));
		rep(i, k/2, k) rt[2*i]=rt[i], rt[2*i+1]=rt[i]*z;
	}
	fft(a); fft(b);
	rep(i, 0, MAXN) a[i] *= b[i] / (double)MAXN;
	reverse(a+1,a+MAXN); fft(a); // store the result in a
}
