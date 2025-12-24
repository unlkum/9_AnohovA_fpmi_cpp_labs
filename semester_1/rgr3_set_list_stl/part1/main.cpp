#include <exception>
#include <iostream>
#include <set>
#include <stdexcept>
#include <vector>

int readNumber() {
    std::cout << "Enter N:\n";
    int N;

    if (!(std::cin >> N)) {
        throw std::runtime_error("Can't read n :(");
    }
    if (N < 2) {
        throw std::invalid_argument("N must be >= 2");
    }
    return N;
}

std::set<int> computePrimes(const int N) {
    std::set<int> primes;
    std::vector<bool> sieve(N + 1, true);

    for (int i = 2; i * i <= N; ++i) {
        for (int j = i * i; j <= N; j += i) {
            sieve[j] = false;
        }
    }
    for (int i = 2; i <= N; i++) {
        if (sieve[i]) {
            primes.insert(i);
        }
    }
    return primes;
}

void printSet(const std::set<int>& primes) {
    std::cout << "\nPrime numbers:\n";
    for (int p : primes) {
        std::cout << p << ' ';
    }
    std::cout << "\n";
}

int main() {
    try {
        int N = readNumber();
        std::set<int> primes = computePrimes(N);
        printSet(primes);
    } catch (const std::exception& err) {
        std::cerr << err.what() << std::endl;
    }

    return 0;
}