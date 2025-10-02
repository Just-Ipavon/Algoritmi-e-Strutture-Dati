### **Schema di scelta dell'algoritmo per i grafi**

| **Tipo di Grafo**      | **Richiesta**                              | **Algoritmo da utilizzare**                                      |
|------------------------|--------------------------------------------|-----------------------------------------------------------------|
| **Non Orientato**       | Cammino minimo tra due nodi               | **BFS** (se non pesato)                                          |
| **Non Orientato**       | Cammino minimo tra due nodi, pesato        | **Dijkstra** (se pesato)                                         |
| **Non Orientato**       | Cammino minimo da un nodo a tutti gli altri | **BFS** (se non pesato)                                          |
| **Non Orientato**       | Cammino minimo da un nodo a tutti gli altri, pesato | **Dijkstra** (se pesato)                                         |
| **Orientato**           | Cammino minimo tra due nodi               | **Dijkstra** (se pesato)                                         |
| **Orientato**           | Cammino minimo tra due nodi, negativo     | **Bellman-Ford**                                                |
| **Orientato**           | Cammino minimo da un nodo a tutti gli altri | **Dijkstra** (se pesato, senza cicli negativi)                   |
| **Orientato**           | Cammino minimo da un nodo a tutti gli altri, con cicli negativi | **Bellman-Ford**                                                |
| **Orientato**           | Ciclo massimo in un grafo pesato          | **Algoritmo Ricorsivo per il Ciclo Massimo** (esplorazione dei cicli) |
| **Orientato**           | Rilevamento di cicli negativi             | **Bellman-Ford**                                                |
| **Non Orientato**       | Connessione tra nodi                      | **BFS** o **DFS**                                               |
| **Orientato**           | Connessione tra nodi                      | **DFS**                                                         |
| **Grafi Generici**      | Raggiungibilità da un nodo a tutti gli altri | **BFS** o **DFS**                                               |

### Note:
- Se il grafo è **non orientato e non pesato**, la scelta migliore per i cammini minimi è **BFS**, poiché esplora tutti i nodi a distanza uguale a partire dalla sorgente.
- Se il grafo è **pesato** (soprattutto con pesi positivi), **Dijkstra** è generalmente l'algoritmo più efficiente per trovare i cammini minimi.
- In presenza di **cicli negativi**, dove i pesi degli archi possono essere negativi, **Bellman-Ford** è l'algoritmo migliore poiché può gestire queste situazioni, e oltre a trovare i cammini minimi, può anche rilevare i cicli negativi.
- Se il problema riguarda **cicli massimi** in un grafo orientato pesato, potrebbe essere necessario un **approccio ricorsivo** per esplorare i cicli e calcolarne la somma dei pesi.
- **DFS** è spesso utile per rilevare la connessione tra i nodi o per esplorare un grafo completamente in profondità.