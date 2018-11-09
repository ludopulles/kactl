#include "template-no-main.h"
#include "../content/graph/SCC.h"

// we have to do a O(N^2) comparison
const int N = 256;

bitset<N> cangoto[N];

void build_graph(double conn_chance, int n = N)
{
	vector<vi> G(n);
	rep(i,0,n) rep(j,0,n)
		if (rand() < RAND_MAX * conn_chance)
			G[i].push_back(j);

	rep(i, 0, n) {
		cangoto[i].reset();	

		queue<int> q;
		q.push(i);
		cangoto[i].set(i);
		while (!q.empty()) { 
			int j = q.front();
			q.pop();
			for (int k : G[j])
				if (!cangoto[i].test(k)) cangoto[i].set(k), q.push(k);
		}
	}

	scc(G, [] (vi a){});

	rep(i, 0, n) rep(j, 0, n) {
		bool is_scc = cangoto[i].test(j) && cangoto[j].test(i);
		assert(is_scc == (comp[i] == comp[j]));
	}
}

void test_small()
{
	build_graph(0.5, rand() % 10);
}

int main() {
	build_graph(0.00001);
	build_graph(0.0001);
	build_graph(0.001);
	build_graph(0.01);
	build_graph(0.1);
	build_graph(0.2);
	build_graph(0.3);
	build_graph(0.5);
	build_graph(0.7);
	build_graph(0.8);
	build_graph(0.9);
	build_graph(0.99);
	build_graph(0.999);
	build_graph(0.9999);
	build_graph(0.99999);

	rep(_,0,1000) test_small();

	return 0;
}
