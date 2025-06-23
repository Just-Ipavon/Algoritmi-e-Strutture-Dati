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
        for (int i = heapsize / 2 - 1; i >= 0; --i)
            min_heapify(i);
    }

public:
    MinHeap(vector<Node<T>*>& vec) : data(vec), heapsize(vec.size()) {
        build();
    }

    void decrease(T val, int i) {
        if (i < 0 || i >= heapsize || val > data[i]->k) {
            cerr << "Invalid decrease request." << endl;
            return;
        }
        data[i]->k = val;
        while (i > 0 && data[(i - 1) / 2]->k > data[i]->k) {
            swap(data[i], data[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    void heapsort() {
        build();
        for (int i = heapsize - 1; i >= 1; --i) {
            swap(data[0], data[i]);
            --heapsize;
            min_heapify(0);
        }
    }

    vector<Node<T>*> getNodes() const { return data; }
};

int main() {
    ifstream in("input.txt");
    ofstream out("output_min.txt");
    int val;
    vector<Node<int>*> nodes;

    while (in >> val) nodes.push_back(new Node<int>(val));

    MinHeap<int> H(nodes);
    out << "Min Heap iniziale:\n";
    for (auto n : H.getNodes()) out << n->k << " ";
    out << "\n\nHeap Sort:\n";
    H.heapsort();
    for (auto n : H.getNodes()) out << n->k << " ";
    out << "\n\nDecrease:\n";
    H.decrease(-100, 5);
    for (auto n : H.getNodes()) out << n->k << " ";

    in.close();
    out.close();
    return 0;
}
