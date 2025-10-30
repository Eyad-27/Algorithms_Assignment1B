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

// Compute nth Fibonacci using Divide and Conquer (matrix exponentiation).

// multiply matrix

vector<vector<long long>> multiply2x2Matrices(const vector<vector<long long>> &arr1,
  const vector<vector<long long>> &arr2) {
vector<vector<long long>> result(2, vector<long long>(2));

result[0][0] = arr1[0][0] * arr2[0][0] + arr1[0][1] * arr2[1][0];
result[0][1] = arr1[0][0] * arr2[0][1] + arr1[0][1] * arr2[1][1];
result[1][0] = arr1[1][0] * arr2[0][0] + arr1[1][1] * arr2[1][0];
result[1][1] = arr1[1][0] * arr2[0][1] + arr1[1][1] * arr2[1][1];

return result;
}


//power matrix
vector<vector<long long>> powerMatrix(vector<vector<long long>> &arr, long long n) {
    // Base case
    if (n == 0)  return {{1, 0}, {0, 1}};

    // Recursive case
    vector<vector<long long>> half = powerMatrix(arr, n / 2);

    if (n % 2 == 0)

        return multiply2x2Matrices(half,half);
    else

        return multiply2x2Matrices(arr,multiply2x2Matrices(half,half)) ;
}

static long long fib_divide_and_conquer(int n) {


    if (n < 0) {
        throw invalid_argument("n must be non-negative");
    }else{
        if(n==0){
            return 0;
        }else if(n==1||n==2){
            return 1;
        }else{
            vector<vector<long long>> Base = {{1, 1}, 
                                              {1, 0}};
            Base =  powerMatrix(Base,n-1);

            return Base[0][0];
        }
    }
    
    return -1;
}

// Compute nth Fibonacci using Dynamic Programming (iterative).
static long long fib_dynamic_programming(int n) {
    if (n < 0) throw invalid_argument("n must be non-negative");
    if (n == 0) return 0;
    if (n == 1) return 1;
    long long a = 0, b = 1;
    for (int i = 2; i <= n; ++i) {
        long long c = a + b;
        a = b;
        b = c;
    }
    return b;
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