# **Algoritmo di Bellman-Ford**

L'algoritmo di Bellman-Ford è utilizzato per trovare i percorsi più brevi da un nodo sorgente a tutti gli altri nodi di un grafo **pesato**, permettendo pesi negativi. A differenza di Dijkstra, Bellman-Ford rileva anche la presenza di cicli di peso negativo.

---

## **Proprietà di Bellman-Ford**

1. **Input**:
   - Un grafo pesato rappresentato come lista di archi.
   - Un nodo sorgente \( s \).

2. **Output**:
   - La distanza minima da \( s \) a ogni altro nodo.
   - Rilevazione di cicli di peso negativo, se presenti.

3. **Assunzioni**:
   - Funziona su grafi diretti e indiretti.
   - Gli archi possono avere pesi negativi, ma non devono esistere cicli di peso negativo raggiungibili dalla sorgente.

4. **Struttura dei Dati Utilizzata**:
   - Una lista di archi per rappresentare il grafo.
   - Un array per memorizzare le distanze minime.

5. **Complessità**:
   - Tempo: \( O(V \cdot E) \), dove:
     - \( V \): numero di nodi.
     - \( E \): numero di archi.

---

## **Algoritmo**

1. Inizializza la distanza di tutti i nodi a \( \infty \), eccetto il nodo sorgente \( s \), che ha distanza \( 0 \).
2. Ripeti \( V-1 \) volte:
   - Per ogni arco \( (u, v, w) \), aggiorna la distanza di \( v \) se \( \text{dist}[u] + w < \text{dist}[v] \).
3. Controlla la presenza di cicli di peso negativo eseguendo un ulteriore rilassamento:
   - Se una distanza può ancora essere aggiornata, allora esiste un ciclo di peso negativo.

---

## **Esempio in C++**

### **Rappresentazione del Grafo e Algoritmo**

```cpp
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// Struttura per rappresentare un arco
struct Edge {
    int source;
    int destination;
    int weight;
};

// Funzione per eseguire l'algoritmo di Bellman-Ford
bool bellmanFord(int V, int E, int source, vector<Edge>& edges) {
    vector<int> distance(V, INT_MAX);
    distance[source] = 0;

    // Passo di rilassamento
    for (int i = 1; i <= V - 1; ++i) {
        for (const Edge& edge : edges) {
            if (distance[edge.source] != INT_MAX &&
                distance[edge.source] + edge.weight < distance[edge.destination]) {
                distance[edge.destination] = distance[edge.source] + edge.weight;
            }
        }
    }

    // Controllo per cicli di peso negativo
    for (const Edge& edge : edges) {
        if (distance[edge.source] != INT_MAX &&
            distance[edge.source] + edge.weight < distance[edge.destination]) {
            cout << "Ciclo di peso negativo rilevato.\n";
            return false;
        }
    }

    // Stampa le distanze minime
    cout << "Distanze dal nodo sorgente " << source << ":\n";
    for (int i = 0; i < V; ++i) {
        cout << "Nodo " << i << ": " << (distance[i] == INT_MAX ? -1 : distance[i]) << "\n";
    }

    return true;
}

int main() {
    int V = 5; // Numero di nodi
    int E = 8; // Numero di archi

    vector<Edge> edges = {
        {0, 1, -1}, {0, 2, 4}, {1, 2, 3}, {1, 3, 2}, {1, 4, 2},
        {3, 2, 5}, {3, 1, 1}, {4, 3, -3}
    };

    // Chiamata a Bellman-Ford
    bellmanFord(V, E, 0, edges);

    return 0;
}
```

---

### **Output Atteso**

```
Distanze dal nodo sorgente 0:
Nodo 0: 0
Nodo 1: -1
Nodo 2: 2
Nodo 3: -2
Nodo 4: 1
```

---

## **Esempio di Grafo**

Il grafo rappresentato dagli input è:

```
       -1
   (0) ----> (1)
    |         |
    | 4       | 3
    v         v
   (2) <---- (3)
     \        ^
      \-3     |
        \---->(4)
```

---

## **Applicazioni**

1. **Rilevazione di Cicli Negativi**: Identificazione di errori in reti di trasporto o valute (arbitraggio).
2. **Problemi di Ottimizzazione**: Determinazione di percorsi più brevi anche in presenza di pesi negativi.
3. **Analisi delle Reti**: Modellazione di flussi e costi in reti.

---