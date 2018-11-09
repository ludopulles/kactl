#include "template-no-main.h"
#include "../content/graph/Dinic.h"

void test_DAG(int N, ll MAXCAP, int loe, int hie)
{
	vi pi(N);
	rep(i, 0, N) pi[i] = i;
	random_shuffle(pi.begin(), pi.end());

	Dinic graph(N);
	ll maxflow = LLINF;
	rep(i, 0, N - 1) {
		// connect i and i + 1 with multiple edges.
		// the flow past this, is the sum of all capacities.

		ll f = 0LL;
		int nedges = loe + rand() % (hie - loe + 1);

		rep(_, 0, nedges) {
			ll cap = rand() % MAXCAP;
			graph.addEdge(pi[i], pi[i + 1], cap);
			f += cap;
		}
		maxflow = min(maxflow, f);
	}

	ll found = graph.maxflow(pi[0], pi[N - 1]);

	assert(found == maxflow);
}

int main()
{
	srand(38763);

	test_DAG(512, RAND_MAX, 1, 64);
	test_DAG(1024, RAND_MAX, 0, 4);
	test_DAG(5, RAND_MAX, 0, 1000);

	// TODO: add different graphs
	return 0;
}
