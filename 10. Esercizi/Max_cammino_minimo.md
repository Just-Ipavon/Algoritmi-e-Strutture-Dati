# Profondità Massima dei Cammini Minimi in un Grafo

## Problema
Dato un grafo `G(V,E)` orientato e pesato (con pesi `w: E -> R`) e un nodo sorgente `s ∈ V`, si vuole trovare la **profondità massima** (numero di archi) tra tutti i cammini minimi che partono da `s`.

---

## Logica dell'Algoritmo

1.  **Calcolo dei Cammini Minimi:** Utilizzare l'algoritmo di Bellman-Ford per calcolare, dalla sorgente `s`, le distanze minime (`d[v]`) e i predecessori (`pi[v]`) per ogni nodo `v`. Questo algoritmo gestisce anche pesi negativi e rileva cicli negativi.
2.  **Analisi dei Cammini Minimi:** Per ogni nodo `v` raggiungibile da `s`:
    *   Ricostruire il cammino minimo da `s` a `v` seguendo i predecessori `pi` all'indietro.
    *   Contare il numero di archi (profondità) di questo cammino.
3.  **Determinazione della Profondità Massima:** Trovare il valore massimo tra tutte le profondità calcolate.

---

## Algoritmo di Bellman-Ford (Prerequisito)

L'algoritmo di Bellman-Ford inizializza `d[s]=0` e `d[v]=∞` per `v≠s`. Successivamente, per `|V|-1` volte, "rilassa" ogni arco `(u,v)`: se `d[u] + w(u,v) < d[v]`, aggiorna `d[v] = d[u] + w(u,v)` e `pi[v]=u`. Infine, controlla la presenza di cicli negativi.

**Output di Bellman-Ford utilizzato:**
*   `d`: Array delle distanze minime da `s`.
*   `pi`: Array dei predecessori sui cammini minimi.
*   Un flag che indica l'assenza/presenza di cicli negativi.

---

## Pseudocodice: Calcolo Profondità Massima (dato l'output di Bellman-Ford)

```c
ALGORITMO CALCOLA_PROFONDITA_MAX_DA_BELLMANFORD_OUTPUT(V_nodi, s_sorgente, d_distanze, pi_predecessori)
  profondita_massima = 0

  PER OGNI nodo v IN V_nodi FAI
    SE d_distanze[v] < +INF ALLORA // Considera solo nodi raggiungibili
      profondita_cammino_v = 0
      nodo_corrente = v

      // Ricostruisci cammino all'indietro e conta archi
      MENTRE nodo_corrente != s_sorgente FAI
        // Assumiamo pi_predecessori[nodo_corrente] sia valido se nodo_corrente != s_sorgente e raggiungibile
        nodo_corrente = pi_predecessori[nodo_corrente] 
        profondita_cammino_v = profondita_cammino_v + 1
      FINE MENTRE

      // Aggiorna profondità massima
      SE profondita_cammino_v > profondita_massima ALLORA
        profondita_massima = profondita_cammino_v
      FINE SE
    FINE SE
  FINE PER

  RESTITUISCI profondita_massima
FINE ALGORITMO
```

---

## Implementazione in C++

```cpp
#include <iostream>
#include <vector>
#include <limits>   // Per numeric_limits
#include <algorithm> // Per max
#include <tuple>     // Per tuple e make_tuple
using namespace std;
// Costante per rappresentare l'infinito per le distanze
const double INF = numeric_limits<double>::infinity();
// Costante per rappresentare NIL (nessun predecessore)
const int NIL = -1;

// Struttura per rappresentare un arco pesato nel grafo
struct Edge {
    int u;      // Nodo di partenza dell'arco
    int v;      // Nodo di arrivo dell'arco
    double weight; // Peso dell'arco
};

// Funzione Bellman-Ford
// Restituisce una tupla: {vettore distanze, vettore predecessori, booleano per cicli negativi}
// Il booleano è 'true' se NON ci sono cicli negativi, 'false' altrimenti.
tuple<vector<double>, vector<int>, bool> bellmanFord(
    int V, // Numero di vertici
    const vector<Edge>& edges, // Vettore di tutti gli archi
    int s  // Nodo sorgente
) {
    vector<double> dist(V, INF);
    vector<int> pred(V, NIL);

    dist[s] = 0;

    // Fase di rilassamento: |V|-1 iterazioni
    for (int i = 0; i < V - 1; ++i) {
        for (const auto& edge : edges) {
            // L'operazione di RILASSAMENTO è qui:
            if (dist[edge.u] != INF && dist[edge.v] > dist[edge.u] + edge.weight) {
                dist[edge.v] = dist[edge.u] + edge.weight;
                pred[edge.v] = edge.u;
            }
        }
    }

    // Fase di controllo cicli negativi
    for (const auto& edge : edges) {
        if (dist[edge.u] != INF && dist[edge.v] > dist[edge.u] + edge.weight) {
            // Ciclo negativo rilevato
            return make_tuple(dist, pred, false);
        }
    }

    // Nessun ciclo negativo rilevato
    return make_tuple(dist, pred, true);
}

// Funzione per calcolare la profondità massima dei cammini minimi,
// dati gli output di Bellman-Ford.
// Assume che non ci siano cicli negativi e che 'dist' e 'pred' siano corretti.
int calcolaProfonditaMaxDaBellmanFordOutput(
    int V, // Numero di vertici
    int s, // Nodo sorgente
    const vector<double>& dist, // Array delle distanze minime
    const vector<int>& pred     // Array dei predecessori
) {
    int profondita_massima = 0;

    for (int v_node = 0; v_node < V; ++v_node) {
        // Considera solo i nodi raggiungibili dalla sorgente
        if (dist[v_node] < INF) {
            int profondita_cammino_v = 0;
            int nodo_corrente = v_node;

            // Ricostruisci il cammino all'indietro verso s, contando gli archi.
            // Se dist[v_node] < INF, il cammino tramite pred deve arrivare a s.
            while (nodo_corrente != s) {
                if (pred[nodo_corrente] == NIL && nodo_corrente != s) {
                    profondita_cammino_v = -1; // Segnala un problema per questo cammino
                    break; 
                }
                nodo_corrente = pred[nodo_corrente];
                profondita_cammino_v++;
            }
            
            if (profondita_cammino_v != -1) { // Se il calcolo della profondità è andato a buon fine
                 if (profondita_cammino_v > profondita_massima) {
                    profondita_massima = profondita_cammino_v;
                }
            }
        }
    }
    return profondita_massima;
}

int main() {
    // Definizione del grafo dell'esempio:
    // Nodi V = {s, a, b, c, d} -> mappati a {0, 1, 2, 3, 4}
    // Sorgente s = 0
    int V_nodes = 5; // Numero di vertici
    int source_node = 0; // Nodo sorgente (indice 0)

    vector<Edge> edges_list;
    edges_list.push_back({0, 1, 1.0});  // s -> a, peso 1
    edges_list.push_back({0, 2, 6.0});  // s -> b, peso 6
    edges_list.push_back({1, 2, 2.0});  // a -> b, peso 2
    edges_list.push_back({1, 3, 7.0});  // a -> c, peso 7
    edges_list.push_back({2, 3, 1.0});  // b -> c, peso 1
    edges_list.push_back({2, 4, -2.0}); // b -> d, peso -2
    edges_list.push_back({3, 4, 3.0});  // c -> d, peso 3

    // Esegui Bellman-Ford
    auto [distances, predecessors, no_negative_cycle_found] = bellmanFord(V_nodes, edges_list, source_node);

    // Chiama la funzione per calcolare la profondità massima
    int max_depth = calcolaProfonditaMaxDaBellmanFordOutput(V_nodes, source_node, distances, predecessors);

    cout << "Profondita' massima dei cammini minimi: " << max_depth << endl;

    return 0;
}
```

---

## Riassunto

L'approccio consiste nel:
1.  Eseguire Bellman-Ford per ottenere l'albero dei cammini minimi dalla sorgente `s` (memorizzato come array di distanze `d` e predecessori `pi`).
2.  Se vengono rilevati cicli negativi, il problema non ha soluzione definita.
3.  Altrimenti, per ogni nodo `v` raggiungibile, si calcola la sua profondità (numero di archi) nel cammino minimo risalendo da `v` a `s` tramite i predecessori `pi`.
4.  La profondità massima trovata tra tutti i nodi raggiungibili è il risultato.
