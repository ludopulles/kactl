/**
 * Author: Simon Lindholm, Ludo Pulles
 * Date: 2016-09-10
 * License: CC0
 * Source: folklore
 * Description:
 * Status: tested
 */
#pragma once

const ll mod = 1000000007; // ~2x faster if mod is const
ll modpow(ll b, ll e) {
	ll r=1; for(;e; e /= 2,b=b*b%mod) if (e & 1) r=r*b%mod;
	return r; }
ll modmpow(ll b, ll e, ll m) {
	ll r=1; for(;e; e /= 2,b=b*b%m) if (e & 1) r=r*b%m;
	return r; }

