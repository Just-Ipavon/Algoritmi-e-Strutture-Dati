#include <iostream>
#include <fstream>
#include <string>
using namespace std;

template<typename T, typename S>
struct Oggetto {
    T chiave;
    S valore;
    bool occupied;

    Oggetto() : occupied(false) {}
    Oggetto(T k, S v) : chiave(k), valore(v), occupied(true) {}
};

template<typename T, typename S>
class Hash {
public:
    int m;
    Oggetto<T,S>* tabella;

    Hash(int size) : m(size) {
        tabella = new Oggetto<T,S>[m];
    }

    int hash(T chiave) { return chiave % m; }

    void insert(T chiave, S valore) {
        int idx = hash(chiave);
        int start = idx;

        while (tabella[idx].occupied) {
            if (tabella[idx].chiave == chiave) {
                tabella[idx].valore = valore;
                return;
            }
            idx = (idx + 1) % m;
            if (idx == start) {
                cerr << "Tabella piena!\n";
                return;
            }
        }
        tabella[idx] = Oggetto<T,S>(chiave, valore);
    }

    S* find(T chiave) {
        int idx = hash(chiave);
        int start = idx;

        while (tabella[idx].occupied) {
            if (tabella[idx].chiave == chiave) return &(tabella[idx].valore);
            idx = (idx + 1) % m;
            if (idx == start) break;
        }
        return nullptr;
    }

    bool remove(T chiave) {
        int idx = hash(chiave);
        int start = idx;

        while (tabella[idx].occupied) {
            if (tabella[idx].chiave == chiave) {
                tabella[idx].occupied = false; 
                return true;
            }
            idx = (idx + 1) % m;
            if (idx == start) break;
        }
        return false;
    }

    void stampa(ofstream& out) {
        for (int i = 0; i < m; i++)
            if (tabella[i].occupied)
                out << tabella[i].chiave << " -> " << tabella[i].valore << "\n";
    }

    void leggiFile(const string& file) {
        ifstream in(file);
        int k;
        string v;
        char c;
        while (in >> c && c == '<' && in >> k >> c && c == ',') {
            getline(in, v, '>');
            insert(k, v);
        }
    }
};

int main() {
    int M = 999;
    Hash<int,string> H1(M);

    H1.leggiFile("input.txt");

    ofstream out("output.txt");

    out << "\nTabella 1\n"; 
    H1.stampa(out);

    int chiaveDaCercare;
    cout << "Inserisci la chiave da cercare: ";
    cin >> chiaveDaCercare;

    string* valoreTrovato = H1.find(chiaveDaCercare);
    if (valoreTrovato)
        cout << "Trovato! La chiave " << chiaveDaCercare << " ha valore: " << *valoreTrovato << "\n";
    else
        cout << "La chiave " << chiaveDaCercare << " non e' stata trovata nella tabella.\n";

    // PROVA DELETE
    int chiaveDaEliminare;
    cout << "Inserisci la chiave da eliminare: ";
    cin >> chiaveDaEliminare;

    if (H1.remove(chiaveDaEliminare))
        cout << "Chiave " << chiaveDaEliminare << " eliminata con successo!\n";
    else
        cout << "Chiave " << chiaveDaEliminare << " non trovata.\n";

    // Verifica dopo la cancellazione
    valoreTrovato = H1.find(chiaveDaEliminare);
    if (valoreTrovato)
        cout << "ATTENZIONE: La chiave " << chiaveDaEliminare << " è ancora presente.\n";
    else
        cout << "Conferma: La chiave " << chiaveDaEliminare << " non è più nella tabella.\n";

    return 0;
}
