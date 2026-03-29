#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

template<typename T>
class MinHeap {
private:
    vector<T> data;
    inline int left(int i) { return 2*i + 1; }
    inline int right(int i) { return 2*i + 2; }
    inline int parent(int i) { return (i-1)/2; }

    void heapify(int i, int size) {
        int l = left(i), r = right(i), smallest = i;
        if (l < size && data[l] < data[smallest]) smallest = l;
        if (r < size && data[r] < data[smallest]) smallest = r;
        
        if (smallest != i) {
            swap(data[i], data[smallest]);
            heapify(smallest, size);
        }
    }

public:
    MinHeap(const vector<T>& vec) : data(vec) { 
        for (int i = data.size()/2 - 1; i >= 0; --i)
            heapify(i, data.size());
    }

    void decrease_key(int i, T key) {
        if (key > data[i]) return; // ignoriamo se più grande
        data[i] = key;
        while (i > 0 && data[parent(i)] > data[i]) {
            swap(data[i], data[parent(i)]);
            i = parent(i);
        }
    }

    void heapsort() {
        int n = data.size();
        for (int i = n-1; i >= 1; --i) {
            swap(data[0], data[i]);
            heapify(0, i);
        }
    }

    void print(ostream& out) const {
        for (auto v : data) out << v << " ";
        out << "\n";
    }
};

int main() {
    ifstream in("input.txt");
    vector<int> vals;
    if(in) {
        int v;
        while (in >> v) vals.push_back(v);
    }

    if (vals.empty()) {
        cout << "Nessun valore in input.txt\n";
        return 1;
    }

    MinHeap<int> H(vals);

    ofstream out("output_min.txt");
    out << "Min Heap iniziale:\n"; 
    H.print(out);

    H.decrease_key(3, 30); // esempio test
    out << "Min Heap dopo decrease_key:\n"; 
    H.print(out);

    H.heapsort();
    out << "Heap ordinato decrescente:\n"; 
    H.print(out);

    cout << "Operazioni completate. Controlla output_min.txt\n";
    return 0;
}
