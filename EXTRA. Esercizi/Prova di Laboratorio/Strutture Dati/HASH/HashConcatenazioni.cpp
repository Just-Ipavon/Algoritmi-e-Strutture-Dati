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
    vector<list<item<T, S>>> table; // Ogni cella è una lista
    int m;

    hashtable(int m) : m(m) {
        table.resize(m);
    }

    // Funzione hash base
    int hash(T key) {
        return key % m;
    }

    void insert(item<T, S> itm) {
        int idx = hash(itm.key);
        // Aggiorna valore se chiave già esistente
        for (auto& existing : table[idx]) {
            if (existing.key == itm.key) {
                existing.val = itm.val;
                return;
            }
        }
        table[idx].push_back(itm);
    }

    item<T, S>* find(T key) {
        int idx = hash(key);
        for (auto& itm : table[idx]) {
            if (itm.key == key) {
                return &itm;
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

    void print(ofstream& out) {
        for (int i = 0; i < m; i++) {
            for (const auto& itm : table[i]) {
                out << "CHIAVE: " << itm.key << " VALORE: " << itm.val << endl;
            }
        }
    }
};

int main() {
    ifstream in("hashstringa.txt");
    if (!in) {
        cerr << "Errore apertura file input\n";
        return 1;
    }

    hashtable<int, string> H(999);

    char dummy;
    int key;
    string val;

    while (in >> dummy >> key >> dummy) { // legge '<' key ','
        getline(in, val, '>');            // legge fino a '>'
        while (!val.empty() && (val[0] == ' ' || val[0] == '\t')) val.erase(0, 1);
        while (!val.empty() && (val.back() == ' ' || val.back() == '\t')) val.pop_back();

        item<int, string> itm(key, val);
        H.insert(itm);
    }
    in.close();

    // Test ricerca e rimozione
    item<int, string>* result = H.find(1);

    ofstream out("output.txt");
    if (!out) {
        cerr << "Errore apertura file output\n";
        return 1;
    }

    if (result != nullptr) {
        out << "L'elemento richiesto ha come chiave: " << result->key << " ed il valore: " << result->val << endl;
    } else {
        out << "L'elemento non esiste" << endl;
    }

    H.remove(2); // Rimuovi la chiave 2
    H.print(out); // Stampa il contenuto della tabella

    out.close();
    cout << "File output.txt creato correttamente" << endl;

    return 0;
}
