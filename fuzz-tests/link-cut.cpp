/**
 * Tests the validity of the link-cut tree, while assuming that the union-find algorithm is valid!
 */
#include "template-no-main.h"
#include "../content/graph/LinkCutTree.h"
#include "../content/data-structures/UnionFind.h"

const int nsamples = 1000, nchanges = 1000;

int main() {
	srand(398728763);

	int _ = nsamples;
	while (_--) {
		int N = rand() % 20 + 1;

		LinkCut lc(N);
		UF uf(N);
		vector<pii> edges;

		rep(__, 0, nchanges) {
			int v = (rand() >> 4) & 3;
			if (v == 0 && !edges.empty()) { // remove
				int r = (rand() >> 4) % sz(edges);
				pii ed = edges[r];
				swap(edges[r], edges.back());
				edges.pop_back();
				if (rand() & 16)
					lc.cut(ed.first, ed.second);
				else
					lc.cut(ed.second, ed.first);
			} else {
				int a = (rand() >> 4) % N;
				int b = (rand() >> 4) % N;
				uf.e.assign(N, -1);
				trav(ed, edges) uf.join(ed.first, ed.second);
				bool c = uf.same_set(a, b);
				if (!c && v != 1) {
					lc.link(a, b);
					edges.emplace_back(a, b);
				} else {
					assert(lc.connected(a, b) == c);
				}
			}
		}
	}

	return 0;
}
