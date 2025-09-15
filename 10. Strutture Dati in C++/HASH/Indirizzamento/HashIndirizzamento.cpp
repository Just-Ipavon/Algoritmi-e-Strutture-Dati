#include <iostream>
#include <fstream>
#include <vector>
#include <list>
using namespace std;


template<typename T,typename S>
class Oggetto{
public:
    T chiave;
    S valore;

    Oggetto(T chiave,S valore) : chiave(chiave), valore(valore) {}
};

template<typename T, typename S>
class Hash{
public:
    vector<list<Oggetto<T,S>>> tabella;
    int m;

    Hash(int m) : m(m){
        tabella.resize(m);
    }

    int hash(T chiave){
        return chiave % m;
    }

    void insert(T chiave, S valore){
        int idx = hash(chiave);
        for(auto& i : tabella[idx]){
            if(i.chiave == chiave){
                i.valore = valore;
                return;
            }
        }
        tabella[idx].push_back(Oggetto<T,S>(chiave,valore));
    }

    bool contiene(T chiave){
        int idx = chiave % m;
        for(auto& i : tabella[idx])
            if(i.chiave == chiave) return true;
        return false;
    }


    void stampa(ofstream& out){
        for(int i = 0; i < m; i++)
            for(auto& j : tabella[i])
                out << j.chiave << " -> " << j.valore << "\n";
    }

    S* find(T chiave){
        int idx = hash(chiave);
        for(auto& oggetto : tabella[idx]){
            if(oggetto.chiave == chiave){
                return &(oggetto.valore);
            }
        }
        return nullptr;
    }

};

void leggiFile(Hash<int,string>& H, string file){
    ifstream in(file);
    int k;
    string v;
    char c;
    while(in >> c && c == '<' && in >> k >> c && c == ','){
        getline(in, v, '>');
        H.insert(k,v);
    }
}
bool disjoint( Hash<int,string>& A,  Hash<int,string>& B){
    for(int i = 0; i<A.m;i++)
        for(auto& j : A.tabella[i])
            if(B.contiene(j.chiave)) return false;
    return true;
}




int main()
{
    int M = 999;
    Hash<int,string> H1(M), H2(M);
    leggiFile(H1,"input1.txt");
    leggiFile(H2,"input2.txt");

    ofstream out("output.txt");
    out << (disjoint(H1,H2) ? "Disgiunte\n" : "Non disgiunte");

    out << "\n Tabella 1\n"; H1.stampa(out);
    out << "\n Tabella 2\n"; H2.stampa(out);

     int chiaveDaCercare;
     cout << "inserisci la chiave da cercare: ";
     cin >> chiaveDaCercare;
    string* valoreTrovato = H1.find(chiaveDaCercare);

    if (valoreTrovato != nullptr) {
        cout << "Trovato! La chiave " << chiaveDaCercare << " ha valore: " << *valoreTrovato << "\n"<<endl;
    } else {
        cout << "La chiave non e' stata trovata nella tabella.\n"<<endl;
    }




    return 0;
}
