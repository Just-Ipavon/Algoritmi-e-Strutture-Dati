#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
using namespace std;

template<typename K, typename V>
class HashList {
public:
    int m;
    vector<list<pair<K, V>>> table;

    HashList(int size) : m(size), table(size) {}

    int hash(K key) { return key % m; }

    void insert(K key, V val) {
        int idx = hash(key);
        for (auto& item : table[idx]) {
            if (item.first == key) {
                item.second = val; // aggiorna e fine
                return;
            }
        }
        table[idx].push_back({key, val});
    }

    bool contains(K key) {
        int idx = hash(key);
        for (auto& item : table[idx])
            if (item.first == key) return true;
        return false;
    }

    V* find(K key) {
        int idx = hash(key);
        for (auto& item : table[idx]) {
            if (item.first == key) return &(item.second);
        }
        return nullptr;
    }

    void print(ostream& out) {
        for (int i = 0; i < m; i++)
            for (auto& item : table[i])
                out << item.first << " -> " << item.second << "\n";
    }
};

void readFile(HashList<int, string>& H, string file) {
    ifstream in(file);
    int k; string v; char c;
    while(in >> c && c == '<' && in >> k >> c && c == ',') {
        getline(in, v, '>');
        H.insert(k, v);
    }
}

bool disjoint(HashList<int, string>& A, HashList<int, string>& B) {
    for (int i = 0; i < A.m; i++)
        for (auto& row : A.table[i])
            if (B.contains(row.first)) return false;
    return true;
}

int main() {
    int M = 999;
    HashList<int, string> H1(M), H2(M);
    readFile(H1, "input1.txt");
    readFile(H2, "input2.txt");

    ofstream out("output.txt");
    out << (disjoint(H1, H2) ? "Disgiunte\n" : "Non disgiunte\n");

    out << "\nTabella 1\n"; H1.print(out);
    out << "\nTabella 2\n"; H2.print(out);

    cout << "Chiave da cercare in H1: ";
    int k;
    if (cin >> k) {
        string* found = H1.find(k);
        if (found) cout << "Trovato: " << *found << "\n";
        else cout << "Non trovato\n";
    }

    return 0;
}
