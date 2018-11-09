/**
 * Author: Simon Lindholm
 * Date: 2016-09-10
 * License: CC0
 * Source: based on KACTL's FFT
 * Description: Can be used for convolutions modulo specific nice primes
 * of the form $2^a b+1$, where the convolution result has size at most $2^a$.
 * For other primes/integers, use two different primes and combine with CRT.
 * Time: O(N \log N)
 * Status: Somewhat tested
 */
#pragma once

#include "../number-theory/ModPow.h"

const ll nmod = (119 << 23) + 1, root = 3; // = 998244353
// For p < 2^30 there is also e.g. (5 << 25, 3), (7 << 26, 3),
// (479 << 21, 3) and (483 << 21, 5). The last two are > 10^9.

typedef vector<ll> vl;
void ntt(ll* x, ll* temp, ll* roots, int N, int skip) {
	if (N == 1) return;
	int n2 = N/2;
	ntt(x     , temp, roots, n2, skip*2);
	ntt(x+skip, temp, roots, n2, skip*2);
	rep(i,0,N) temp[i] = x[i*skip];
	rep(i,0,n2) {
		ll s = temp[2*i], t = temp[2*i+1] * roots[skip*i];
		x[skip*i] = (s + t) % nmod; x[skip*(i+n2)] = (s - t) % nmod;
	}
}
void ntt(vl& x, bool inv = false) {
	ll e = modmpow(root, (nmod-1) / sz(x), nmod);
	if (inv) e = modmpow(e, nmod-2, nmod);
	vl roots(sz(x), 1), temp = roots;
	rep(i,1,sz(x)) roots[i] = roots[i-1] * e % nmod;
	ntt(&x[0], &temp[0], &roots[0], sz(x), 1);
}
vl conv(vl a, vl b) {
	if (a.empty() || b.empty()) return {};
	int s = sz(a) + sz(b) - 1, L = 32 - __builtin_clz(s-1), n = 1 << L;
	if (s <= 200) {
		vl c(s); // (3x faster for |a|,|b| = 10)
		rep(i,0,sz(a)) rep(j,0,sz(b))
			c[i + j] = (c[i + j] + a[i] * b[j]) % nmod;
		trav(x, c) if (x < 0) x += nmod;
		return c;
	}
	a.resize(n); ntt(a);
	b.resize(n); ntt(b);
	ll d = modmpow(n, nmod-2, nmod); // n^{-1}
	rep(i,0,n) a[i] = a[i] * b[i] % nmod * d % nmod;
	ntt(a, true); a.resize(s); trav(x, a) if (x<0) x += nmod; return a;
}
