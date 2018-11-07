/**
 * Author: Håkan Terelius, Ludo Pulles
 * Date: 2009-09-25
 * License: CC0
 * Source: http://en.wikipedia.org/wiki/Euler's_totient_function
 * Description: Euler's totient (or phi) function is defined as
 * \[ \phi(i) := \# \set{ 0 < j \leq i | \mathrm{gcd}(i, j) = 1 } = n \cdot \prod_{p \mid n} \frac{p-1}{p}. \]
 * The \emph{cototient} is $n-\phi(n)$.
 * $\phi(1)=1$, $p$ prime $\Rightarrow \phi(p^k)=(p-1)p^{k-1}$, $m,n$ coprime $\Rightarrow \phi(mn)=\phi(m)\phi(n)$.
 * If $n=p_1^{k_1}p_2^{k_2} ... p_r^{k_r}$ then $\phi(n) = (p_1-1)p_1^{k_1-1}...(p_r-1)p_r^{k_r-1}$.
 * $\sum_{d|n} \phi(d) = n$, $\sum_{1\leq k \leq n, \gcd(k,n)=1} k = n \phi(n)/2, n>1$
 * 
 * \textbf{Euler's thm}: $a,n$ coprime $\Rightarrow a^{\phi(n)} \equiv 1 \pmod{n}$.
 *
 * \textbf{Fermat's little thm}: $p$ prime $\Rightarrow a^{p-1} \equiv 1 \pmod{p}$ $\forall a$.
 * Status: Tested
 */
#pragma once

vi totient(int N) {
	vi phi(N);
	for (int i = 0; i < N; i++) phi[i] = i;
	for (int i = 2; i < N; i++) if (phi[i] == i)
		for (int j = i; j < N; j+=i) phi[j] -= phi[j]/i;
	return phi;
}
