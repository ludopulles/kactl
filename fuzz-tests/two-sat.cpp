#include "template-no-main.h"
#include "../content/graph/2sat.h"

int test_big() {
	const int N = 100, M = 100000;

	// Random constraints, unsolvable
	TwoSat ts(N);
	rep(i,0,M) {
		int s = rand();
		int a, b;
		do {
			a = rand() % N;
			b = rand() % N;
		} while (a == b);
		ts.either(s&1 ? a : ~a, s&2 ? b : ~b);
	}
	assert(!ts.solve());

	// Random solvable instance
	vector<bool> v(N);
	rep(i,0,N) v[i] = rand() & (1 << 20);
	ts = TwoSat(N);
	rep(i,0,M) {
		bool s = rand() & 1;
		int a, b;
		do {
			a = rand() % N;
			b = rand() % N;
		} while (a == b);
		ts.either(v[a] ? a : ~a, s&1 ? b : ~b);
	}
	return 0;
}

void test_unsats() {
	const int N = 150;

	TwoSat ts(N);
	int nadded = 0;
	while (nadded < N && ts.solve()) {
		// add an extra conflicting constraint.
		nadded++;

		int a, b;
		do {
			a = rand() % N;
			b = rand() % N;
		} while (a == b);

		bool sata = !ts.values[a];
		bool satb = !ts.values[b];
		ts.either(sata ? a : ~a, satb ? b : ~b);
	}
	assert(nadded < N);
}

int test_specific() {
	int N = 4;
	TwoSat ts(N);
	ts.either(0, 1);
	ts.either(0, ~1);
	ts.either(~2, ~3);

	assert(ts.solve());

	vi ans{ 1, 1, 1, 0 };
	assert(ts.values == ans);
	return 0;
}

void run_big_cases()
{
	const int N = 100, M = 400;
	rep(it,0,100) {
		vector<bool> v(N);
		rep(i,0,N) v[i] = rand() & 1;
		TwoSat ts(N);
		vector<vi> atm;
		vi r;
		rep(i,0,M) {
			if (rand() % 100 < 5) {
				bool s = rand() & 1;
				int a, b;
				do {
					a = rand() % N;
					b = rand() % N;
				} while (a == b);

				ts.either(v[a] ? a : ~a, s ? b : ~b);
			} else {
				int k = rand() % 4 + 1;
				r.clear();
				rep(ki,0,k-1) {
					int a = rand() % N;
					r.push_back(v[a] ? ~a : a);
				}
				r.push_back(rand() % (2*N) - N);
				random_shuffle(all(r), [](int x) { return rand() % x; });
				ts.at_most_one(r);
				atm.push_back(r);
			}
		}
		assert(ts.solve());
		int to = 0;
		rep(i,0,N) to += (ts.values[i] == v[i]);
		trav(rr, atm) {
			int co = 0;
			trav(x, rr) co += (ts.values[max(x, ~x)] == (x >= 0));
			assert(co <= 1);
		}

		// TODO: find a better criteria to check if this 2-sat result is valid.
		assert(to >= 90);
	}
}

// Test at_most_one
int main() {
	srand(13763850);

	test_big();
	test_specific();

	for (int i = 0; i < 10; i++) test_unsats();

	run_big_cases();

	return 0;
}
