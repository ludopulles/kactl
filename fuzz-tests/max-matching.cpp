#include "template-no-main.h"
#include "../content/graph/MinimumVertexCover.h"
#include "../content/graph/Dinic.h"

void testgraph(const vector<vi> &g, int n, int m)
{
	// compare the maximal matching with Dinic.
	int found = dfs_matching(g, n, m);

	Dinic fg(n + m + 2);
	rep(i, 0, n) {
		fg.addEdge(n+m, i, 1);
		for (int j : g[i]) fg.addEdge(i, n + j, 1);
	}
	rep(j, 0, m) fg.addEdge(n+j, n+m+1, 1);

	int expected = (int) fg.maxflow(n+m,n+m+1);
	assert(expected == found);

	// find the minimum vertex cover and compare the size with the maximal matching.
	// König's theorem states these are equal.

	vi cv = cover(g, n, m); // runs max-matching again :(.
	assert(sz(cv) == found);

	vector<bool> inlcover(n, false), inrcover(m, false);
	for (int i : cv)
		if (i < n) inlcover[i] = true;
		else inrcover[i - n] = true;

	// assert this is a vertex cover
	rep(i, 0, n) for (int j : g[i]) {
		assert(inlcover[i] || inrcover[j]);
	}
}

void testgraph(int maxn, int maxm, int maxe)
{
	int n = rand() % maxn;
	int m = rand() % maxm;
	vector<vi> g(n);
	int nedges = !n || !m ? 0 : rand() % maxe;
	while (nedges--) {
		int a = rand() % n, b = rand() % m;
		g[a].push_back(b);
	}
	testgraph(g, n, m);
}

int main()
{
	srand(139873);

	rep(i, 0, 100) testgraph(50, 50, 1000);
	testgraph(1000, 1000, 50000);
	testgraph(5, 10000, 50000);
	testgraph(10000, 5, 50000);
	return 0;
}

