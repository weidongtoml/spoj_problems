// File: PrimeGenerator.cc
// Description: generates a list of all primes within the given range.
// 	For proper problem statement, refer to spoj problem ID 2 Prime Generator.
// Date: 2013.12.13

#include <bitset>
#include <iostream>
#include <cmath>

using namespace std;

const size_t maxN = 1000000001;
bitset<maxN> primes;  //primes[0] == 0 means prime, 1 for non-primes.
int main() {
	const size_t sqrtMaxN = size_t(sqrt(maxN));
	
	primes[0] = 1;
	primes[1] = 1;
	// Main processing loop.
	int numCases;
	cin >> numCases;
	while (numCases-- > 0) {
		size_t m, n;
		cin >> m >> n;
		// Segmented Sieve of Eratosthenes
		for (size_t i = 2; i <= size_t(sqrt(n)); i++) {
			if (primes[i] == 0) {
				size_t m_f = size_t(m/i);
				if (m_f <= 1) {
					m_f = 2;
				}
				for (size_t j = i*m_f; j <= n; j+=i) {
					primes[j] = 1;
				}
			}
		}
		for (size_t i = m; i <= n; i++) {
			if (primes[i] == 0) {
				cout << i << endl;
			}
		}
		cout << endl;
	}
	return 0;
}

