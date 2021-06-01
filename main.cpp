#include <vector>
#include <iostream>
#include <functional>
#include "memoize.h"
#include <chrono>

using namespace std;

unsigned long fib(unsigned n) {
    return (n < 2) ? n :
           STATIC_MEMOIZER(fib)(n - 1) +
           STATIC_MEMOIZER(fib)(n - 2);
}

unsigned long fibonacci(unsigned n) {
    return (n < 2) ? n : fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {

    static chrono::time_point<chrono::steady_clock> start, end;
    static chrono::duration<double, std::milli> ms_double;
    static long long n = INT16_MAX;

    start = chrono::high_resolution_clock::now();
    fibonacci(n);
    end = chrono::high_resolution_clock::now();
    ms_double = end - start;
    cout << "not memoized: " << ms_double.count() << "ms\n";

    start = chrono::high_resolution_clock::now();
    fib(n);
    end = chrono::high_resolution_clock::now();
    ms_double = end - start;
    cout << "    memoized: " << ms_double.count() << "ms\n";
}