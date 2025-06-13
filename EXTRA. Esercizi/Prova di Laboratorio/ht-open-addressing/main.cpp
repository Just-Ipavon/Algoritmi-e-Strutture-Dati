#include <iostream>
#include <vector>

using namespace std;


enum Status {EMPTY, OCCUPIED, DELETED};

template <class K, class V>
class TableItem {
private:
    K key;
    V value;
    Status status;
public:
    K get_key() {return this->key;}
    V get_value() {return this->value;}
    Status get_status() {return this->status;}

    void set_key(K key) {this->key = key;}
    void set_value(V value) {this->value = value;}
    void set_status(Status status) {this->status = status;}

    TableItem(K key, V value) : key(key), value(value), status(Status::OCCUPIED) {}
    TableItem() : status(Status::EMPTY) {}
};

template <class K, class V>
class HashTable {
private:
    int capacity;
    vector<TableItem<K, V>*> table;

    int h1(K key) {return key % capacity;}
    int h2(K key) {return 1 + (key % (capacity - 1));}
    int hash(K key, int i) {return (h1(key) + (i * h2(key))) % capacity;}
public:
    void insert(K key, V value) {
        int i = 0;
        while (i < capacity) {
            int j = hash(key, i);
            if (table[j]->get_status() == Status::EMPTY || table[j]->get_status() == Status::DELETED) {
                table[j]->set_key(key);
                table[j]->set_value(value);
                table[j]->set_status(Status::OCCUPIED);
                return;
            }
            i++;
        }
        cout << "Can't perform 'insert'. Full capacity reached." << endl;
    }

    V find(K key) {
        int i = 0;

        while(i < capacity) {
            int j = hash(key, i);
            if (table[j]->get_status() == Status::OCCUPIED && table[j]->get_key() == key) {
                return table[j]->get_value();
            } else if (table[j]->get_status() == Status::EMPTY) {
                break;
            }
            i++;
        }
        cout << "Can't find " << key << " in the hash table." << endl;
       return V();
    }

    void remove(K key) {
        int i = 0;

        while(i < capacity) {
            int j = hash(key, i);
            if (table[j]->get_status() == Status::OCCUPIED && table[j]->get_key() == key) {
                table[j]->set_key(K());
                table[j]->set_value(V());
                table[j]->set_status(Status::DELETED);
                return;
            } else if (table[j]->get_status() == Status::EMPTY) {
                break;
            }
            i++;
        }
        cout << "Can't remove " << key << ". key not found in the hash table." << endl;
    }

    HashTable(int capacity) : capacity(capacity) {
        for(int i = 0; i < capacity; i++) {
            table.push_back(new TableItem<K, V>());
        }
    }

    ~HashTable() {
        for (auto item : table) {
            delete item;
        }
    }
};
