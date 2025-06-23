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
        for (int i = heapsize / 2 - 1; i >= 0; --i)
            max_heapify(i);
    }

public:
    MaxHeap(vector<Node<T>*>& vec) : data(vec), heapsize(vec.size()) {
        build();
    }

    void increase(T val, int i) {
        if (i < 0 || i >= heapsize || val < data[i]->k) {
            cerr << "Invalid increase request." << endl;
            return;
        }
        data[i]->k = val;
        while (i > 0 && data[(i - 1) / 2]->k < data[i]->k) {
            swap(data[i], data[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    void heapsort() {
        build();
        for (int i = heapsize - 1; i >= 1; --i) {
            swap(data[0], data[i]);
            --heapsize;
            max_heapify(0);
        }
    }

    vector<Node<T>*> getNodes() const { return data; }
};

int main() {
    ifstream in("input.txt");
    ofstream out("output_max.txt");
    int val;
    vector<Node<int>*> nodes;

    while (in >> val) nodes.push_back(new Node<int>(val));

    MaxHeap<int> H(nodes);
    out << "Max Heap iniziale:\n";
    for (auto n : H.getNodes()) out << n->k << " ";
    out << "\n\nHeap Sort:\n";
    H.heapsort();
    for (auto n : H.getNodes()) out << n->k << " ";
    out << "\n\nIncrease:\n";
    H.increase(220000, 5);
    for (auto n : H.getNodes()) out << n->k << " ";

    in.close();
    out.close();
    return 0;
}