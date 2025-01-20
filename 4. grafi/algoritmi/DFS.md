# **Depth-First Search (DFS)**

La **Depth-First Search (DFS)** è un algoritmo utilizzato per attraversare o cercare nodi in un grafo. DFS segue un approccio di esplorazione completa di ogni percorso prima di tornare indietro, utilizzando una logica di visita basata sui colori.

---

## **Proprietà di DFS**

1. **Struttura**:
   - Funziona su grafi pesati e non pesati.
   - Utilizza una pila (esplicitamente o attraverso la ricorsione) per tenere traccia del percorso esplorato.

2. **Stato dei nodi**:
   - **Bianco**: Nodo non visitato.
   - **Grigio**: Nodo in esplorazione, con almeno un vicino bianco.
   - **Nero**: Nodo completamente esplorato.

3. **Applicazioni**:
   - Rilevamento di cicli.
   - Classificazione degli archi (alberi, retrollacciamenti, ecc.).
   - Verifica della connettività di componenti fortemente connesse.
   - Algoritmi topologici.

4. **Tempo di Esecuzione**:
   - \( O(V + E) \), dove \( V \) è il numero di nodi e \( E \) è il numero di archi.

5. **Struttura dei Dati Utilizzata**:
   - Una pila (implicita o esplicita) per la gestione della ricorsione.

---

## **Algoritmo**

1. Inizializza tutti i nodi come **bianchi**.
2. Per ogni nodo bianco:
   - Contrassegnalo come **grigio** e avvia l'esplorazione.
3. Durante l'esplorazione:
   - Visita ogni vicino bianco e contrassegnalo come **grigio**.
   - Dopo aver esplorato tutti i vicini, contrassegna il nodo come **nero**.

---

## **Esempio in C++**

### **Rappresentazione del Grafo con Lista di Adiacenza**

```cpp
#include <iostream>
#include <vector>
using namespace std;

// DFS Function
void dfsVisit(int node, vector<vector<int>>& adjList, vector<int>& state) {
    state[node] = 1; // Grigio
    cout << node << " "; // Stampa il nodo visitato

    // Esplora i vicini
    for (int neighbor : adjList[node]) {
        if (state[neighbor] == 0) { // Nodo bianco
            dfsVisit(neighbor, adjList, state);
        }
    }

    state[node] = 2; // Nero
}

// DFS Wrapper
void dfs(vector<vector<int>>& adjList) {
    int numNodes = adjList.size();
    vector<int> state(numNodes, 0); // 0 = bianco, 1 = grigio, 2 = nero

    cout << "DFS Traversal: ";
    for (int i = 0; i < numNodes; ++i) {
        if (state[i] == 0) { // Nodo bianco
            dfsVisit(i, adjList, state);
        }
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

    // Chiamata alla DFS
    dfs(adjList);

    return 0;
}
```

---

### **Output Atteso**

```
DFS Traversal: 0 1 3 5 4 2
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
   - **Bianco**: Il nodo non è stato ancora visitato.
   - **Grigio**: Il nodo è in fase di esplorazione, ma alcuni dei suoi vicini devono ancora essere visitati.
   - **Nero**: Il nodo e tutti i suoi vicini sono stati esplorati completamente.

2. **Proprietà Importanti**:
   - La DFS può essere utilizzata per costruire una foresta di visita.
   - È adatta per grafi diretti e non diretti.
    - Può essere utilizzata per trovare cicli in un grafo.