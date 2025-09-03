// indirizzamento aperto
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

template<typename T, typename S>
class item {
public:
    T key;
    S val;

    item(T key, S val) : key(key), val(val) {}
};

template<typename T, typename S>
class hashtable {
public:
    vector<item<T, S>*> table;
    int m;

    hashtable(int m) : m(m) {
        table.resize(m, nullptr); // faccio il resize del vettore in modo che sia di dimensione m e riempito con null
    }

    int hash(T key, int i) {
        return (key + i) % m;
    }

    void insert(item<T, S>* itm) {
        int i = 0;
        while (i < m) {
            int j = hash(itm->key, i);
            if (table[j] == nullptr) {
                table[j] = itm;
                return;
            }
            i++;
        }
        cout << "ERROR: table full, cannot insert key " << itm->key << endl;
    }

    item<T, S>* find(T key) {
        int i = 0;
        while (i < m) {
            int j = hash(key, i);
            if (table[j] == nullptr) return nullptr;
            if (table[j]->key == key) return table[j];
            i++;
        }
        return nullptr;
    }

    void remove(T key) {
        int i = 0;
        while (i < m) {
            int j = hash(key, i);
            if (table[j] == nullptr) return;
            if (table[j]->key == key) {
                delete table[j];
                table[j] = nullptr;
                return;
            }
            i++;
        }
    }

    void print(ofstream& out) {
        for (int i = 0; i < m; i++) {
            if (table[i] != nullptr) {
                out << "CHIAVE: " << table[i]->key << " VALORE: " << table[i]->val << endl;
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
    int key;
    string val;
    char dummy;

    while (in >> dummy >> key >> dummy) { // legge '<' e ','
        getline(in, val, '>');            // legge la stringa fino a '>'
        // Rimuove eventuali spazi
        while (!val.empty() && (val[0] == ' ' || val[0] == '\t')) val.erase(0, 1);
        while (!val.empty() && (val.back() == ' ' || val.back() == '\t')) val.pop_back();

        H.insert(new item<int, string>(key, val));
    }
    in.close();

    item<int, string>* result = H.find(2);

    ofstream out("output.txt");
    if (!out) {
        cerr << "Errore apertura file output\n";
        return 1;
    }

    // Stampa il risultato della ricerca
    if (result != nullptr) {
        out << "L'elemento richiesto ha come chiave: " << result->key
            << " ed il valore: " << result->val << endl;
    } else {
        out << "L'elemento non esiste" << endl;
    }

    // PRIMA della rimozione
    out << "\nTabella PRIMA della rimozione:\n";
    H.print(out);

    // Rimuovi la chiave 1
    H.remove(1);

    // DOPO la rimozione
    out << "\nTabella DOPO la rimozione della chiave 1:\n";
    H.print(out);

    out.close();
    cout << "File output.txt creato correttamente" << endl;

    return 0;
}
