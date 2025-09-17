#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

template<typename T>
class MinHeap {
private:
    vector<T> data;

    void min_heapify(int i, int size) {
        int l = 2*i + 1, r = 2*i + 2, smallest = i;
        if (l < size && data[l] < data[smallest]) smallest = l;
        if (r < size && data[r] < data[smallest]) smallest = r;
        if (smallest != i) {
            swap(data[i], data[smallest]);
            min_heapify(smallest, size);
        }
    }

    void build() {
        for (int i = data.size()/2 - 1; i >= 0; --i)
            min_heapify(i, data.size());
    }

public:
    MinHeap(const vector<T>& vec) : data(vec) { build(); }

    void decrease_key(int i, T key) {
        if (key > data[i]) return; // nuova chiave più grande, ignoriamo
        data[i] = key;
        while (i > 0 && data[(i-1)/2] > data[i]) {
            swap(data[i], data[(i-1)/2]);
            i = (i-1)/2;
        }
    }

    void heapsort() {
        int n = data.size();
        for (int i = n-1; i >= 1; --i) {
            swap(data[0], data[i]);
            min_heapify(0, i);
        }
    }

    void print_heap(ostream& out) const {
        for (auto v : data) out << v << " ";
        out << endl;
    }
};

int main() {
    ifstream in("input.txt");
    ofstream out("output_min.txt");
    vector<int> vals;
    int v;
    while (in >> v) vals.push_back(v);

    MinHeap<int> H(vals);

    out << "Min Heap iniziale:\n"; H.print_heap(out);

    H.decrease_key(3, 30); // esempio
    out << "\nMin Heap dopo decrease_key:\n"; H.print_heap(out);

    H.heapsort();
    out << "\nHeap ordinato decrescente:\n"; H.print_heap(out);

    cout << "Operazioni completate. Controlla output_min.txt\n";
}
