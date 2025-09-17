#include <iostream>
#include <fstream>
#include <string>
using namespace std;

template<typename K, typename V>
struct Oggetto {
    K chiave;
    V valore;
    bool occupied;

    Oggetto() : occupied(false) {}
    Oggetto(K k, V v) : chiave(k), valore(v), occupied(true) {}
};

template<typename K, typename V>
class Hash {
    int m; // dimensione tabella
    Oggetto<K,V>* tabella;

    size_t hash(K key) { return key % m; }

public:
    Hash(int size) : m(size) { tabella = new Oggetto<K,V>[m]; }

    void insert(K key, V value) {
        size_t idx = hash(key);
        size_t start = idx;
        while(tabella[idx].occupied) {
            idx = (idx + 1) % m;
            if(idx == start) { cerr << "Tabella piena!\n"; return; }
        }
        tabella[idx] = Oggetto<K,V>(key, value);
    }

    void stampa(ofstream& out) {
        for(int i = 0; i < m; i++) {
            if(tabella[i].occupied)
                out << tabella[i].chiave << " -> " << tabella[i].valore << "\n";
        }
    }

    void leggiFile(const string& file) {
        ifstream in(file);
        int k;
        string v;
        char c;
        while(in >> c && c == '<' && in >> k >> c && c == ',') {
            getline(in, v, '>');
            insert(k, v);
        }
    }
};

int main() {
    Hash<int,string> H(10); // hash table dimensione 10
    H.leggiFile("input.txt");

    ofstream out("output.txt");
    H.stampa(out);
    out.close();

    cout << "Hash table salvata su output.txt\n";
    return 0;
}
