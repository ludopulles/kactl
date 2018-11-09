/**
 * Author: Simon Lindholm (with some fiddling by Ludo Pulles)
 * Date: 2016-08-31
 * License: CC0
 * Source: http://eli.thegreenplace.net/2009/03/07/computing-modular-square-roots-in-python/
 * Description: Tonelli-Shanks algorithm for modular square roots.
 * Time: O(\log^2 p) worst case, often O(\log p)
 * Status: Tested for all a,p <= 10000
 */
#pragma once

#include "ModPow.h"

ll sqrt(ll a, ll p) {
	if ((a%=p) < 0) a += p;
	if (a == 0) return 0;
	assert(modmpow(a, (p-1)/2, p) == 1); // legendre
	if (p % 4 == 3) return modmpow(a, (p+1)/4, p);
	// a^(n+3)/8 or 2^(n+3)/8 * 2^(n-1)/4 works if p % 8 == 5
	ll s = p - 1, n = 2;
	int r = 0;
	while (s % 2 == 0) ++r, s /= 2;
	// find a non-square mod p
	while (modmpow(n, (p - 1) / 2, p) != p - 1) ++n;
	ll x = modmpow(a, (s + 1) / 2, p);
	ll b = modmpow(a, s, p), g = modmpow(n, s, p);
	while (r && b != 1) {
		int m = 0;
		for (ll t = b; m < r && t != 1; ++m) t = t * t % p;
		//assert(m!=0);
		ll gs = modmpow(g, 1LL << (r - m - 1), p);
		g = gs * gs % p; x = x * gs % p;
		b = b * g % p; r = m;
	}
	return x;
}
