#include <iostream>
#include <list>
#include <vector>
using namespace std;

template <class K, class V>
class Entry {
public:
    K key;
    V value;

    Entry(K k, V v) : key(k), value(v) {}
};

template <class K, class V>
ostream& operator<<(ostream& os, const Entry<K, V>& entry) {
    os << "(" << entry.key << ", " << entry.value << ")";
    return os;
}

template <class K, class V>
class HashTable {
private:
    vector<list<Entry<K, V>>> table;
    int capacity;

    int hash(K key) const {
        return static_cast<int>(key) % capacity;
    }

public:
    HashTable(int cap) : capacity(cap) {
        table.resize(capacity);
    }

    void insert(K key, V value) {
        int idx = hash(key);
        for (auto& entry : table[idx]) {
            if (entry.key == key) {
                entry.value = value;  // sovrascrive valore esistente
                return;
            }
        }
        table[idx].emplace_back(key, value);
    }

    V search(K key) const {
        int idx = hash(key);
        for (const auto& entry : table[idx]) {
            if (entry.key == key)
                return entry.value;
        }
        cout << "Key not found: " << key << endl;
        return V();
    }

    void remove(K key) {
        int idx = hash(key);
        for (auto it = table[idx].begin(); it != table[idx].end(); ++it) {
            if (it->key == key) {
                table[idx].erase(it);
                return;
            }
        }
        cout << "Key not found (remove): " << key << endl;
    }

    void display() const {
        for (int i = 0; i < capacity; ++i) {
            cout << "[" << i << "]: ";
            for (const auto& entry : table[i])
                cout << entry << " ";
            cout << endl;
        }
    }
};

int main() {
    HashTable<int, string> ht(10);

    ht.insert(1, "uno");
    ht.insert(2, "due");
    ht.insert(3, "tre");
    ht.insert(4, "quattro");
    ht.insert(5, "cinque");
    ht.insert(10, "dieci");
    ht.insert(20, "venti");

    ht.display();

    cout << "\nValore associato a 3: " << ht.search(3) << endl;

    ht.remove(10);
    ht.remove(42); // non esiste

    cout << "\nDopo la rimozione:\n";
    ht.display();

    return 0;
}
