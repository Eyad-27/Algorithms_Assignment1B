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
    MaxHeap internalHeap;
    // We use a mask to encode the priority and value. 
    // This assumes priority and value are less than 10000.
    const int ENCODING_MASK = 10000;

    // Inserts an element (value) with a given priority.
    void insert(int value, int priority) {
        // Encode: priority * MASK + value.
        // Higher priority results in a larger encoded key, which MaxHeap will place at the top.
        // If priorities are equal, the higher value will be selected next.
        int encoded = priority * ENCODING_MASK + value;
        internalHeap.insert(encoded);
        cout << "Priority Queue: Inserted (Value: " << value << ", Priority: " << priority << "). Encoded Key: " << encoded << "\n";
    }

    // Extracts the value of the item with the highest priority.
    int extractHighestPriority() {
        if (internalHeap.empty()) {
            cout << "Priority Queue: Cannot extract, the queue is empty. Returning 0 (sentinel).\n";
            return 0; 
        }
        // Extract the maximum encoded key from the MaxHeap
        int encoded = internalHeap.extractMax();
        
        // Decode the original value (LSB) from the encoded key: value = encoded % MASK
        int extractedValue = encoded % ENCODING_MASK;
        int extractedPriority = encoded / ENCODING_MASK; // For logging

        cout << "Priority Queue: Extracted (Value: " << extractedValue << ", Priority: " << extractedPriority << ").\n";
        return extractedValue;
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
static void runPriorityQueue() {
    PriorityQueue pq;
    
    int n = readInt("Enter number of elements to insert: ");
    while (n <= 0) { 
        cout << "Invalid n\n"; 
        n = readInt("Enter number of elements: "); 
    }
    
    cout << "Enter " << n << " value-priority pairs:\n";
    for (int i = 0; i < n; ++i) {
        int value = readInt("Value: ");
        int priority = readInt("Priority: ");
        pq.insert(value, priority);
    }
    
    cout << "\nExtracting all elements by highest priority:\n";
    // Extract all elements from the queue
    for (int i = 0; i < n; i++) {
        int extracted = pq.extractHighestPriority();
        if (extracted == 0) {
            cout << "Queue is empty, stopping extraction.\n";
            break;
        }
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
        else if (choice == 2) runPriorityQueue(); 
        else if (choice == 3) { vector<int> a; heapSort(a); }
        else cout << "Unknown option\n";
    }
    cout << "Goodbye!\n";
    return 0;
}
