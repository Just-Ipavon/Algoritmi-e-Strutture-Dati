# **Breadth-First Search (BFS)**

La **Breadth-First Search (BFS)** è un algoritmo utilizzato per attraversare o cercare nodi in un grafo. Funziona visitando i nodi livello per livello, partendo da un nodo sorgente. 

---

## **Proprietà di BFS**

1. **Struttura**:
   - Funziona su grafi orientati e non orientati.
   - Adatto per grafi non pesati.

2. **Stato dei nodi**:
   - **Bianco**: Nodo non visitato.
   - **Grigio**: Nodo visitato, ma con almeno un vicino bianco da esplorare.
   - **Nero**: Nodo completamente esplorato, senza vicini bianchi.

3. **Applicazioni**:
   - Trovare il percorso più corto in un grafo non ponderato.
   - Verificare la connettività di un grafo.
   - Rilevamento di cicli in un grafo non orientato.

4. **Tempo di Esecuzione**:
   - \( O(V + E) \), dove \( V \) è il numero di nodi e \( E \) è il numero di archi.

5. **Struttura dei Dati Utilizzata**:
   - Una coda per gestire i nodi grigi.

---

## **Algoritmo**

1. Inizializza tutti i nodi come **bianchi**.
2. Scegli un nodo sorgente, contrassegnalo come **grigio** e aggiungilo alla coda.
3. Finché la coda non è vuota:
   - Rimuovi il primo nodo dalla coda.
   - Visita tutti i suoi vicini bianchi:
     - Contrassegnali come **grigi**.
     - Aggiungili alla coda.
   - Contrassegna il nodo attuale come **nero**.

---

## **Esempio in C++**

### **Rappresentazione del Grafo con Lista di Adiacenza**

```cpp
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// BFS Function
void bfs(int startNode, const vector<vector<int>>& adjList) {
    int numNodes = adjList.size();

    // Stati dei nodi: 0 = bianco, 1 = grigio, 2 = nero
    vector<int> state(numNodes, 0);

    // Coda per BFS
    queue<int> q;

    // Inizializza il nodo di partenza
    state[startNode] = 1; // Grigio
    q.push(startNode);

    cout << "BFS Traversal: ";

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        cout << current << " ";

        // Esplora i vicini
        for (int neighbor : adjList[current]) {
            if (state[neighbor] == 0) { // Nodo bianco
                state[neighbor] = 1;   // Diventa grigio
                q.push(neighbor);
            }
        }

        // Contrassegna il nodo come nero
        state[current] = 2;
    }

    cout << endl;
}

int main() {
    // Numero di nodi
    int numNodes = 6;

    // Lista di adiacenza per il grafo
    vector<vector<int>> adjList(numNodes);

    // Aggiungere archi
    adjList[0] = {1, 2};
    adjList[1] = {0, 3, 4};
    adjList[2] = {0, 4};
    adjList[3] = {1, 5};
    adjList[4] = {1, 2, 5};
    adjList[5] = {3, 4};

    // Chiamata alla BFS
    bfs(0, adjList); // Nodo di partenza

    return 0;
}
```

---

### **Output Atteso**

```
BFS Traversal: 0 1 2 3 4 5
```

---

## **Esempio di Grafo**

Il grafo rappresentato dall'input precedente:

```
    0 - 1 - 3
     \  |    \
      2 - 4 - 5
```

---

## **Approfondimenti**

1. **Stato dei nodi**:
   - **Bianco**: All'inizio, tutti i nodi sono bianchi.
   - **Grigio**: Un nodo diventa grigio quando è stato visitato ma non sono stati esplorati tutti i suoi vicini.
   - **Nero**: Un nodo diventa nero quando tutti i suoi vicini sono stati esplorati.

2. **Proprietà Importanti**:
   - La BFS trova il percorso più breve in un grafo non ponderato.
   - Ogni nodo viene visitato esattamente una volta, garantendo l'efficienza.
