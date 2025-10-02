# **Grafi: Rappresentazioni e Proprietà**

I grafi sono strutture dati che modellano relazioni tra oggetti. Sono composti da:
- **Nodi (o Vertici)**: Gli oggetti che rappresentano entità.
- **Archi**: Collegamenti tra i nodi, che possono essere orientati o non orientati.

Un grafo G può essere rappresentato come una coppia G = (V, E), dove:
- **V**: Insieme di nodi.
- **E**: Insieme di archi.

---

## **Proprietà dei Grafi**

- **Adiacenza**: due nodi sono adiacenti se esiste un arco che li collega direttamente.
- **Cammino**: una sequenza di nodi in cui ogni coppia consecutiva di nodi è collegata da un arco.
- **Lunghezza**: il numero di archi in un cammino e corrisponde al numero di nodi meno uno.
- **Cammino semplice**: un cammino che non contiene nodi ripetuti eccetto il primo e l'ultimo nodo.

### Tipi di Grafi:
- **Orientato/Diretto**: Gli archi hanno una direzione ovvero un arco è una coppia ordinata (v,w) di nodi (v,w ∈ V)
- **Non Orientato/Indiretto**: Gli archi non hanno una direzione ovvero un arco è una coppia non ordinata (v,w) di nodi (v,w ∈ V)
- **Pesato**: Gli archi hanno un peso.
- **Non Pesato**: Gli archi non hanno peso.

### Terminologia:
- **Grado di un Nodo**: Numero di archi incidenti su un nodo.
- **Cammino**: Sequenza di nodi collegati da archi.
- **Ciclo**: Un cammino che inizia e termina nello stesso nodo.

---

## **Rappresentazioni dei Grafi**

### **1. Matrice di Adiacenza**

La matrice di adiacenza è una matrice \( n \times n \), dove \( n \) è il numero di nodi. Ogni elemento della matrice indica la presenza o il peso di un arco tra due nodi.

#### **Esempio in C++**

```cpp
#include <iostream>
#include <vector>

using namespace std;

void printAdjMatrix(const vector<vector<int>>& matrix) {
    cout << "Matrice di Adiacenza:" << endl;
    for (const auto& row : matrix) {
        for (int value : row) {
            cout << value << " ";
        }
        cout << endl;
    }
}

int main() {
    int numNodes = 4;
    vector<vector<int>> adjMatrix(numNodes, vector<int>(numNodes, 0));

    // Aggiungere archi
    adjMatrix[0][1] = 1; // Arco da 0 a 1
    adjMatrix[1][2] = 1; // Arco da 1 a 2
    adjMatrix[2][3] = 1; // Arco da 2 a 3
    adjMatrix[3][0] = 1; // Arco da 3 a 0

    // Stampare la matrice
    printAdjMatrix(adjMatrix);

    return 0;
}
```

#### **Output:**
```
Matrice di Adiacenza:
0 1 0 0
0 0 1 0
0 0 0 1
1 0 0 0
```

---

### **2. Lista di Adiacenza**

La lista di adiacenza utilizza un array di liste, dove ogni nodo ha una lista dei nodi adiacenti. È più efficiente in termini di spazio per grafi sparsi.

#### **Esempio in C++**

```cpp
#include <iostream>
#include <vector>

using namespace std;

void printAdjList(const vector<vector<int>>& adjList) {
    cout << "Lista di Adiacenza:" << endl;
    for (int i = 0; i < adjList.size(); i++) {
        cout << "Nodo " << i << ": ";
        for (int neighbor : adjList[i]) {
            cout << neighbor << " ";
        }
        cout << endl;
    }
}

void addEdge(vector<vector<int>>& adjList, int u, int v) {
    adjList[u].push_back(v); // Per grafi non orientati, aggiungere anche: adjList[v].push_back(u);
}

int main() {
    int numNodes = 4;
    vector<vector<int>> adjList(numNodes);

    // Aggiungere archi
    addEdge(adjList, 0, 1);
    addEdge(adjList, 1, 2);
    addEdge(adjList, 2, 3);
    addEdge(adjList, 3, 0);

    // Stampare la lista di adiacenza
    printAdjList(adjList);

    return 0;
}
```

#### **Output:**
```
Lista di Adiacenza:
Nodo 0: 1 
Nodo 1: 2 
Nodo 2: 3 
Nodo 3: 0 
```

---

## **Confronto**

| **Caratteristica**     | **Matrice di Adiacenza**   | **Lista di Adiacenza**       |
|-------------------------|---------------------------|-----------------------------|
| **Spazio**             | \( O(n^2) \)              | \( O(n + m) \), dove \( m \) è il numero di archi |
| **Tempo di Accesso**   | \( O(1) \)                | Dipende dalla lista (\( O(k) \), dove \( k \) è il numero di adiacenti) |
| **Grafi Sparsi**       | Inefficiente              | Efficiente                  |
| **Grafi Densi**        | Efficiente                | Inefficiente                |
