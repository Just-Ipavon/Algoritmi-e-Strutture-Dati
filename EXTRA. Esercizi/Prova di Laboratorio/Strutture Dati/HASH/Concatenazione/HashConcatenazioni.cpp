#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>

using namespace std;

// Definizione della coppia chiave-valore
template<typename T, typename S>
class item {
public:
    T key;
    S val;

    item(T key, S val) : key(key), val(val) {}
};

// Hash table con concatenamento
template<typename T, typename S>
class hashtable {
public:
    vector<list<item<T, S>>> table;
    int m;

    hashtable(int m) : m(m) {
        table.resize(m);
    }

    int hash(T key) {
        return key % m;
    }

    void insert(item<T, S> itm) {
        int idx = hash(itm.key);
        for (auto& existing : table[idx]) {
            if (existing.key == itm.key) {
                existing.val = itm.val;
                return;
            }
        }
        table[idx].push_back(itm);
    }

    item<T, S>* find(T key) const {
        int idx = hash(key);
        for (const auto& itm : table[idx]) {
            if (itm.key == key) {
                return const_cast<item<T, S>*>(&itm); // safe per uso semplice
            }
        }
        return nullptr;
    }

    void remove(T key) {
        int idx = hash(key);
        for (auto it = table[idx].begin(); it != table[idx].end(); ++it) {
            if (it->key == key) {
                table[idx].erase(it);
                return;
            }
        }
    }

    void print(ofstream& out) const {
        for (int i = 0; i < m; i++) {
            for (const auto& itm : table[i]) {
                out << "CHIAVE: " << itm.key << " VALORE: " << itm.val << endl;
            }
        }
    }
};

// Funzione per leggere un file e popolare una hashtable
void leggi_file(hashtable<int, string>& H, const string& filename) {
    ifstream in(filename);
    if (!in) {
        cerr << "Errore apertura file " << filename << endl;
        return;
    }

    int key;
    string val;
    char dummy1, dummy2, dummy3;

    while (in >> dummy1 >> key >> dummy2) {
        in >> val;
        in >> dummy3;
        H.insert(item<int, string>(key, val));
    }

    in.close();
}

// Funzione per verificare se due tabelle hash sono disgiunte
template<typename T, typename S>
bool disjoint(const hashtable<T, S>& H1, const hashtable<T, S>& H2) {
    for (int i = 0; i < H1.m; ++i) {
        for (const auto& itm : H1.table[i]) {
            if (H2.find(itm.key)) {
                return false; // Chiave in comune trovata
            }
        }
    }
    return true;
}

int main() {
    hashtable<int, string> H1(999);
    hashtable<int, string> H2(999);

    leggi_file(H1, "input1.txt");
    leggi_file(H2, "input2.txt");

    ofstream out("output.txt");
    if (!out) {
        cerr << "Errore apertura file output\n";
        return 1;
    }

    if (disjoint(H1, H2)) {
        out << "Le due tabelle hash sono disgiunte." << endl;
    } else {
        out << "Le due tabelle hash NON sono disgiunte." << endl;
    }

    out << "\nContenuto della prima tabella:\n";
    H1.print(out);
    out << "\nContenuto della seconda tabella:\n";
    H2.print(out);

    out.close();
    cout << "File output.txt creato correttamente" << endl;

    return 0;
}
