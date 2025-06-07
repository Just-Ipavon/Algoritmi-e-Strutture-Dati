# Controllo dei vertici di un Grafo

## Problema
Dato un grafo orientato `G(V,E)` scrivere un algoritmo in pseudocodice che restituisca il numero dei cicli con numero di vertici maggiore di uno.

---

## Logica dell'Algoritmo
Un grafo orientato è visitabile grazie all'algoritmo di DFS e grazie ad esso possiamo controllare se durante la visita troviamo un altro nodo definito come vertice

---
**Algoritmo:**

1.  Utilizza una DFS standard per visitare il grafo.
2.  Si mantiene traccia dello stato di visita di ogni nodo (WHITE, GRAY, BLACK).
3.  Quando da un nodo `u` (GRAY) si esplora un arco `(u,v)` e si trova che `v` è anch'esso GRAY (cioè `v` è un antenato di `u` nello stack di ricorsione DFS), si è trovato un arco all'indietro che chiude un ciclo.
4.  Se `v` è diverso da `u`, questo ciclo coinvolge più di un vertice. Incrementa un contatore.


---

## Pseudocodice
```c
// Variabili globali o passate come parametri e modificate per riferimento
colore: array[1..N_vertici]   // Valori: WHITE, GRAY, BLACK
contatore_cicli_rilevati: intero

// Funzione principale che inizializza e avvia la DFS
Funzione NUMERO_CICLI_MAGGIORI_DI_UNO(Grafo G)
  PER OGNI vertice u IN G.Venti:
    colore[u] = WHITE
  FINE PER
  contatore_cicli_rilevati = 0

  PER OGNI vertice u IN G.Venti:
    SE colore[u] == WHITE ALLORA
      DFS_VISIT_CONTA_CICLI(G, u) // 'contatore_cicli_rilevati' è globale
    FINE SE
  FINE PER
  
  RITORNA contatore_cicli_rilevati
FINE FUNZIONE


// Procedura ricorsiva DFS per visitare e contare
PROCEDURA DFS_VISIT_CONTA_CICLI(Grafo G, Nodo u)
  colore[u] = GRAY

  PER OGNI vertice v IN G.Adiacenti[u]: // Per ogni vicino v di u
    SE colore[v] == WHITE ALLORA
      DFS_VISIT_CONTA_CICLI(G, v)
    ALTRIMENTI SE colore[v] == GRAY ALLORA
      // Arco (u,v) verso un nodo grigio: è un arco all'indietro.
      // Se v != u, il ciclo formato ha più di un vertice.
      SE v != u THEN
        contatore_cicli_rilevati = contatore_cicli_rilevati + 1
      END IF
    END IF
  FINE PER

  colore[u] = BLACK // Visita di u e dei suoi discendenti completata
FINE PROCEDURA
```
---

## Esempio pratico:

![graph](https://i.imgur.com/GItBe57.png)

*   **Ciclo 1 (C1):** A -> B -> C -> A
*   **Ciclo 2 (C2):** B -> D -> E -> B
*   **Cappio:** F -> F

**Algoritmo (come definito prima):**
`NUMERO_CICLI_MAGGIORI_DI_UNO(G1)`

Variabili:
`colore`: inizializzato a WHITE per tutti
`contatore_cicli_rilevati = 0`

**Esecuzione della DFS (un possibile ordine di visita):**

Supponiamo che il loop esterno di `NUMERO_CICLI_MAGGIORI_DI_UNO` processi i nodi in ordine alfabetico: A, B, C, D, E, F.

1.  **Chiama `DFS_VISIT_CONTA_CICLI(G1, A)` (colore[A] == WHITE)**
    *   `colore[A] = GRAY`
    *   Vicini di A: {B}
        *   `colore[B] == WHITE`. Chiama `DFS_VISIT_CONTA_CICLI(G1, B)`
            *   `colore[B] = GRAY`
            *   Vicini di B: {C, D}
                *   (Processa C) `colore[C] == WHITE`. Chiama `DFS_VISIT_CONTA_CICLI(G1, C)`
                    *   `colore[C] = GRAY`
                    *   Vicini di C: {A, D}
                        *   (Processa A) `colore[A] == GRAY`.
                            *   `A != C` è VERO. **Rilevato arco all'indietro `C -> A`**.
                            *   `contatore_cicli_rilevati = 1`.
                        *   (Processa D) `colore[D] == WHITE`. Chiama `DFS_VISIT_CONTA_CICLI(G1, D)`
                            *   `colore[D] = GRAY`
                            *   Vicini di D: {E}
                                *   `colore[E] == WHITE`. Chiama `DFS_VISIT_CONTA_CICLI(G1, E)`
                                    *   `colore[E] = GRAY`
                                    *   Vicini di E: {B}
                                        *   `colore[B] == GRAY`.
                                            *   `B != E` è VERO. **Rilevato arco all'indietro `E -> B`**.
                                            *   `contatore_cicli_rilevati = 2`.
                                    *   `colore[E] = BLACK`
                            *   `colore[D] = BLACK`
                    *   `colore[C] = BLACK`
                *   (Torna a B, D è già BLACK perché visitato tramite C). `colore[D] == BLACK`. Non fa nulla.
            *   `colore[B] = BLACK`
    *   `colore[A] = BLACK`

2.  Il loop esterno continua. B, C, D, E sono ora BLACK.
3.  **Chiama `DFS_VISIT_CONTA_CICLI(G1, F)` (colore[F] == WHITE)**
    *   `colore[F] = GRAY`
    *   Vicini di F: {A, F}
        *   (Processa A) `colore[A] == BLACK`. Non fa nulla.
        *   (Processa F) `colore[F] == GRAY`.
            *   `F != F` è FALSO. Questo è un cappio. **Non incrementa** `contatore_cicli_rilevati`.
    *   `colore[F] = BLACK`

**Risultato Finale:**
`contatore_cicli_rilevati` sarà **2**.

**Analisi dei Rilevamenti:**
*   L'arco `C -> A` chiude il ciclo C1 (A-B-C-A). Contato 1.
*   L'arco `E -> B` chiude il ciclo C2 (B-D-E-B). Contato 1.
*   Il cappio `F -> F` è stato correttamente ignorato dal contatore perché `v == u`.

**Cosa succederebbe se la DFS visitasse i vicini in un ordine diverso?**
Supponiamo che durante la visita di B, D venga processato prima di C:

1.  **Chiama `DFS_VISIT_CONTA_CICLI(G1, A)`**
    *   `A` diventa GRAY
    *   Chiama `DFS_VISIT_CONTA_CICLI(G1, B)`
        *   `B` diventa GRAY
        *   Vicini di B: {D, C} (supponiamo questo ordine)
            *   (Processa D) `colore[D] == WHITE`. Chiama `DFS_VISIT_CONTA_CICLI(G1, D)`
                *   `D` diventa GRAY
                *   Chiama `DFS_VISIT_CONTA_CICLI(G1, E)`
                    *   `E` diventa GRAY
                    *   Vicini di E: {B}
                        *   `colore[B] == GRAY`. `B != E`. `contatore_cicli_rilevati = 1` (Ciclo B-D-E-B rilevato).
                    *   `E` diventa BLACK
                *   `D` diventa BLACK
            *   (Processa C) `colore[C] == WHITE`. Chiama `DFS_VISIT_CONTA_CICLI(G1, C)`
                *   `C` diventa GRAY
                *   Vicini di C: {A, D}
                    *   (Processa A) `colore[A] == GRAY`. `A != C`. `contatore_cicli_rilevati = 2` (Ciclo A-B-C-A rilevato).
                    *   (Processa D) `colore[D] == BLACK`. Non fa nulla.
                *   `C` diventa BLACK
        *   `B` diventa BLACK
    *   `A` diventa BLACK
    *   ... (poi F come prima, non cambia il contatore)

Il risultato è sempre **2**.

---
