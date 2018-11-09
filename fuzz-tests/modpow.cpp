#include "template-no-main.h"
#include "../content/number-theory/ModPow.h"

const int maxtests = 1000;
const int stress_test = 1000 * 1000;

// void T1() { rep(_,0,stress_test) { ll x=rand()%mod, y=rand()%mod; fmodpow(x,y); }}
void T2() { rep(_,0,stress_test) { ll x=rand()%mod, y=rand()%mod; modpow(x,y); }}
// void T3() { rep(_,0,stress_test) { ll x=rand()%mod, y=rand()%mod; modpow(x,y,mod); }}
void T4() { rep(_,0,stress_test) { ll x=rand()%mod, y=rand()%mod; modmpow(x,y,mod); }}

void timefunc(void (*f) (), const char *fname, double lim)
{
    auto t_start = chrono::high_resolution_clock::now();

	f();

    auto t_end = chrono::high_resolution_clock::now();
	double millis = chrono::duration<double, milli>(t_end-t_start).count();
	assert(millis < lim);
	printf("Time taken by function \"%s\": %.f ms\n", fname, millis);
}

int main()
{
	srand(12763763);

	assert(modpow(12345 % mod, 0) == 1);
	assert(modpow(12345 % mod, 1) == 12345 % mod);

	rep(_, 0, maxtests) {
		ll a = rand() % mod; // defined by ModPow.h
		ll ainv = modpow(a, mod - 2);
		assert(0 <= ainv && ainv < mod);
		assert(ainv * a % mod == 1); // it is the inverse by Fermat's little theorem.
	}

	// try different methods.
	// timefunc(T1, "fmodpow");
	timefunc(T2, "impfmodpow", 500);
	// timefunc(T3, "modpow");
	timefunc(T4, "impmodpow", 800);

	return 0;
}
