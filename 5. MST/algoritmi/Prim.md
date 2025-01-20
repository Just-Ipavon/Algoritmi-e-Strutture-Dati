# Prim's Algorithm

L'algoritmo di **Prim** è un altro metodo per risolvere il problema del **Minimum Spanning Tree (MST)** in un grafo pesato. A differenza di Kruskal, che seleziona gli archi più leggeri, Prim cresce un albero di copertura espandendo il suo MST ad ogni passo, partendo da un nodo iniziale e aggiungendo il nodo più vicino che non è ancora stato incluso nell'albero.

### Proprietà di Prim:
- **Espansione locale**: Inizia con un singolo nodo e, ad ogni iterazione, aggiunge l'arco di peso minimo che collega un nodo già nell'albero a un nodo fuori dall'albero.
- **Albero connesso**: Garantisce la creazione di un albero che copre tutti i vertici.
- **Struttura dati**: Viene utilizzata una **coda di priorità (min-heap)** per mantenere traccia dei vertici da esplorare e selezionare il più vicino in termini di peso.

## Procedura di Prim

L'algoritmo di Prim funziona come segue:

1. **Inizializzazione**: Si parte da un nodo arbitrario e si inizializza la coda di priorità con le distanze ai nodi (inizialmente tutte infinite, tranne quella del nodo di partenza).
2. **Selezione dell'arco minimo**: Si esplora il nodo con la distanza minima e si aggiorna la distanza dei suoi vicini.
3. **Ripetizione**: Si ripete il passo 2 finché non sono stati esplorati tutti i nodi, costruendo così l'MST.

### Pseudocodice di Prim:

```text
function Prim(grafo, nodo_iniziale):
    per ogni nodo v in grafo:
        distanza[v] = infinito
        padre[v] = null
    distanza[nodo_iniziale] = 0
    inizializza coda di priorità con distanza minima
    
    mentre la coda non è vuota:
        u = nodo con distanza minima
        rimuovi u dalla coda
        per ogni nodo v adiacente a u:
            se v è ancora nella coda e il peso dell'arco (u, v) è inferiore alla distanza[v]:
                aggiorna distanza[v]
                aggiorna padre[v]

    ritorna l'MST
```

### Complessità:
- Se usiamo una coda di priorità implementata come un **min-heap**:
  - Operazioni di inserimento ed estrazione: \( O(log V) \)
  - Per ogni arco, si aggiorna la coda: \( O(log V) \)
- Complessità totale: \( O(E log V) \), dove \( V \) è il numero di vertici e \( E \) è il numero di archi.

## Codice C++ di Prim

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// Struttura per rappresentare un arco
struct Edge {
    int v, weight;
    Edge(int v, int weight) : v(v), weight(weight) {}
};

// Struttura per il grafo (list of adjacency)
class Graph {
public:
    int V;  // Numero di vertici
    vector<vector<Edge>> adjList;  // Lista di adiacenza

    Graph(int V) {
        this->V = V;
        adjList.resize(V);
    }

    // Aggiunge un arco al grafo
    void addEdge(int u, int v, int weight) {
        adjList[u].push_back(Edge(v, weight));
        adjList[v].push_back(Edge(u, weight)); // per grafo non orientato
    }
};

// Funzione di Prim per trovare l'MST
int prim(Graph& g, int start) {
    vector<int> dist(g.V, INT_MAX);  // Distanze ai vertici, inizializzate a infinito
    vector<int> parent(g.V, -1);     // Array per tenere traccia dei genitori
    vector<bool> inMST(g.V, false);  // Se un nodo è nell'MST
    dist[start] = 0;  // Partiamo dal nodo di partenza

    // Coda di priorità per selezionare il nodo con la distanza minima
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});  // Distanza 0 per il nodo di partenza

    int mstWeight = 0;  // Peso totale dell'MST

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        // Se il nodo è già stato incluso nell'MST, salta
        if (inMST[u]) continue;

        inMST[u] = true;
        mstWeight += dist[u];  // Aggiungi il peso del nodo all'MST

        // Aggiorna i vicini
        for (const Edge& e : g.adjList[u]) {
            int v = e.v;
            int weight = e.weight;
            if (!inMST[v] && weight < dist[v]) {
                dist[v] = weight;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    // Stampa gli archi dell'MST
    cout << "Archi dell'MST:" << endl;
    for (int i = 0; i < g.V; i++) {
        if (parent[i] != -1) {
            cout << parent[i] << " - " << i << " con peso " << dist[i] << endl;
        }
    }

    return mstWeight;
}

int main() {
    int V = 5;  // Numero di vertici
    Graph g(V);

    // Aggiungi gli archi (u, v, peso)
    g.addEdge(0, 1, 2);
    g.addEdge(0, 3, 6);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 8);
    g.addEdge(1, 4, 5);
    g.addEdge(2, 4, 7);

    int mstWeight = prim(g, 0);  // Inizia dal nodo 0
    cout << "Peso totale dell'MST: " << mstWeight << endl;

    return 0;
}
```

### Spiegazione del Codice:

1. **Struttura `Edge`**: Ogni arco è rappresentato da un vertice di destinazione \( v \) e un peso \( weight \).
2. **Classe `Graph`**: La classe gestisce il grafo, rappresentato come una lista di adiacenza. La funzione `addEdge` aggiunge un arco tra due vertici.
3. **Funzione `prim`**:
   - Inizializza le distanze a infinito e la coda di priorità.
   - Aggiunge il nodo iniziale alla coda con distanza 0.
   - Esplora il grafo, aggiornando le distanze dei nodi non ancora inclusi nell'MST.
   - Restituisce il peso totale dell'MST.

### Esempio di Esecuzione:

Supponiamo di avere il seguente grafo:

- Vertici: \( 0, 1, 2, 3, 4 \)
- Archi: \( (0,1,2), (0,3,6), (1,2,3), (1,3,8), (1,4,5), (2,4,7) \)

L'output sarà:

```
Archi dell'MST:
0 - 1 con peso 2
1 - 2 con peso 3
0 - 3 con peso 6
Peso totale dell'MST: 11
```

### Conclusioni:

- **Prim's Algorithm** è ideale per trovare l'MST quando il grafo è denso e la rappresentazione in lista di adiacenza è efficiente.
- La complessità dell'algoritmo è \( O(E log V) \), dove \( E \) è il numero di archi e \( V \) è il numero di vertici, grazie all'uso della coda di priorità.
- **Prim** è particolarmente utile quando si parte da un nodo specifico e si desidera costruire l'MST.
