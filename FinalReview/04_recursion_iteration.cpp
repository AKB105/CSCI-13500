/*
    Week 6 Review: Recursion vs Iteration

    Good cheat-sheet ideas:
    - Recursion needs a base case.
    - Naive recursive Fibonacci repeats work.
    - Iteration is better for long flat sequences.
    - Memoization keeps recursion readable while avoiding repeated work.
*/

#include <iostream>
#include <vector>

int FibonacciRecursive(int n) {
    if (n <= 1) {
        return n;
    }
    return FibonacciRecursive(n - 1) + FibonacciRecursive(n - 2);
}

int FibonacciIterative(int n) {
    if (n <= 1) {
        return n;
    }

    int previous = 0;
    int current = 1;

    for (int i = 2; i <= n; i++) {
        int next = previous + current;
        previous = current;
        current = next;
    }

    return current;
}

long long FibonacciMemoizedHelper(int n, std::vector<long long>& memo) {
    if (n <= 1) {
        return n;
    }

    if (memo[n] != -1) {
        return memo[n];
    }

    memo[n] = FibonacciMemoizedHelper(n - 1, memo) +
              FibonacciMemoizedHelper(n - 2, memo);
    return memo[n];
}

long long FibonacciMemoized(int n) {
    std::vector<long long> memo(n + 1, -1);
    return FibonacciMemoizedHelper(n, memo);
}

int SumArrayIterative(const int values[], int size) {
    int total = 0;
    for (int i = 0; i < size; i++) {
        total += values[i];
    }
    return total;
}

int SumArrayRecursive(const int values[], int size) {
    if (size == 0) {
        return 0;
    }
    return values[0] + SumArrayRecursive(values + 1, size - 1);
}

int main() {
    for (int n = 0; n <= 10; n++) {
        std::cout << n << ": "
                  << FibonacciRecursive(n) << ", "
                  << FibonacciIterative(n) << ", "
                  << FibonacciMemoized(n) << "\n";
    }

    const int scores[5] = {10, 20, 30, 40, 50};
    std::cout << "Iterative sum: " << SumArrayIterative(scores, 5) << "\n";
    std::cout << "Recursive sum: " << SumArrayRecursive(scores, 5) << "\n";

    return 0;
}
