#include <bits/stdc++.h>
using namespace std;

// ------------ Simple robust integer input (no exceptions needed) ------------
static int readInt(const string &prompt) {
    for (;;) {
        if (!prompt.empty()) cout << prompt;
        int x;
        if (cin >> x) return x;
        cout << "Invalid input. Try again.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// ========================== Core Heap ===========================
class Heap {
    vector<int> a;
    bool isMax; // true => Max-Heap, false => Min-Heap

    bool better(int x, int y) const { return isMax ? (x > y) : (x < y); }

    void shiftUp(int i) {
        while (i > 0) {
            int p = (i - 1) / 2;
            if (!better(a[i], a[p])) break;
            swap(a[i], a[p]);
            i = p;
        }
    }

  void shiftDown(int i,int size=-1) {
        int n = (int)a.size();
        if (size!=-1)
            n=size;
        while (true) {
            int l = 2 * i + 1, r = 2 * i + 2, best = i;
            if (l < n && better(a[l], a[best])) best = l;
            if (r < n && better(a[r], a[best])) best = r;
            if (best == i) break;
            swap(a[i], a[best]);
            i = best;
        }
    }

public:
    explicit Heap(bool asMaxHeap = true) : isMax(asMaxHeap) {}

    void build(const vector<int> &v) {
        a = v;
        heapify();
    }

    void heapify() {
        for (int i = (int)a.size() / 2 - 1; i >= 0; --i) shiftDown(i);
    }
  void heapSortHelper(){

        for(int i=a.size()-1;i>=0;i--){
            swap(a[0],a[i]);
            shiftDown(0,i);
        }
    }
    void print(){
        for (int i = 0; i < a.size(); ++i)
        {
            cout<<a[i]<<' ';
        }
        cout<<endl;
    }

    void insert(int x) {
        a.push_back(x);
        shiftUp((int)a.size() - 1);
    }

    bool empty() const { return a.empty(); }
    int size() const { return (int)a.size(); }

    // Return top element (max for max-heap, min for min-heap). If empty, prints and returns 0.
    int extractTop() {
        if (a.empty()) {
            cout << "Heap is empty. Returning 0 (sentinel).\n";
            return 0;
        }
        int top = a[0];
        a[0] = a.back();
        a.pop_back();
        if (!a.empty()) shiftDown(0);
        return top;
    }

    int top() const { return a.empty() ? 0 : a[0]; }
};

struct MaxHeap {
    Heap h{true};
    void build(const vector<int> &v) { h.build(v); }
    void heapify() { h.heapify(); }
    void insert(int x) { h.insert(x); }
    bool empty() const { return h.empty(); }
    int extractMax() { return h.extractTop(); }
};

struct MinHeap {
    Heap h{false};
    void build(const vector<int> &v) { h.build(v); }
    void heapify() { h.heapify(); }
    void insert(int x) { h.insert(x); }
    bool empty() const { return h.empty(); }
    int extractMin() { return h.extractTop(); }
};

struct PriorityQueue
{
    MaxHeap internalHeap;
    const int ENCODING_MASK = 10000;

    void insert(int value, int priority)
    {
        int encoded = priority * ENCODING_MASK + value;
        internalHeap.insert(encoded);
        cout << "Priority Queue: Inserted (Value: " << value << ", Priority: " << priority << "). Encoded Key: " << encoded << "\n";
    }

    int extractHighestPriority()
    {
        if (internalHeap.empty())
        {
            cout << "Priority Queue: Cannot extract, the queue is empty. Returning 0 (sentinel).\n";
            return 0;
        }
        int encoded = internalHeap.extractMax();

        int extractedValue = encoded % ENCODING_MASK;
        int extractedPriority = encoded / ENCODING_MASK; // For logging

        cout << "Priority Queue: Extracted (Value: " << extractedValue << ", Priority: " << extractedPriority << ").\n";
        return extractedValue;
    }
};

static void heapSort(vector<int> &arr) {
    cout << "[HeapSort] TODO: not implemented yet.\n";
    Heap MaxHeap = Heap();
    MaxHeap.build(arr);
    MaxHeap.heapSortHelper();
    MaxHeap.print();
}

static void runHeapDemo() {
    cout << "\n--- Heap Demo ---\n";
    cout << "1) Max Heap\n2) Min Heap\n";
    int t = readInt("Type: ");

    int n = readInt("Enter number of elements: ");
    while (n <= 0) {
        cout << "Invalid n\n";
        n = readInt("Enter number of elements: ");
    }

    vector<int> v(n);
    cout << "Enter " << n << " integers:\n";
    for (int i = 0; i < n; ++i) v[i] = readInt("");

    if (t == 1) {
        MaxHeap h; h.build(v);
        cout << "Built Max-Heap.\n";
        int q = readInt("How many operations? count: ");
        while (q--) {
            int op = readInt("op (1=insert, 2=extract): ");
            if (op == 1) { int x = readInt("value: "); h.insert(x); }
            else if (op == 2) { cout << "max= " << h.extractMax() << "\n"; }
            else cout << "unknown op\n";
        }
    } else if (t == 2) {
        MinHeap h; h.build(v);
        cout << "Built Min-Heap.\n";
        int q = readInt("How many operations? count: ");
        while (q--) {
            int op = readInt("op (1=insert, 2=extract): ");
            if (op == 1) { int x = readInt("value: "); h.insert(x); }
            else if (op == 2) { cout << "min= " << h.extractMin() << "\n"; }
            else cout << "unknown op\n";
        }
    } else {
        cout << "Unknown type\n";
    }
}

static void runPriorityQueueDemo() {
    cout << "\n--- Priority Queue ---\n";
    PriorityQueue pq;
    int n = readInt("How many items to insert? ");
    while (n-- > 0) {
        int val = readInt("value: ");
        int pr  = readInt("priority: ");
        pq.insert(val, pr);
    }
    int k = readInt("How many extractions? ");
    while (k-- > 0) {
        int x = pq.extractHighestPriority();
        cout << "extracted: " << x << "\n";
    }
}

static void runHeapSortDemo() {

    cout << "\n--- Heap Sort ---\n";
    int n = readInt("Array size: ");
    while (n <= 0) { cout << "Invalid n\n"; n = readInt("Array size: "); }
    vector<int> a(n);
    cout << "Enter " << n << " integers:\n";
    for (int i = 0; i < n; ++i) a[i] = readInt("");
    heapSort(a);


    cout << "After heapSort:\n";
    for (int x : a) cout << x << ' ';
    cout << '\n';
    heapSort(a);
}

static void runPriorityQueue()
{
    PriorityQueue pq;

    int n = readInt("Enter number of elements to insert: ");
    while (n <= 0)
    {
        cout << "Invalid n\n";
        n = readInt("Enter number of elements: ");
    }

    cout << "Enter " << n << " value-priority pairs:\n";
    for (int i = 0; i < n; ++i)
    {
        int value = readInt("Value: ");
        int priority = readInt("Priority: ");
        pq.insert(value, priority);
    }

    cout << "\nExtracting all elements by highest priority:\n";
    // Extract all elements from the queue
    for (int i = 0; i < n; i++)
    {
        int extracted = pq.extractHighestPriority();
        if (extracted == 0)
        {
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
        else if (choice == 2) runPriorityQueueDemo();
        else if (choice == 3) runHeapSortDemo();
        else cout << "Unknown option\n";
    }
    cout << "Goodbye!\n";
    return 0;
}

