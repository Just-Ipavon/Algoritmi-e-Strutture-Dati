# Minimum Spanning Tree (MST)

Un **Minimum Spanning Tree** (MST) è un sotto-grafo di un grafo connesso e pesato che include tutti i vertici del grafo originale e un insieme di archi tali che il peso totale degli archi sia minimo. Inoltre, l'albero di copertura (spanning tree) non ha cicli e connette tutti i vertici del grafo.

### Proprietà di un MST:
- **Connesso**: Tutti i vertici sono connessi tra loro.
- **Senza cicli**: Non ci sono cicli tra gli archi.
- **Peso minimo**: La somma dei pesi degli archi è minima.

### Problema:
Dato un grafo connesso e pesato, trovare l'MST che collega tutti i vertici con il costo totale minimo.

Esistono diversi algoritmi per risolvere il problema del Minimum Spanning Tree. I due più comuni sono:

1. **Kruskal’s Algorithm**
2. **Prim’s Algorithm**

## 1. [Kruskal's Algorithm](algoritmi/Kruskal.md)

L'algoritmo di **Kruskal** è un algoritmo greedy che costruisce l'MST selezionando gli archi in ordine crescente di peso, garantendo che non venga mai creato un ciclo.

### Procedura:

1. **Ordinare gli archi** del grafo in ordine crescente di peso.
2. **Selezionare il primo arco** nell'ordine e aggiungerlo all'albero (se non crea un ciclo).
3. Continuare a selezionare archi finché l'albero non contiene \( V - 1 \) archi, dove \( V \) è il numero di vertici del grafo.

### Pseudocodice di Kruskal:

```cpp
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
- Ordinamento degli archi: \( O(E \log E) \), dove \( E \) è il numero di archi.
- Operazioni di unione e ricerca (con **Union-Find**): \( O(\alpha(V)) \), dove \( \alpha \) è la funzione di Ackermann, che è praticamente costante per valori ragionevoli di \( V \).

### Esempio:
Immagina un grafo con 5 nodi e 7 archi con pesi associati. L'algoritmo di Kruskal ordinerà gli archi in base al peso, selezionerà i più piccoli evitando i cicli, fino a completare l'MST.

## 2. [Prim's Algorithm](algoritmi/Prim.md)

L'algoritmo di **Prim** è un altro algoritmo greedy che, a partire da un nodo arbitrario, costruisce l'MST espandendo l'albero selezionando gli archi di peso minimo che collegano un nodo dell'albero a un nodo esterno.

### Procedura:

1. Iniziare con un nodo arbitrario e aggiungere i suoi archi al grafo.
2. Selezionare l'arco con il peso minimo che collega un nodo nell'albero a un nodo esterno.
3. Ripetere il passo precedente fino a che tutti i nodi non siano inclusi nell'albero.

### Pseudocodice di Prim:

```cpp
function Prim(grafo, nodo_iniziale):
    MST = insieme vuoto
    chiave[nodo_iniziale] = 0
    inizializzare la coda di priorità con i nodi e i pesi
    mentre la coda non è vuota:
        nodo = nodo con la chiave minima
        aggiungi nodo a MST

        per ogni vicino v di nodo:
            se v non è in MST e peso(nodo, v) < chiave[v]:
                chiave[v] = peso(nodo, v)
                aggiorna la priorità di v nella coda

    return MST
```

### Complessità:
- Utilizzando una coda di priorità (heap binario), la complessità temporale è \( O(E \log V) \), dove \( E \) è il numero di archi e \( V \) è il numero di vertici.
  
### Esempio:
In un grafo connesso, partendo da un nodo arbitrario, Prim esplorerà il grafo selezionando sempre l'arco con il peso minimo che collega l'albero in costruzione a un nodo non ancora visitato.

## Confronto tra Kruskal e Prim

| Proprietà         | Kruskal                         | Prim                              |
|-------------------|---------------------------------|-----------------------------------|
| **Tipo di grafo** | Adatto per grafi sparsi         | Adatto per grafi densi            |
| **Tipo di operazione** | Basato sugli archi            | Basato sui nodi                   |
| **Complessità**   | \( O(E log E) \)               | \( O(E log V) \)                 |

## Conclusioni

- **Kruskal's Algorithm** è generalmente più semplice da implementare e più adatto per grafi sparsi, dove il numero di archi è molto inferiore al numero di nodi.
- **Prim's Algorithm** è più efficiente quando si tratta di grafi densi, dove il numero di archi è vicino al massimo possibile.

Entrambi gli algoritmi sono efficaci e si adattano a diversi tipi di grafi. La scelta dell'algoritmo dipende dalla struttura del grafo e dalle specifiche esigenze del problema.
