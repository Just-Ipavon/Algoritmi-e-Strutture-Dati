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
class HashTable {
private:
    vector<list<Entry<K, V>*>> table;
    int size;

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
        size++;
    }

    V search(K key) {
        int i = hash(key);
        for (Entry<K, V>* entry : table[i]) {
            if (entry->get_key() == key) {
                return entry->get_value();
            }
        }
        cerr << "Error during 'search'. Key not found." << endl;
        exit(1);
    }

    void remove(K key) {
        int i = hash(key);
        for(auto it = table[i].begin(); it != table[i].end(); it++) {
            if ((*it)->get_key() == key) {
                delete *it;
                table[i].erase(it);
                size--;
                return;
            }
        }

        cerr << "Error during 'remove'. Key not found." << endl;
        exit(2);
    }

    HashTable(int table_size) : size(0) {
        table.resize(table_size);
    }
    ~HashTable() {
        for (auto& bucket : table) {
            for (Entry<K, V>* entry : bucket) {
                delete entry;
            }
            bucket.clear();
        }
        table.clear();
    }
};


int main() {
    HashTable<int, string> ht(10);

    cout << "Inserting (1, 'one'), (2, 'two'), (3, 'three')..." << endl;
    ht.insert(1, "one");
    ht.insert(2, "two");
    ht.insert(3, "three");

    cout << "Searching for keys 1, 2, 3:" << endl;
    cout << "1: " << ht.search(1) << endl;
    cout << "2: " << ht.search(2) << endl;
    cout << "3: " << ht.search(3) << endl;

    cout << "Updating key 2 to 'TWO'..." << endl;
    ht.insert(2, "TWO");
    cout << "2: " << ht.search(2) << endl;

    cout << "Removing key 1..." << endl;
    ht.remove(1);

    cout << "Trying to search for key 1 (should cause error):" << endl;
    ht.search(1); // this should print error and exit

    return 0;
}