# **Algoritmo di Dijkstra**

L'algoritmo di Dijkstra è un metodo utilizzato per trovare i percorsi più brevi da un nodo sorgente a tutti gli altri nodi di un grafo **pesato** con pesi degli archi non negativi.

---

## **Proprietà di Dijkstra**

1. **Input**:
   - Un grafo pesato rappresentato come matrice di adiacenza o lista di adiacenza.
   - Un nodo sorgente \( s \).

2. **Output**:
   - La distanza minima da \( s \) a ogni altro nodo.
   - (Facoltativo) Il percorso più breve da \( s \) a uno specifico nodo.

3. **Assunzioni**:
   - Gli archi hanno pesi non negativi.
   - Funziona solo su grafi connessi.

4. **Struttura dei Dati Utilizzata**:
   - Una coda di priorità (tipicamente implementata come un min-heap) per trovare il nodo con la distanza minima.

5. **Complessità**:
   - Con una coda di priorità basata su heap binario: \( O((V + E) \log V) \), dove:
     - \( V \): numero di nodi.
     - \( E \): numero di archi.

---

## **Algoritmo**

1. Inizializza la distanza di tutti i nodi a \( \infty \), eccetto il nodo sorgente \( s \), che ha distanza \( 0 \).
2. Utilizza una coda di priorità per gestire i nodi non visitati e la loro distanza corrente.
3. Iterativamente:
   - Estrai il nodo \( u \) con la distanza minima dalla coda.
   - Aggiorna le distanze dei vicini di \( u \) se il percorso passando per \( u \) è più breve.
4. Ripeti fino a visitare tutti i nodi.

---

## **Esempio in C++**

### **Rappresentazione del Grafo e Algoritmo**

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

// Struttura per rappresentare un arco
struct Edge {
    int destination;
    int weight;
};

// Funzione per eseguire l'algoritmo di Dijkstra
void dijkstra(int source, vector<vector<Edge>>& adjList) {
    int V = adjList.size();
    vector<int> distance(V, INT_MAX); // Distanze inizializzate a infinito
    distance[source] = 0;

    // Min-heap (priority queue) per i nodi da visitare
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> minHeap;
    minHeap.push({0, source}); // {distanza, nodo}

    while (!minHeap.empty()) {
        int dist = minHeap.top().first;
        int node = minHeap.top().second;
        minHeap.pop();

        // Visita ogni vicino del nodo corrente
        for (const Edge& edge : adjList[node]) {
            int nextNode = edge.destination;
            int weight = edge.weight;

            // Relaxation step
            if (distance[node] + weight < distance[nextNode]) {
                distance[nextNode] = distance[node] + weight;
                minHeap.push({distance[nextNode], nextNode});
            }
        }
    }

    // Stampa le distanze minime dal nodo sorgente
    cout << "Distanze dal nodo sorgente " << source << ":\n";
    for (int i = 0; i < V; ++i) {
        cout << "Nodo " << i << ": " << (distance[i] == INT_MAX ? -1 : distance[i]) << "\n";
    }
}

int main() {
    int V = 6; // Numero di nodi
    vector<vector<Edge>> adjList(V);

    // Aggiunta degli archi al grafo
    adjList[0].push_back({1, 4});
    adjList[0].push_back({2, 1});
    adjList[2].push_back({1, 2});
    adjList[1].push_back({3, 1});
    adjList[2].push_back({3, 5});
    adjList[3].push_back({4, 3});
    adjList[4].push_back({5, 2});

    // Chiamata a Dijkstra
    dijkstra(0, adjList);

    return 0;
}
```

---

### **Output Atteso**

```
Distanze dal nodo sorgente 0:
Nodo 0: 0
Nodo 1: 3
Nodo 2: 1
Nodo 3: 4
Nodo 4: 7
Nodo 5: 9
```

---

## **Esempio di Grafo**

Il grafo rappresentato dagli input è:

```
    (0)
   /   \
  4     1
 /       \
(1)---2---(2)
  \       /
   1     5
    \   /
     (3)
      |
      3
      |
     (4)
      |
      2
      |
     (5)
```

---

## **Applicazioni**

1. **Navigazione GPS**: Calcolo di percorsi più brevi tra punti geografici.
2. **Reti di Computer**: Determinazione dei percorsi ottimali per il trasferimento dati.
3. **Problemi di Ottimizzazione**: Utilizzo in problemi di minimo costo.

---