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
    // Internal struct to store value-priority pairs
    struct PQElement {
        int value;
        int priority;
        PQElement(int v, int p) : value(v), priority(p) {}
    };
    
    // MaxHeap modified to store PQElement
    class PQMaxHeap {
        vector<PQElement> a;
        
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
        void insert(int value, int priority) {
            a.push_back(PQElement(value, priority));
            shiftUp((int)a.size() - 1);
        }
        
        bool empty() const { return a.empty(); }
        
        pair<int, int> extractMax() {
            if (a.empty()) return {INT_MIN, INT_MIN};
            pair<int, int> ans = {a[0].value, a[0].priority};
            a[0] = a.back();
            a.pop_back();
            if (!a.empty()) shiftDown(0);
            return ans;
        }
    };
    
    PQMaxHeap heap;
    
public:
    // Insert a value with its priority
    void insert(int value, int priority) {
        heap.insert(value, priority);
    }
    
    // Extract the element with highest priority
    pair<int, int> extractHighestPriority() {
        if (heap.empty()) {
            cout << "Priority Queue is empty\n";
            return {INT_MIN, INT_MIN};
        }
        auto result = heap.extractMax();
        cout << "Extracted: value = " << result.first << ", priority = " << result.second << "\n";
        return result;
    }
    
    bool empty() const {
        return heap.empty();
    }
};
//---------------------------------------- Heap Sort-----------------------------------------------------------

void heapify(vector<int>&arr,int n,int position){
  int l=2*position+1,
      r=2*position+2,
      max=position;
  
      if(l<n&&arr[l]>arr[max])
      max=l;
      if(r<n&&arr[r]>arr[max])
      max=r;
      if (max!=position){
      swap(arr[position],arr[max]);
      heapify(arr,n,max);
  }
  } 
void buildheap(vector<int>&r){
  for(int i=(r.size()/2)-1;i>=0;i--){
    heapify(r,r.size(),i);
  }


}

static void heapSort(vector<int>&arr){
    buildheap(arr);
    for(int i=arr.size()-1;i>=0;i--){
       swap(arr[0],arr[i]);
       heapify(arr,i,0) ; 


    }
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
