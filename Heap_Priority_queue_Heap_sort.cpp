#include <bits/stdc++.h>
using namespace std;

// Simple MaxHeap and MinHeap implementations
class MaxHeap {
    vector<int> a;
    void shiftUp(int i) {
        while (i > 0) {
            int p = (i - 1) / 2;
            if (a[p] >= a[i]) break;
            swap(a[p], a[i]);
            i = p;
        }
    }
    void shiftDown(int i) {
        int n = (int)a.size();
        while (true) {
            int l = 2 * i + 1, r = 2 * i + 2, largest = i;
            if (l < n && a[l] > a[largest]) largest = l;
            if (r < n && a[r] > a[largest]) largest = r;
            if (largest == i) break;
            swap(a[i], a[largest]);
            i = largest;
        }
    }
public:
    void build(const vector<int>& v) {
        a = v;
        for (int i = (int)a.size() / 2 - 1; i >= 0; --i) shiftDown(i);
    }
    void insert(int x) { a.push_back(x); shiftUp((int)a.size() - 1); }
    bool empty() const { return a.empty(); }
    int extractMax() {
        if (a.empty()) return INT_MIN;
        int ans = a[0];
        a[0] = a.back(); a.pop_back();
        if (!a.empty()) shiftDown(0);
        return ans;
    }
};

class MinHeap {
    vector<int> a;
    void shiftUp(int i) {
        while (i > 0) {
            int p = (i - 1) / 2;
            if (a[p] <= a[i]) break;
            swap(a[p], a[i]);
            i = p;
        }
    }
    void shiftDown(int i) {
        int n = (int)a.size();
        while (true) {
            int l = 2 * i + 1, r = 2 * i + 2, smallest = i;
            if (l < n && a[l] < a[smallest]) smallest = l;
            if (r < n && a[r] < a[smallest]) smallest = r;
            if (smallest == i) break;
            swap(a[i], a[smallest]);
            i = smallest;
        }
    }
public:
    void build(const vector<int>& v) {
        a = v;
        for (int i = (int)a.size() / 2 - 1; i >= 0; --i) shiftDown(i);
    }
    void insert(int x) { a.push_back(x); shiftUp((int)a.size() - 1); }
    bool empty() const { return a.empty(); }
    int extractMin() {
        if (a.empty()) return INT_MAX;
        int ans = a[0];
        a[0] = a.back(); a.pop_back();
        if (!a.empty()) shiftDown(0);
        return ans;
    }
};

struct PriorityQueue {
private:
    priority_queue<pair<int, int>> pq;

public:
    void insert(int value, int priority) {
        pq.push({priority, value});
    }
    int extractHighestPriority() {
        if (pq.empty()) {
            throw runtime_error("Priority Queue is empty");
        }
        int value = pq.top().second;
        pq.pop();
        return value;
    }
    bool empty() const {
        return pq.empty();
    }
};

// Heap Sort
static void heapSort(vector<int>& /*arr*/) {
    cout << "Heap Sort: \n";
}

// Robust integer input helper
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

static void runHeapDemo() {
    cout << "Choose heap type: 1) Max Heap  2) Min Heap\n";
    int t = readInt("Type: ");
    int n = readInt("Enter number of elements: ");
    while (n <= 0) { cout << "Invalid n\n"; n = readInt("Enter number of elements: "); }
    vector<int> v(n);
    cout << "Enter " << n << " integers:\n";
    for (int i = 0; i < n; ++i) v[i] = readInt("");

    if (t == 1) {
        MaxHeap h; h.build(v);
        int k = readInt("How many extractions (max) to perform? ");
        for (int i = 0; i < k; ++i) {
            if (h.empty()) { cout << "Heap empty\n"; break; }
            cout << "Extracted max: " << h.extractMax() << "\n";
        }
    } else if (t == 2) {
        MinHeap h; h.build(v);
        int k = readInt("How many extractions (min) to perform? ");
        for (int i = 0; i < k; ++i) {
            if (h.empty()) { cout << "Heap empty\n"; break; }
            cout << "Extracted min: " << h.extractMin() << "\n";
        }
    } else {
        cout << "Unknown type\n";
    }
}

static void printMenu() {
    cout << "\nHeap / Priority Queue / Heap Sort\n";
    cout << "1) Heap (Max/Min)\n";
    cout << "2) Priority Queue\n";
    cout << "3) Heap Sort\n";
    cout << "0) Exit\n";
}

int main() {
    while (true) {
        printMenu();
        int choice = readInt("Choose: ");
        if (choice == 0) break;
        if (choice == 1) runHeapDemo();
        else if (choice == 2) { PriorityQueue pq; pq.insert(0, 0); pq.extractHighestPriority(); }
        else if (choice == 3) { vector<int> a; heapSort(a); }
        else cout << "Unknown option\n";
    }
    cout << "Goodbye!\n";
    return 0;
}