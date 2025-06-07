# Esercizio: Conteggio Nodi Raggiungibili in un Intervallo di Lunghezza (DAG)

Data la seguente traccia d'esame:

> Dato un grafo `G(V,E)` aciclico orientato e pesato con funzione peso non negativa `w`, due interi `l` e `h` contenuti in `N` con `l < h`, ed un nodo `s` contenuto in `V`. Scrivere un algoritmo in pseudocodice che restituisca il numero di nodi raggiungibili da `s` con un cammino minimo di lunghezza `m` tale che `l <= m <= h`.

## Spiegazione dell'Approccio

Il problema chiede di trovare il numero di nodi `v` (diversi dalla sorgente `s`) tali che:
1.  `v` sia raggiungibile da `s`.
2.  Il costo (o lunghezza, intesa come somma dei pesi) del **cammino minimo** da `s` a `v`, indicato con `dist[v]`, soddisfi la condizione `l <= dist[v] <= h`.

Per risolvere questo problema, seguiremo due passaggi principali:

1.  **Calcolo dei Cammini Minimi:** Utilizzeremo l'algoritmo di **Dijkstra** per calcolare le distanze minime da `s` a tutti gli altri nodi del grafo. Dijkstra è adatto perché i pesi degli archi sono non negativi. L'algoritmo di Dijkstra ci fornirà un array `dist` dove `dist[v]` è il costo del cammino minimo da `s` a `v`.
2.  **Conteggio dei Nodi Validi:** Una volta ottenute tutte le distanze minime, itereremo su tutti i nodi del grafo. Per ogni nodo `v` (diverso da `s`), controlleremo se è raggiungibile (cioè `dist[v]` non è infinito) e se `dist[v]` rientra nell'intervallo specificato `[l, h]`. Se entrambe le condizioni sono vere, incrementeremo un contatore.

## Algoritmo in Pseudocodice

```c
ALGORITMO CONTA_NODI_LUNGHEZZA_CAMMINO_MINIMO(Grafo G, FunzionePeso w, Nodo s, Intero l, Intero h)

  // PARTE 1: Algoritmo di Dijkstra per calcolare le distanze minime
  // Inizializzazione
  PER OGNI vertice v IN G.Venti:
    dist[v] = +INFINITO
  FINE PER
  dist[s] = 0

  // Coda a priorità (min-heap) per gestire i nodi da visitare
  CodaPriorita Q 
  AGGIUNGI_A_CODA(Q, s, dist[s]) // Aggiungi la sorgente con la sua distanza

  // Ciclo principale di Dijkstra
  MENTRE Q NON È VUOTA:
    Nodo u = ESTRAI_MIN(Q) // Estrae il nodo con la distanza minima corrente

    // Se la distanza minima per u è infinito, i nodi rimanenti in Q 
    // non sono raggiungibili da s, quindi possiamo interrompere.
    SE dist[u] == +INFINITO ALLORA
      INTERROMPI_CICLO 
    FINE SE

    // Rilassamento degli archi uscenti da u
    PER OGNI arco (u, v) CON PESO w_uv CHE ESCE DA u:
      SE dist[v] > dist[u] + w_uv ALLORA
        dist[v] = dist[u] + w_uv
        // Aggiorna la priorità di v in Q o lo aggiunge se non presente
        AGGIORNA_O_INSERISCI_IN_CODA(Q, v, dist[v]) 
      FINE SE
    FINE PER
  FINE MENTRE
  // A questo punto, l'array 'dist' contiene le distanze minime da 's'.

  // PARTE 2: Conteggio dei nodi che soddisfano la condizione
  contatore_nodi_validi = 0
  PER OGNI vertice v IN G.Venti:
    // Escludiamo il nodo sorgente 's' stesso dal conteggio
    SE v != s ALLORA
      // Controlla se v è raggiungibile E la sua distanza è nell'intervallo [l, h]
      SE dist[v] != +INFINITO ET dist[v] >= l ET dist[v] <= h ALLORA
        contatore_nodi_validi = contatore_nodi_validi + 1
      FINE SE
    FINE SE
  FINE PER

  RESTITUISCI contatore_nodi_validi

FINE ALGORITMO
```
---

## Esempio Pratico Svolto

![Imgur](https://i.imgur.com/9hiNXBS.png)

*   Nodi: S(0), A(1), B(2), C(3), D(4), E(5)
*   Sorgente `s = 0`
*   Archi e pesi:
    *   S(0) -> A(1) [3]
    *   S(0) -> B(2) [2]
    *   A(1) -> C(3) [1]
    *   A(1) -> D(4) [5]
    *   B(2) -> A(1) [1]
    *   B(2) -> D(4) [6]
    *   C(3) -> E(5) [4]
    *   D(4) -> E(5) [1]
*   Intervallo di lunghezza: `l = 4`, `h = 7`.

**1. Calcolo delle Distanze Minime da S(0) (usando Dijkstra):**

*   `dist[S(0)] = 0`
*   **Processa S(0) (dist=0):**
    *   `dist[A(1)] = min(INF, 0+3) = 3`
    *   `dist[B(2)] = min(INF, 0+2) = 2`
    *   `pq = [{2, B(2)}, {3, A(1)}]`
*   **Processa B(2) (dist=2):**
    *   `dist[A(1)] = min(3, 2+1) = 3` (nessun cambiamento per A)
    *   `dist[D(4)] = min(INF, 2+6) = 8`
    *   `pq = [{3, A(1)}, {8, D(4)}]`
*   **Processa A(1) (dist=3):**
    *   `dist[C(3)] = min(INF, 3+1) = 4`
    *   `dist[D(4)] = min(8, 3+5) = 8` (nessun cambiamento per D)
    *   `pq = [{4, C(3)}, {8, D(4)}]` (ipotizzando che D sia aggiornato o reinserito se la sua priorità cambia; in questo caso non cambia)
*   **Processa C(3) (dist=4):**
    *   `dist[E(5)] = min(INF, 4+4) = 8`
    *   `pq = [{8, D(4)}, {8, E(5)}]`
*   **Processa D(4) (dist=8):**
    *   `dist[E(5)] = min(8, 8+1) = 8` (nessun cambiamento per E)
    *   `pq = [{8, E(5)}]`
*   **Processa E(5) (dist=8):**
    *   Nessun arco uscente.
    *   `pq` è vuota.

Le distanze minime finali da S(0) sono:
*   `dist[S(0)] = 0`
*   `dist[A(1)] = 3`
*   `dist[B(2)] = 2`
*   `dist[C(3)] = 4`
*   `dist[D(4)] = 8`
*   `dist[E(5)] = 8`

**2. Conteggio dei Nodi Validi (`l=4, h=7`):**

*   **Nodo A(1):** `dist[A(1)]=3`. `3 >= 4` è FALSO. Non conta.
*   **Nodo B(2):** `dist[B(2)]=2`. `2 >= 4` è FALSO. Non conta.
*   **Nodo C(3):** `dist[C(3)]=4`. `4 >= 4` (VERO) AND `4 <= 7` (VERO). **Conta!** (Contatore = 1)
*   **Nodo D(4):** `dist[D(4)]=8`. `8 <= 7` è FALSO. Non conta.
*   **Nodo E(5):** `dist[E(5)]=8`. `8 <= 7` è FALSO. Non conta.

**Risultato Finale:** Il numero di nodi che soddisfano la condizione è **1** (solo il nodo C(3)).

L'output atteso del programma C++ per questo esempio sarà:
```
Numero di nodi raggiungibili con cammino minimo di lunghezza m (4 <= m <= 7): 1
```

---
