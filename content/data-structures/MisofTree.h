/**
 * Author: Bjarki Ágúst Guðmundsson, Ludo Pulles
 * Date: 2016-10-28
 * License: MIT
 * Source: https://github.com/SuprDewd/CompetitiveProgramming/
 * Description: A simple tree data structure for inserting, erasing,
 * and querying the $n^{\mathrm{th}}$ largest element.
 * Time: O(\log N) per query
 * Status: untested
 */

const int BITS = 15;
struct misof_tree {
	int cnt[BITS][1<<BITS];
	misof_tree() { memset(cnt, 0, sizeof(cnt)); }
	void add(int x, int dv) { // +1 <-> add, -1 <-> erase
		for (int i = 0; i < BITS; cnt[i++][x] += dv, x >>= 1); }
	int nth(int n) {
		int r = 0, i = BITS;
		while (i--) if (cnt[i][r <<= 1] <= n)
			n -= cnt[i][r], r |= 1;
		return r; } }; 
