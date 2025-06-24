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
class MinHeap {
private:
    vector<Node<T>*> data;
    int heapsize;

    void min_heapify(int i) {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int smallest = i;
        if (l < heapsize && data[l]->k < data[smallest]->k) smallest = l;
        if (r < heapsize && data[r]->k < data[smallest]->k) smallest = r;
        if (smallest != i) {
            swap(data[i], data[smallest]);
            min_heapify(smallest);
        }
    }

    void build() {
        heapsize = (int)data.size();
        for (int i = heapsize / 2 - 1; i >= 0; --i)
            min_heapify(i);
    }

public:
    MinHeap(vector<Node<T>*>& vec) : data(vec), heapsize(vec.size()) {
        build();
    }

    // DECREASE_KEY: diminuisce la chiave dell'elemento in posizione i e riaggiusta il MinHeap
    void decrease_key(int i, T key) {
        if (i < 0 || i >= heapsize) {
            cerr << "Indice fuori range!" << endl;
            return;
        }
        if (key > data[i]->k) {
            cerr << "Nuova chiave più grande della chiave corrente!" << endl;
            return;
        }
        data[i]->k = key;
        // Risaliamo nella heap finché la proprietà del MinHeap non è rispettata
        while (i > 0 && data[(i - 1) / 2]->k > data[i]->k) {
            swap(data[i], data[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    // HEAPSORT che ordina in ordine decrescente (usiamo MinHeap)
    void heapsort() {
        build();
        int original_size = heapsize;
        for (int i = heapsize - 1; i >= 1; --i) {
            swap(data[0], data[i]);
            heapsize--;
            min_heapify(0);
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
    ofstream out("output_min.txt");
    if (!in || !out) {
        cerr << "Errore apertura file input/output\n";
        return 1;
    }

    int val;
    vector<Node<int>*> nodes;

    while (in >> val) nodes.push_back(new Node<int>(val));
    in.close();

    MinHeap<int> H(nodes);

    out << "Min Heap iniziale:\n";
    H.print_heap(out);

    // Supponiamo di chiamare decrease_key sull'indice 3 (per esempio)
    // con nuova chiave 30 (decremento chiave)
    // Se vuoi index 53, assicurati che ci siano almeno 54 elementi in input.txt
    int decrease_index = 3;
    int new_key = 30;

    H.decrease_key(decrease_index, new_key);
    out << "\nMin Heap dopo decrease_key(" << decrease_index << ", " << new_key << "):\n";
    H.print_heap(out);

    // Heapsort in ordine decrescente
    H.heapsort();
    out << "\nMin Heap dopo heapsort (ordinato decrescente):\n";
    H.print_heap(out);

    out.close();

    // Pulizia memoria
    for (auto n : nodes) delete n;

    cout << "Operazioni completate. Controlla output_min.txt\n";
    return 0;
}
