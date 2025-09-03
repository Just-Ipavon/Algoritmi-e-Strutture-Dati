#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

template<typename T>
class Node {
public:
    T k;
    Node(T k) : k(k) {}
};

template<typename T>
class MaxHeap {
private:
    vector<Node<T>*> data;
    int heapsize;

    void max_heapify(int i) {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int largest = i;
        if (l < heapsize && data[l]->k > data[largest]->k) largest = l;
        if (r < heapsize && data[r]->k > data[largest]->k) largest = r;
        if (largest != i) {
            swap(data[i], data[largest]);
            max_heapify(largest);
        }
    }

    void build() {
        heapsize = (int)data.size();
        for (int i = heapsize / 2 - 1; i >= 0; --i)
            max_heapify(i);
    }

public:
    MaxHeap(vector<Node<T>*>& vec) : data(vec), heapsize(vec.size()) {
        build();
    }

    // INCREASE_KEY: aumenta la chiave dell'elemento in posizione i e riaggiusta il MaxHeap
    void increase_key(int i, T key) {
        if (i < 0 || i >= heapsize) {
            cerr << "Indice fuori range!" << endl;
            return;
        }
        if (key < data[i]->k) {
            cerr << "Nuova chiave più piccola della chiave corrente!" << endl;
            return;
        }
        data[i]->k = key;
        // Risaliamo nella heap finché la proprietà del MaxHeap non è rispettata
        while (i > 0 && data[(i - 1) / 2]->k < data[i]->k) {
            swap(data[i], data[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    // HEAPSORT che ordina in ordine crescente (usiamo MaxHeap)
    void heapsort() {
        build();
        int original_size = heapsize;
        for (int i = heapsize - 1; i >= 1; --i) {
            swap(data[0], data[i]);
            heapsize--;
            max_heapify(0);
        }
        heapsize = original_size;
    }

    void print_heap(ostream& out) const {
        for (auto n : data) out << n->k << " ";
        out << endl;
    }
};

int main() {
    ifstream in("input.txt");
    ofstream out("output_max.txt");
    if (!in || !out) {
        cerr << "Errore apertura file input/output\n";
        return 1;
    }

    int val;
    vector<Node<int>*> nodes;

    while (in >> val) nodes.push_back(new Node<int>(val));
    in.close();

    MaxHeap<int> H(nodes);

    out << "Max Heap iniziale:\n";
    H.print_heap(out);

    // Supponiamo di chiamare increase_key sull'indice 5 con nuova chiave 220000
    int increase_index = 5;
    int new_key = 220000;

    H.increase_key(increase_index, new_key);
    out << "\nMax Heap dopo increase_key(" << increase_index << ", " << new_key << "):\n";
    H.print_heap(out);

    H.heapsort();
    out << "\nMax Heap dopo heapsort (ordinato crescente):\n";
    H.print_heap(out);

    out.close();

    // Pulizia memoria
    for (auto n : nodes) delete n;

    cout << "Operazioni completate. Controlla output_max.txt\n";
    return 0;
}
