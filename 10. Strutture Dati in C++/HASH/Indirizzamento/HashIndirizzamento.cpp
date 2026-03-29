#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// Lo stato DELETED (Tombstone) permette di cancellare chiavi 
// senza bloccare la successiva ricerca
enum Status { EMPTY, ACTIVE, DELETED };

template<typename K, typename V>
struct Item {
    K key;
    V val;
    Status stat = EMPTY;
    Item() {}
    Item(K k, V v) : key(k), val(v), stat(ACTIVE) {}
};

template<typename K, typename V>
class HashOpen {
public:
    int m;
    vector<Item<K,V>> table;

    HashOpen(int size) : m(size), table(size) {}

    int hash(K key) { return key % m; }

    void insert(K key, V val) {
        int idx = hash(key);
        int start = idx;

        // Invece di fermarci solo quando è vuoto, sovrascriviamo se vuoto o cancellato.
        while (table[idx].stat != EMPTY && table[idx].stat != DELETED) {
            if (table[idx].key == key && table[idx].stat == ACTIVE) {
                table[idx].val = val; // aggiornamento
                return;
            }
            idx = (idx + 1) % m;
            if (idx == start) { cerr << "Tabella piena!\n"; return; }
        }
        table[idx] = Item<K,V>(key, val);
    }

    V* find(K key) {
        int idx = hash(key);
        int start = idx;

        while (table[idx].stat != EMPTY) {
            if (table[idx].stat == ACTIVE && table[idx].key == key) 
                return &(table[idx].val);
            idx = (idx + 1) % m; // Saltiamo i tombstone e proseguiamo la ricerca
            if (idx == start) break;
        }
        return nullptr;
    }

    bool remove(K key) {
        int idx = hash(key);
        int start = idx;

        while (table[idx].stat != EMPTY) {
            if (table[idx].stat == ACTIVE && table[idx].key == key) {
                table[idx].stat = DELETED; // Contrassegna come rimosso
                return true;
            }
            idx = (idx + 1) % m;
            if (idx == start) break;
        }
        return false;
    }

    void print(ostream& out) {
        for (int i = 0; i < m; i++)
            if (table[i].stat == ACTIVE)
                out << table[i].key << " -> " << table[i].val << "\n";
    }
};

void leggiFile(HashOpen<int, string>& H, string file) {
    ifstream in(file);
    int k; string v; char c;
    while (in >> c && c == '<' && in >> k >> c && c == ',') {
        getline(in, v, '>');
        H.insert(k, v);
    }
}

int main() {
    int M = 999;
    HashOpen<int, string> H1(M);
    leggiFile(H1, "input.txt");

    ofstream out("output.txt");
    out << "Tabella Hash ad Indirizzamento Aperto:\n"; 
    H1.print(out);

    cout << "Chiave da cercare: ";
    int k;
    if (cin >> k) {
        string* val = H1.find(k);
        if (val) cout << "Trovato: " << *val << "\n";
        else cout << "Non trovato.\n";
    }

    cout << "Chiave da eliminare: ";
    if (cin >> k) {
        if (H1.remove(k)) cout << "Eliminata con successo.\n";
        else cout << "Non trovata.\n";
        
        // La prova del 9 del tombstone
        if (H1.find(k)) cout << "ERRORE: La chiave e' ancora presente.\n";
        else cout << "OK: La chiave non si trova piu' con find().\n";
    }

    return 0;
}
