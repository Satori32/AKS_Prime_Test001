#include <iostream>
#include <cstdint>
#include <cmath>
#include <numeric>
#include <limits>
#include <algorithm>
#include <vector>

//not complete.

double MyLog(const double& V, const double& Base) {
	//return std::pow(V, 1 / std::log(std::exp(Base)));
	return std::pow(V, 1 / Base);
}

double Or(double N,double r) {//N^a = a^N?
	return std::floor(std::fmod(std::log(N),r));
	//return std::pow(N, r) * (1 - (1 / N));
}
std::uintmax_t totient(const std::uintmax_t& In) {

	std::uintmax_t N = 0;
	for (std::uintmax_t i = 1; i < In; i++) {
		if (std::lcm(i, In) == 1) { N++; }
	}

	return N;
}
std::uintmax_t totient(const std::uintmax_t& N,double r) {
	/** /
	std::uintmax_t N = 0;
	for (std::uintmax_t i = 0; i < In; i++) {
		if (std::lcm(i, In) == 1) { N++; }
	}

	return N;
	/**/
	return std::pow(N, r) * (1 - (1 / (double)N));
}

double FloorFunction(double N) {
	return std::floor(N);
}

bool AKSPrime(const std::uintmax_t& N) {
	double A = 0.0;
	if (N < 2) return false;

	for (std::uintmax_t i = 2; i < N; i++) {
		double V = MyLog(N, 2);
		if (V == std::floor(V)) return false;
		if ((N % i) == 0) return false;
	}

	double T = 4 * MyLog(N, 2);
	double r = 0;

	for (r = 0; Or(N,r) <= T; r += 0.001) {}

	std::uintmax_t a = 0;
	for (a = 2; a <= r; a++) {
		std::uintmax_t V = std::lcm(a, N);
		if ((1 < V) && (V <= N)) { return false; }
	}
	if (N <= r) { return true; }

	T = FloorFunction(2 * std::sqrt(totient(r)) * MyLog(N,10));
	for (double a = 1; a <T ; a += std::numeric_limits<double>::epsilon()*2) {
		for (double X = 0; X < N; X += 1) {
			double A = std::pow(X + a, N);
			double B = std::fmod(std::pow(X, N) + a,N);
			if (std::fmod(A, B) != 0)return false;
		}
	}
	

	return true;
	//for (double X = 1; X < std::floor(2 * std::sqrt(totient(r)) * MyLog(N, 10)); X += 1) {	}
}

int main() {
	for (std::size_t N = 0; N <= 100; N++) {
		std::cout << N << ':' << AKSPrime(N) << std::endl;
	}

	return 0;
}
