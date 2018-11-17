/**
 * Author: Johan Sannemo, Simon Lindholm
 * Date: 2016-12-15
 * License: CC0
 * Description: Finds a minimum vertex cover in a bipartite graph.
 * A vertex cover is a set $\tilde{V} \subseteq V$ of vertices such that each edge has $\geq 1$ of its endpoints in $\tilde{V}$.
 *  The size is the same as the size of a maximum matching, and
 *  the complement is an independent set.
 * Status: fuzz-tested
 */
#pragma once

#include "DFSMatching.h"

vi cover(const vector<vi> &g, int n, int m) {
	int res = dfs_matching(g, n, m);
	seen.assign(m, false);
	vector<bool> lfound(n, true);
	for (int i : match) if (i >= 0) lfound[i] = false;
	vi q, vc; rep(i,0,n) if (lfound[i]) q.push_back(i);
	while (!q.empty()) {
		int i = q.back(); q.pop_back(); lfound[i] = true;
		for (int j : g[i]) if (!seen[j] && match[j] >= 0)
			seen[j] = true, q.push_back(match[j]);
	}
	rep(i,0,n) if (!lfound[i]) vc.push_back(i);
	rep(i,0,m) if (seen[i]) vc.push_back(n+i);
	assert(sz(vc) == res); return vc;
}
