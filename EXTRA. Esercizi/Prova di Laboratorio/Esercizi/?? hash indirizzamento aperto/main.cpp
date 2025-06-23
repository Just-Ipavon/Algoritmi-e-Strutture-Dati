#include <iostream>
#include <vector>

using namespace std;

enum class Status { EMPTY, OCCUPIED, DELETED };

template <class K, class V>
class TableItem {
public:
    K key;
    V value;
    Status status;

    TableItem() : status(Status::EMPTY) {}
    TableItem(K k, V v) : key(k), value(v), status(Status::OCCUPIED) {}
};

template <class K, class V>
class HashTable {
private:
    int capacity;
    vector<TableItem<K, V>> table;

    int h1(K key) const { return key % capacity; }
    int h2(K key) const { return 1 + (key % (capacity - 1)); }
    int hash(K key, int i) const { return (h1(key) + i * h2(key)) % capacity; }

public:
    HashTable(int cap) : capacity(cap), table(cap) {}

    void insert(K key, V value) {
        for (int i = 0; i < capacity; ++i) {
            int idx = hash(key, i);
            if (table[idx].status == Status::EMPTY || table[idx].status == Status::DELETED) {
                table[idx] = TableItem<K, V>(key, value);
                return;
            }
        }
        cout << "Insert failed: table is full.\n";
    }

    V find(K key) const {
        for (int i = 0; i < capacity; ++i) {
            int idx = hash(key, i);
            if (table[idx].status == Status::EMPTY)
                break;
            if (table[idx].status == Status::OCCUPIED && table[idx].key == key)
                return table[idx].value;
        }
        cout << "Find failed: key " << key << " not found.\n";
        return V();
    }

    void remove(K key) {
        for (int i = 0; i < capacity; ++i) {
            int idx = hash(key, i);
            if (table[idx].status == Status::EMPTY)
                break;
            if (table[idx].status == Status::OCCUPIED && table[idx].key == key) {
                table[idx].status = Status::DELETED;
                return;
            }
        }
        cout << "Remove failed: key " << key << " not found.\n";
    }

    void display() const {
        for (int i = 0; i < capacity; ++i) {
            cout << "[" << i << "]: ";
            if (table[i].status == Status::OCCUPIED)
                cout << "(" << table[i].key << ", " << table[i].value << ")";
            else if (table[i].status == Status::DELETED)
                cout << "<deleted>";
            else
                cout << "<empty>";
            cout << endl;
        }
    }
};



int main() {
    HashTable<int, string> ht(11);

    ht.insert(1, "uno");
    ht.insert(12, "dodici");
    ht.insert(23, "ventitré");
    ht.display();

    cout << "\nTrovo chiave 12: " << ht.find(12) << endl;
    ht.remove(12);
    ht.display();

    return 0;
}
