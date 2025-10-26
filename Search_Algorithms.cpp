#include <bits/stdc++.h>
using namespace std;

// Sequential search
int sequentialSearchIterative(const vector<int>& a, int target) {
    (void)a; (void)target; // not implemented
    return -1;
}

int sequentialSearchRecursive(const vector<int>& a, int target, int i = 0) {
    if (i >= static_cast<int>(a.size())) {
        return -1;
    }
    if (a[i] == target) {
        return i;
    }
    return sequentialSearchRecursive(a, target, i + 1);
}


// Binary search (iterative)
int binarySearchIterative(const vector<int>& a, int target) {
    int l = 0, r = (int)a.size() - 1;
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (a[m] == target) return m;
        if (a[m] < target) l = m + 1; else r = m - 1;
    }
    return -1;
}

// Binary search (recursive)
int binarySearchRecursive(const vector<int>& a, int target, int l = 0, int r = -1) {
    if (r == -1) r = (int)a.size() - 1;
    if (l > r) return -1;
    int m = l + (r - l) / 2;
    if (a[m] == target) return m;
    if (a[m] < target) return binarySearchRecursive(a, target, m + 1, r);
    return binarySearchRecursive(a, target, l, m - 1);
}

// Read an integer with prompt; keep asking until valid
static int readInt(const string& prompt) {
    for (;;) {
        if (!prompt.empty()) cout << prompt;
        int x;
        if (cin >> x) return x;
        cout << "Invalid input. Try again.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

static void printMenu() {
    cout << "\nSearch Algorithms\n";
    cout << "1) Binary Search (Iterative)\n";
    cout << "2) Binary Search (Recursive)\n";
    cout << "3) Sequential Search (Iterative)\n";
    cout << "4) Sequential Search (Recursive)\n";
    cout << "0) Exit\n";
}

int main() {
    while (true) {
        printMenu();
        int choice = readInt("Choose: ");
        if (choice == 0) break;

        int n = readInt("Enter number of elements: ");
        while (n <= 0) { cout << "Invalid n\n"; n = readInt("Enter number of elements: "); }
        vector<int> a(n);
        if (choice == 1 || choice == 2) cout << "Enter " << n << " sorted integers:\n"; else cout << "Enter " << n << " integers:\n";
        for (int i = 0; i < n; ++i) a[i] = readInt("");
        int target = readInt("Enter target: ");

        int idx = -1;
        if (choice == 1) idx = binarySearchIterative(a, target);
        else if (choice == 2) idx = binarySearchRecursive(a, target);
        else if (choice == 3) idx = sequentialSearchIterative(a, target);
        else if (choice == 4) idx = sequentialSearchRecursive(a, target);
        else { cout << "Unknown option\n"; continue; }

        if (idx >= 0) cout << "Found at index " << idx << "\n"; else cout << "Not found\n";
    }
    cout << "Goodbye!\n";
    return 0;
}