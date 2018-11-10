/**
 * Author: Ludo Pulles
 * License: CC0
 * Source: folklore
 * Description: \texttt{z[i]} is the length of longest substring starting from $i$.
 * Time: O(N)
 */

vi z_function(const string &s) {
	int n = sz(s), l=0,r=0; vi z(n);
	rep(i, 1, n) {
		if (i <= r) z[i] = min (r - i + 1, z[i - l]);
		while (i+z[i] < n && s[z[i]] == s[i+z[i]]) z[i]++;
		if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
	} return z; }
