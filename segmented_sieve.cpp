#include <iostream>
#include <cmath>
#include <vector>

bool is_prime(int n) {
	for (int i = 2; i <= (int)std::sqrt(n); i++) {
		if (n%i == 0) return false;
	}
	return true;
}

std::vector<int> standard_sieve(int n) {
	std::vector<int> found_primes = {};
	std::vector<bool> A = std::vector<bool>(n, true);
	A[0] = false;
	A[1] = false;
	for (int i = 2; i <= (int)std::sqrt(n); i++) {
		// if A[i] is prime
		if (A[i] != false) {
			for (int j = i*i; j < n; j += i) {
				A[j] = false;
			}
		}
	}
	for (int i = 0; i < n; i++) {
		if (A[i] == true) {
			found_primes.push_back(i);
		}
	}
	return found_primes;
}

std::vector<int> segmented_sieve(int n) {
	int delta = (int)std::sqrt(n);
	std::vector<int> found_primes = standard_sieve(delta);

	// m is the topmost value of the segment
	// meaning the segment is [m-delta+1,m]
	// number k has index k-(m-delta+1) = k-m+delta-1
	// number at index i has value m-delta+1+i
	for (int m = delta*2 - 1; m < n; m += delta) {
		std::vector<bool> A = std::vector<bool>(delta, true);
		int i = 0;
		while (found_primes[i] <= (int)std::sqrt(m)) {
			int p = found_primes[i];
			int q = ((m-delta)/p) + 1; // one before first num in range divided by p, then ceiled
			for (int multiple = p*q; multiple <= m; multiple += p) {
				A[multiple-m+delta-1] = false;
			}
			i++;
		}
		for (int i = 0; i < delta; i++) {
			if (A[i] == true) {
				found_primes.push_back(m-delta+1+i);
			}
		}
	}
	return found_primes;
}

int main() {

	constexpr int N = 1'000'000'000;
	auto segmented_primes = segmented_sieve(N);

	std::cout << "Num primes below " << N << " is " << segmented_primes.size() << '\n';

	return 0;
}
