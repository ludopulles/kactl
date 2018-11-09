#include "template-no-main.h"
#include "../content/data-structures/LazySegmentTreeAlt.h"

const int tests = 16;

void run(int N, int operations)
{
	// initialize with random values:
	vector<ll> arr(N, 0);
	rep(i, 0, N) arr[i] = rand() - RAND_MAX / 2;

	segment_tree st(arr);

	while (operations--) {
		int op = rand() % 3;
		if (op == 0) { 
			// update
			int a = rand() % N;
			ll v = rand();

			st.update(a, v); // update theirs
			arr[a] = v; // update ours

		} else if (op == 1) {
			// range update
			int a = rand() % N, b = rand() % N;
			if (a > b) swap(a, b);
			ll v = rand();

			st.range_update(a, b, v);
			for (int i = a; i <= b; i++)
				arr[i] += v;

		} else {
			// query
			int a = rand() % N, b = rand() % N;
			if (a > b) swap(a, b);

			ll expected = *min_element(arr.begin() + a, arr.begin() + b + 1);
			assert(st.query(a, b).x == expected);
		}
	}
}

int main() {
	rep(_,0,tests) run(1024, 8192); // 1 << 23
	rep(_,0,tests) run(16, 1 << 19); // 1 << 23
}
