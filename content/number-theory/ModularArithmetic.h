/**
 * Author: Lukas Polacek
 * Date: 2009-09-28
 * License: CC0
 * Source: folklore
 * Description: Operators for modular arithmetic. You need to set {\tt mod} to
 * some number first and then you can use the structure.
 */
#pragma once

#include "euclid.h"

template<ll M> struct Mod {
	ll x;
	Mod(ll xx) : x(((xx%M)+M)%M) {}
	Mod operator+(Mod b) { return Mod((x + b.x) % M); }
	Mod operator-(Mod b) { return Mod((x - b.x + M) % M); }
	Mod operator*(Mod b) { return Mod((x * b.x) % M); }
	Mod operator/(Mod b) { return *this * invert(b); }
	Mod invert(Mod a) {
		ll i, y; assert(euclid(a.x, M, i, y) == 1);
		return Mod((i + M) % M);
	}
	Mod operator^(ll e) {
		if (!e) return Mod(1);
		Mod r = *this ^ (e / 2); r = r * r;
		return e&1 ? *this * r : r;
	}
};
