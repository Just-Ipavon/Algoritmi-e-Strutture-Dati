# Kruskal's Algorithm

L'algoritmo di **Kruskal** è uno degli algoritmi più utilizzati per risolvere il problema del **Minimum Spanning Tree (MST)** in un grafo connesso e pesato. L'algoritmo segue una strategia **greedy**, selezionando gli archi di peso minimo uno alla volta, evitando di formare cicli, fino a quando non è stato costruito un albero di copertura che connette tutti i vertici.

### Proprietà di Kruskal:
- **Ordinamento degli archi**: Kruskal ordina tutti gli archi in ordine crescente di peso.
- **Costruzione dell'albero di copertura**: Se un arco non forma un ciclo, viene aggiunto all'MST.
- **Disjoint-set**: Kruskal usa una struttura dati chiamata "disjoint-set" (insiemi disgiunti) per determinare se due vertici sono già connessi nello stesso albero.

## Procedura di Kruskal

L'algoritmo di Kruskal funziona come segue:

1. **Ordinare gli archi** del grafo in ordine crescente di peso.
2. **Inizializzare la struttura "disjoint-set"** per tenere traccia di quali nodi sono già collegati.
3. **Selezionare l'arco con il peso minimo** che non forma un ciclo.
4. Continuare a selezionare archi fino a quando l'MST non contiene \( V - 1 \) archi (dove \( V \) è il numero di vertici del grafo).

### Pseudocodice di Kruskal:

```text
function Kruskal(grafo):
    ordinare gli archi di grafo in ordine crescente di peso
    MST = insieme vuoto
    inizializzare il "disjoint-set" per ogni nodo

    per ogni arco (u, v) in ordine crescente:
        se u e v sono in set diversi:
            aggiungi arco (u, v) a MST
            unisci i set di u e v

    return MST
```

### Complessità:
- Ordinamento degli archi: \( O(E log E) \), dove \( E \) è il numero di archi nel grafo.
- Operazioni di unione e ricerca (con **Union-Find**): \( O(a(V)) \), dove \( a \) è la funzione di Ackermann, che è praticamente costante per valori ragionevoli di \( V \).
- Complessità totale: \( O(E log E) \).

## Codice C++ di Kruskal

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Struttura per rappresentare un arco
struct Edge {
    int u, v, weight;
    Edge(int u, int v, int weight) : u(u), v(v), weight(weight) {}
};

// Struttura per il Disjoint-Set (Union-Find)
struct DisjointSet {
    vector<int> parent, rank;
    
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int u) {
        if (parent[u] != u) {
            parent[u] = find(parent[u]);  // Path compression
        }
        return parent[u];
    }

    void unionSets(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        if (rootU != rootV) {
            // Union by rank
            if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU;
            } else if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV;
            } else {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }
};

// Funzione di Kruskal
int Kruskal(int V, vector<Edge>& edges) {
    // Ordina gli archi in ordine crescente di peso
    sort(edges.begin(), edges.end(), [](Edge& e1, Edge& e2) {
        return e1.weight < e2.weight;
    });

    DisjointSet ds(V);
    int mstWeight = 0;
    vector<Edge> mst;

    for (Edge& e : edges) {
        // Se i due vertici non sono nello stesso set, uniscili
        if (ds.find(e.u) != ds.find(e.v)) {
            mst.push_back(e);
            mstWeight += e.weight;
            ds.unionSets(e.u, e.v);
        }
    }

    // Stampa gli archi dell'MST
    cout << "Archi dell'MST:" << endl;
    for (Edge& e : mst) {
        cout << "(" << e.u << ", " << e.v << ") con peso " << e.weight << endl;
    }

    return mstWeight;
}

int main() {
    int V = 4;  // Numero di vertici
    vector<Edge> edges = {
        Edge(0, 1, 10),
        Edge(0, 2, 6),
        Edge(0, 3, 5),
        Edge(1, 3, 15),
        Edge(2, 3, 4)
    };

    int mstWeight = Kruskal(V, edges);
    cout << "Peso totale dell'MST: " << mstWeight << endl;

    return 0;
}
```

### Spiegazione del Codice:

1. **Struttura `Edge`**: Rappresenta un arco nel grafo, con i suoi vertici \( u \), \( v \) e il peso associato.
2. **Struttura `DisjointSet`**: Gestisce l'insieme disgiunto tramite la tecnica di "Union-Find". La funzione `find` restituisce il rappresentante di un nodo (con compressione del percorso), mentre la funzione `unionSets` unisce due sottoinsiemi.
3. **Funzione `Kruskal`**:
    - Ordina gli archi in ordine crescente di peso.
    - Usa il **Disjoint-Set** per evitare cicli, aggiungendo un arco all'MST solo se i due vertici non sono già connessi.
    - Restituisce il peso totale dell'MST.

### Esempio di Esecuzione:

Supponiamo di avere il seguente grafo:

- Vertici: \( 0, 1, 2, 3 \)
- Archi: \( (0,1,10), (0,2,6), (0,3,5), (1,3,15), (2,3,4) \)

L'output sarà:

```
Archi dell'MST:
(2, 3) con peso 4
(0, 3) con peso 5
(0, 1) con peso 10
Peso totale dell'MST: 19
```

### Conclusioni:

- **Kruskal's Algorithm** è un algoritmo efficiente per trovare l'MST in un grafo, in particolare quando il grafo è sparso (cioè ha pochi archi rispetto al numero di vertici).
- La complessità dell'algoritmo è determinata principalmente dal passo di ordinamento degli archi, che richiede \( O(E log E) \), e dalle operazioni di unione e ricerca, che sono quasi costanti grazie alla compressione del percorso e unione per rango.

