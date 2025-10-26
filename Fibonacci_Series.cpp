#include <bits/stdc++.h>
using namespace std;

// Compute nth Fibonacci using simple recursion.
// n must be >= 0. Returns fib(n) as 64-bit integer.
static long long fib_recursive(int n) {
    if (n < 0) {
        throw invalid_argument("n must be non-negative");
    }
    if (n <= 1) return n;
    return fib_recursive(n - 1) + fib_recursive(n - 2);
}

// Divide and Conquer (Matrix Exponentiation) placeholder.
static long long fib_divide_and_conquer(int n) {
    if (n < 0) {
        throw invalid_argument("n must be non-negative");
    }
    return 0;
}

// Dynamic Programming placeholder.
static long long fib_dynamic_programming(int n) {
    if (n < 0) {
        throw invalid_argument("n must be non-negative");
    }
    return 0;
}

// Read a non-negative integer from standard input with prompt.
static int read_non_negative_int(const string &prompt) {
    while (true) {
        cout << prompt;
        string line;
        if (!getline(cin, line)) {
            // EOF or input error
            throw runtime_error("Input stream closed unexpectedly");
        }
        stringstream ss(line);
        long long x; char c;
        if ((ss >> x) && !(ss >> c)) {
            if (x >= 0 && x <= numeric_limits<int>::max()) {
                return static_cast<int>(x);
            }
            cout << "Please enter a non-negative integer within range.\n";
        } else {
            cout << "Invalid input. Please enter a non-negative integer.\n";
        }
    }
}

static void print_menu() {
    cout << "\n==== Fibonacci Calculator ====\n";
    cout << "1) Fibonacci using recursion\n";
    cout << "2) Fibonacci using divide & conquer (matrix exponentiation)\n";
    cout << "3) Fibonacci using dynamic programming\n";
    cout << "0) Exit\n";
}

int main() {

    while (true) {
        print_menu();
        int choice = read_non_negative_int("Select an option: ");
        if (choice == 0) {
            cout << "Goodbye!\n";
            break;
        }
        if (choice < 0 || choice > 3) {
            cout << "Unknown option. Try again.\n";
            continue;
        }

        int n = read_non_negative_int("Enter n (0..92 recommended for 64-bit): ");
        if (n > 92) {
            cout << "Warning: 64-bit signed overflow occurs for n > 92. Results may be incorrect.\n";
        }

        try {
            long long result = 0;
            switch (choice) {
                case 1:
                    if (n > 45) {
                        cout << "Note: Recursive method is very slow for large n. Expect delays.\n";
                    }
                    result = fib_recursive(n);
                    break;
                case 2:
                    result = fib_divide_and_conquer(n);
                    break;
                case 3:
                    result = fib_dynamic_programming(n);
                    break;
            }
            cout << "Fibonacci(" << n << ") = " << result << "\n";
        } catch (const exception &ex) {
            cout << "Error: " << ex.what() << "\n";
        }
    }

    return 0;
}