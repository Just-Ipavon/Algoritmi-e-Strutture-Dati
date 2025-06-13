#include <iostream>
#include <list>
#include <vector>

using namespace std;


template <class K, class V>
class Entry {
private:
    K key;
    V value;
public:
    K get_key() {return this->key;}
    V get_value() {return this->value;}
    void set_value(V value) {this->value = value;}

    Entry(K key, V value) : key(key), value(value) {}
    ~Entry() {}
};

template <class K, class V>
ostream& operator<<(ostream& os, Entry<K, V>* entry) {
    os << "(" << entry->get_key() << ", " << entry->get_value() << ")";
    return os;
}


template <class K, class V>
class HashTable {
private:
    vector<list<Entry<K, V>*>> table;

    int hash(K key) {
        return static_cast<int>(key) % table.size();
    }
public:
    void insert(K key, V value) {
        int i = hash(key);
        for (Entry<K, V>* entry : table[i]) {
            if (entry->get_key() == key) {
                entry->set_value(value);
                return;
            }
        }
        table[i].emplace_back(new Entry<K, V>(key, value));
    }

    V search(K key) {
        int i = hash(key);
        for (Entry<K, V>* entry : table[i]) {
            if (entry->get_key() == key) {
                return entry->get_value();
            }
        }
        cout << "key not found in search" << endl;
        return V();
    }

    void remove(K key) {
        int i = hash(key);
        for (auto it = table[i].begin(); it != table[i].end(); it++) {
            if ((*it)->get_key() == key) {
                delete (*it);
                table[i].erase(it);
                return;
            }
        }
        cout << "key not found in remove" << endl;
    }

    void display() {
        for (int i = 0; i < table.size(); i++) {
            cout << "[" << i << "]: ";
            for (Entry<K, V>* entry: table[i]) {
                cout << entry << " ";
            }
            cout << endl;
        }
    }

    HashTable(int capacity) {
        table.resize(capacity);
    }
    ~HashTable() {
        for (auto& lst : table) {
            for (Entry<K, V>* entry : lst) {
                delete entry;
            }
        }
    }
};


int main(int argc, char** argv) {
    HashTable<int, string> ht(10);

    ht.insert(1, "uno");
    ht.insert(2, "due");
    ht.insert(3, "tre");
    ht.insert(4, "quattro");
    ht.insert(5, "cinque");
    ht.insert(10, "dieci");
    ht.insert(20, "venti");


    ht.display();
}