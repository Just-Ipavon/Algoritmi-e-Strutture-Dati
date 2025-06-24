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
        table.resize(m, nullptr);
    }

    int hash(T key, int i) {
        // Funzione hash semplice: (key + i) modulo m
        return (key + i) % m;
    }

    void insert(item<T, S>* itm) {
        int i = 0;
        while (i < m) {
            int j = hash(itm->key, i);
            if (table[j] == nullptr) {
                table[j] = itm;
                return;
            } else {
                i++;
            }
        }
        cout << "ERROR: table full, cannot insert key " << itm->key << endl;
    }

    item<T, S>* find(T key) {
        int i = 0;
        while (i < m) {
            int j = hash(key, i);
            if (table[j] == nullptr) {
                return nullptr; // Non trovato
            }
            if (table[j]->key == key) {
                return table[j];
            }
            i++;
        }
        return nullptr;
    }

    void remove(T key) {
        int i = 0;
        while (i < m) {
            int j = hash(key, i);
            if (table[j] == nullptr) return; // Non trovato
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

    // Per esempio, file con righe tipo:
    // <1,hello>
    // <2,world>
    // Leggo delimitatori '<' e ',' e '>' per leggere key e val
    hashtable<int, string> H(999);
    int key;
    string val;
    char dummy1, dummy2, dummy3; // per leggere < , >



    while (in >> dummy1 >> key >> dummy2) {   // legge '<' key ','
        in >> val;                           // legge la parola dopo la virgola
        in >> dummy3;                       // legge '>'

        cout << "Key: " << key << " Val: " << val << "\n";
    }
    in.close();

    // Test find e rimozione
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

    H.remove(2);
    H.print(out);

    out.close();
    cout << "File output.txt creato correttamente" << endl;

    return 0;
}
