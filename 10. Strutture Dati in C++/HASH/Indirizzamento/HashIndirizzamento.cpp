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

// Funzione di lettura del file, adattata dal primo codice
void leggiFile(hashtable<int,string>& H, string file){
    ifstream in(file);
    int k;
    string v;
    char c;
    while(in >> c && c == '<' && in >> k >> c && c == ','){
        getline(in, v, '>');
        H.insert(new item<int, string>(k,v));
    }
    in.close();
}


int main() {
    hashtable<int, string> H(999);
    
    leggiFile(H, "hashstringa.txt");

    item<int, string>* result = H.find(2);

    ofstream out("output.txt");

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