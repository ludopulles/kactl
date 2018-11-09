#include "template-no-main.h"
#include "../content/graph/MinimumVertexCover.h"

int main() {
	rep(it,0,1000000) {
		int N = rand() % 20, M = rand() % 20;
		int prop = rand();
		vector<vi> gr(N);
		vi left(N), right(M);
		rep(i,0,N) rep(j,0,M) if (rand() < prop) {
			gr[i].push_back(j);
		}
		auto verify = [&](vi& cover) {
			trav(x, cover) {
				if (x < N) left[x] = 1;
				else right[x - N] = 1;
			}
			rep(i,0,N) if (!left[i]) trav(j,gr[i]) {
				assert(right[j]);
				/* if (!right[j]) {
					cout << N << ' ' << M << endl;
					rep(i,0,N) trav(j, gr[i]) cout << i << " - " << j << endl;
					cout << "yields " << sz(cover) << endl;
					trav(x, cover) cout << x << endl;
					abort();
				} */
			}
		};
		// vi cover1 = dfs2(gr, N, M);
		vi cover2 = cover(gr, N, M);
		// assert(sz(cover1) == sz(cover2));
		// verify(cover1);
		verify(cover2);
		// cout << '.' << endl;
	}
}
