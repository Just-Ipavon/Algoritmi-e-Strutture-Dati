#include <iostream>
#include <vector>

using namespace std;


template <class T>
class MaxHeap {
private:
    vector<T> items;
    int heapsize;

    int get_left(int i) {return (i * 2) + 1;}
    int get_right(int i) {return (i * 2) + 2;}
    int get_parent(int i) {return (i - 1) / 2;}

    void heapify_down(int i) {
        int max = i;
        int left = get_left(i);
        int right = get_right(i);

        if (left < heapsize && items[left] > items[max])
            max = left;
        if (right < heapsize && items[right] > items[max])
            max = right;

        if (max != i) {
            swap(items[i], items[max]);
            heapify_down(max);
        }
    }

    void heapify_up(int i) {
        int parent = get_parent(i);
        if (parent >= 0 && items[i] > items[parent]) {
            swap(items[i], items[parent]);
            heapify_up(parent);
        }
    }
public:
    T peek_max() {
        if (heapsize <= 0) throw runtime_error("Can't return root. Heap is empty");
        return items[0];
    }

    T extract_root() {
        if (heapsize <= 0) throw runtime_error("Can't extract root. Heap is empty");

        T root = items[0];
        swap(items[0], items[heapsize - 1]);
        items.pop_back();
        heapsize--;
        heapify_down(0);
        return root;
    }

    void insert(T new_item) {
        items.push_back(new_item);
        heapsize++;
        heapify_up(heapsize - 1);
    }

    void increase_priority(int i, T new_priority) {
        if (i < 0 || i >= heapsize) throw runtime_error("Can't increase priority. Given index is out of range");
        else if (new_priority < items[i]) throw runtime_error("Can't increase priority. Given priority can't be less than current one");

        items[i] = new_priority;
        heapify_up(i);
    }

    void heapsort() {
        for (int i = heapsize - 1; i >= 0; i--) {
            swap(items[0], items[i]);
            heapsize--;
            heapify_down(0);
        }
    }

    int size() {return heapsize;}

    bool empty() {return items.empty();}

    void print() {
        for (auto& item : items) {
            cout << item << " ";
        }
        cout << endl;
    }

    MaxHeap() : heapsize(0) {}
    MaxHeap(vector<T>& items) : items(items), heapsize(items.size()) {
        for (int i = (heapsize / 2) - 1; i >= 0; i--) {
            heapify_down(i);
        }
    }
};