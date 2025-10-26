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
    // Internal struct to store value-priority pairs
    struct Item {
        int value;
        int priority;
        Item(int v, int p) : value(v), priority(p) {}
    };

    class MaxHeap {
        vector<Item> a;
        
        void shiftUp(int i) {
            while (i > 0) {
                int p = (i - 1) / 2;
                if (a[p].priority >= a[i].priority) break;
                swap(a[p], a[i]);
                i = p;
            }
        }
        
        void shiftDown(int i) {
            int n = (int)a.size();
            while (true) {
                int l = 2 * i + 1, r = 2 * i + 2, largest = i;
                if (l < n && a[l].priority > a[largest].priority) largest = l;
                if (r < n && a[r].priority > a[largest].priority) largest = r;
                if (largest == i) break;
                swap(a[i], a[largest]);
                i = largest;
            }
        }
        
    public:
        void insert(Item x) { 
            a.push_back(x); 
            shiftUp((int)a.size() - 1); 
        }
        
        bool empty() const { return a.empty(); }
        
        Item extractMax() {
            if (a.empty()) return Item(0, INT_MIN);
            Item ans = a[0];
            a[0] = a.back(); 
            a.pop_back();
            if (!a.empty()) shiftDown(0);
            return ans;
        }
    };

    class MinHeap {
        vector<Item> a;
        void shiftUp(int i) {
            while (i > 0) {
                int p = (i - 1) / 2;
                if (a[p].priority <= a[i].priority) break;
                swap(a[p], a[i]);
                i = p;
            }
        }
        
        void shiftDown(int i) {
            int n = (int)a.size();
            while (true) {
                int l = 2 * i + 1, r = 2 * i + 2, smallest = i;
                if (l < n && a[l].priority < a[smallest].priority) smallest = l;
                if (r < n && a[r].priority < a[smallest].priority) smallest = r;
                if (smallest == i) break;
                swap(a[i], a[smallest]);
                i = smallest;
            }
        }
        
    public:
        void insert(Item x) { 
            a.push_back(x); 
            shiftUp((int)a.size() - 1); 
        }
        
        bool empty() const { return a.empty(); }
        
        Item extractMin() {
            if (a.empty()) return Item(0, INT_MAX);
            Item ans = a[0];
            a[0] = a.back(); 
            a.pop_back();
            if (!a.empty()) shiftDown(0);
            return ans;
        }
    };

    MaxHeap maxHeap;
    MinHeap minHeap;
    bool useMaxHeap; // Flag to determine which heap to use

    // Constructor to set heap type (true for max-heap, false for min-heap)
    PriorityQueue(bool useMax = true) : useMaxHeap(useMax) {}

    void insert(int value, int priority) {
        Item item(value, priority);
        if (useMaxHeap) {
            maxHeap.insert(item);
        } else {
            minHeap.insert(item);
        }
    }

    int extractHighestPriority() {
        if (useMaxHeap) {
            Item item = maxHeap.extractMax();
            return item.value;
        } else {
            Item item = minHeap.extractMin();
            return item.value;
        }
    }

    bool empty() const {
        return useMaxHeap ? maxHeap.empty() : minHeap.empty();
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
    cout << "Choose priority queue type:\n1) Max Priority (highest first)\n2) Min Priority (lowest first)\n";
    int type = readInt("Type: ");
    while (type != 1 && type != 2) {
        cout << "Invalid type. Choose 1 or 2.\n";
        type = readInt("Type: ");
    }
    PriorityQueue pq(type == 1); // true for max-heap, false for min-heap
    
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
    cout << "Extracting elements by " << (type == 1 ? "highest" : "lowest") << " priority:\n";
    while (!pq.empty()) {
        cout << "Extracted value: " << pq.extractHighestPriority() << "\n";
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