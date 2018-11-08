/**
 * Author: Lucian Bicsi, Ludo Pulles (making it compile)
 * Date: 2015-06-25
 * License: GNU Free Documentation License 1.2
 * Source: csacademy
 * Description: Transform to a basis with fast convolutions of the form
 * $\displaystyle c[z] = \sum\nolimits_{z = x \oplus y} a[x] \cdot b[y]$,
 * where $\oplus$ is one of AND (use \texttt{op < 0}), XOR (use \texttt{op = 0}) and OR (use \texttt{op > 0}). The size of $a$ must be a power of two.
 * Time: O(N \log N)
 * Status: tested
 */
#pragma once

void FST(vi& a, int op, bool inv) {
	for (int n = sz(a), step = 1; step < n; step *= 2) {
		for (int i = 0; i < n; i += 2 * step) rep(j,i,i+step) {
			int &u = a[j], &v = a[j + step];
			if (op<0) tie(u,v) = inv ? pii(v - u, u) : pii(v, u + v);
			if (op>0) tie(u,v) = inv ? pii(v, u - v) : pii(u + v, u);
			if (!op) tie(u, v) = pii(u + v, u - v);
		}
	}
	if (inv && !op) trav(x, a) x /= sz(a);
}
vi conv(vi a, vi b, int op) {
	FST(a, op, 0); FST(b, op, 0);
	rep(i, 0, sz(a)) a[i] *= b[i];
	FST(a, op, 1); return a;
}
