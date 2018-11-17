/**
 * Author: Ludo Pulles
 * Date: 2018-11-17
 * License: CC0
 * Source: Folklore
 * Description: Finds the maximum matching in a bipartite graph of $n$ left and $m$ right nodes, with a list of edges from the left to the right partition.
 * If you want to get the matched pairs, \texttt{match[i]} contains
 * match for vertex $i$ on the right side or $-1$ if it is unmatched.
 * Time: O(VE)
 * Status: works
 */
#pragma once

vi match; vector<bool> seen;
bool augment(int v, const vector<vi> &g) {
	if (seen[v]) return false;
	seen[v] = true;
	for (int w : g[v]) if (match[w] < 0 || augment(match[w], g))
		return match[w] = v, true;
	return false;
}
int dfs_matching(const vector<vi> &g, int n, int m) {
	match.assign(m, -1); seen.resize(n); int r = 0;
	rep(i, 0, n) fill(all(seen), false), r += augment(i, g);
	return r;
}
