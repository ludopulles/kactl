/**
 * Author: Ludo Pulles
 * License: CC0
 * Description: pi[x] computes the length of the longest prefix of s that ends at x, other than s[0...x] itself (abacaba -> 0010123).
 * Can be used to find all occurrences of a string.
 * Time: O(n)
 * Status: fuzz-tested
 * Usage: KMP(`pattern', pi_fn(`pattern'), 'text');
 */
#pragma once

vi pi_fn(const string &s) {
	int n = sz(s); vi p(n, 0);
	for (int i = 1, j = 0; i < n; ) {
		if (s[i] == s[j]) p[i++] = ++j; // match
		else if (j > 0) j = p[j-1]; // fallback
		else i++; // no match
	} return p;
}

vi KMP(const string &pat, const vi &p, const string &text) {
	vi res; // assert(pi(pat) == p);
	for (int i = 0, j = 0; i < sz(text); ) {
		if (text[i] == pat[j]) {
			i++; if (++j == sz(pat)) res.push_back(i-sz(pat)), j = p[j-1];
		} else if (j > 0) j = p[j-1];
		else i++;
	} return res; }
