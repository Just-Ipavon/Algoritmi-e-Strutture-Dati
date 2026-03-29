#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


template<typename T>
class MaxHeap {
private:
    vector<T> data;
    inline int left(int i) { return 2*i + 1; }
    inline int right(int i) { return 2*i + 2; }
    inline int parent(int i) { return (i-1)/2; }

    void heapify(int i, int size) {
        int l = left(i), r = right(i), largest = i;
        if (l < size && data[l] > data[largest]) largest = l;
        if (r < size && data[r] > data[largest]) largest = r;
        
        if (largest != i) {
            swap(data[i], data[largest]);
            heapify(largest, size);
        }
    }

public:
    MaxHeap(const vector<T>& vec) : data(vec) { 
        for (int i = data.size()/2 - 1; i >= 0; --i)
            heapify(i, data.size());
    }

    void increase_key(int i, T key) {
        if (key < data[i]) return; // ignoriamo se più piccola
        data[i] = key;
        
        while (i > 0 && data[parent(i)] < data[i]) {
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

    MaxHeap<int> H(vals);

    ofstream out("output_max.txt");
    out << "Max Heap iniziale:\n"; 
    H.print(out);

    H.increase_key(3, 50); // Mettiamo 50 in posizione 3 come test
    out << "Max Heap dopo increase_key:\n"; 
    H.print(out);

    H.heapsort();
    out << "Heap ordinato crescente:\n"; 
    H.print(out);

    cout << "Operazioni completate. Controlla output_max.txt\n";
    return 0;
}
