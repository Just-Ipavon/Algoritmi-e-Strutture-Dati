#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

template<typename T>
class MaxHeap {
private:
    vector<T> data;

    void max_heapify(int i, int size) {
        int l = 2*i + 1, r = 2*i + 2, largest = i;
        if (l < size && data[l] > data[largest]) largest = l;
        if (r < size && data[r] > data[largest]) largest = r;
        if (largest != i) {
            swap(data[i], data[largest]);
            max_heapify(largest, size);
        }
    }

    void build() {
        for (int i = data.size()/2 - 1; i >= 0; --i)
            max_heapify(i, data.size());
    }

public:
    MaxHeap(const vector<T>& vec) : data(vec) { build(); }

    void increase_key(int i, T key) {
        if (key < data[i]) return; // nuova chiave più piccola, ignoriamo
        data[i] = key;
        while (i > 0 && data[(i-1)/2] < data[i]) {
            swap(data[i], data[(i-1)/2]);
            i = (i-1)/2;
        }
    }

    void heapsort() {
        int n = data.size();
        for (int i = n-1; i >= 1; --i) {
            swap(data[0], data[i]);
            max_heapify(0, i);
        }
    }

    void print_heap(ostream& out) const {
        for (auto v : data) out << v << " ";
        out << endl;
    }
};

int main() {
    ifstream in("input.txt");
    ofstream out("output_max.txt");
    if (!in || !out) return 1;

    vector<int> vals;
    int v;
    while (in >> v) vals.push_back(v);

    MaxHeap<int> H(vals);

    out << "Max Heap iniziale:\n"; H.print_heap(out);

    H.increase_key(3, 50); // esempio
    out << "\nMax Heap dopo increase_key:\n"; H.print_heap(out);

    H.heapsort();
    out << "\nHeap ordinato crescente:\n"; H.print_heap(out);

    cout << "Operazioni completate. Controlla output_max.txt\n";
}
