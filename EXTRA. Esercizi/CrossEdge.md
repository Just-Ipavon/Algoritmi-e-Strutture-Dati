# Rilevamento e Conteggio degli Archi Trasversali in un Grafo Orientato

## Problema

Dato un grafo orientato `G=(V,E)`, scrivere un algoritmo che utilizzi la Visita in Profondità (DFS) per identificare e restituire il numero totale degli **archi trasversali** (cross edges) presenti nel grafo.

---

## Spiegazione dell'Approccio e Classificazione degli Archi

Utilizzeremo una **Visita in Profondità (DFS)** per analizzare il grafo. Durante la DFS, quando esploriamo un arco `(u, v)`, lo classifichiamo in base allo stato (colore) di `v` e ai tempi di scoperta/fine.

**Colori dei Nodi (attributo `colore[nodo]`):**
*   `BIANCO`: Non visitato.
*   `GRIGIO`: Scoperto, visita in corso (nello stack di ricorsione).
*   `NERO`: Visita completata.

**Tempi della DFS (attributi `d[nodo]` e `f[nodo]`):**
*   `d[u]`: Tempo di **scoperta** di `u` (quando `colore[u]` diventa `GRIGIO`).
*   `f[u]`: Tempo di **fine visita** di `u` (quando `colore[u]` diventa `NERO`).

**Classificazione degli Archi `(u, v)`:**

1.  **Tree Edge:** Se `colore[v]` è `BIANCO`.
2.  **Back Edge:** Se `colore[v]` è `GRIGIO`. Indica un ciclo.
3.  **Forward Edge o Cross Edge:** Se `colore[v]` è `NERO`.
    *   **Forward Edge:** Se `d[u] < d[v]`. `v` è un discendente di `u` già processato.
    *   **Cross Edge:** Se `d[u] > d[v]`. `v` non è discendente di `u` ed è stato processato in un altro sottoalbero DFS o in un ramo precedente.

L'obiettivo è contare i **Cross Edge**.

---

## Algoritmo in Pseudocodice

```c
// Variabili globali
CONTATORE-CROSS-EDGE
TEMPO

DFS-CONTA-CROSS-EDGES(G)
  PER ogni vertice u ∈ G.V
    colore[u] ← BIANCO
    π[u] ← NIL // Predecessore, standard in DFS Cormen
  TEMPO ← 0
  CONTATORE-CROSS-EDGE ← 0
  PER ogni vertice u ∈ G.V
    SE colore[u] = BIANCO // Confronto
      DFS-VISIT-CONTA-CROSS(G, u)
  RITORNA CONTATORE-CROSS-EDGE

DFS-VISIT-CONTA-CROSS(G, u)
  TEMPO ← TEMPO + 1
  d[u] ← TEMPO
  colore[u] ← GRIGIO
  PER ogni vertice v ∈ G.Adg[u] // G.Adg[u] è la lista di adiacenza di u
    SE colore[v] = BIANCO // Confronto
      π[v] ← u
      DFS-VISIT-CONTA-CROSS(G, v)
    ALTRIMENTI SE colore[v] = NERO // Confronto
      // Se u è stato scoperto DOPO v (d[u] > d[v]), allora (u,v) è un cross edge.
      SE d[u] > d[v] 
        CONTATORE-CROSS-EDGE ← CONTATORE-CROSS-EDGE + 1
  colore[u] ← NERO
  TEMPO ← TEMPO + 1
  f[u] ← TEMPO
```

---

## Immagine Illustrativa

![Esempio Grafo con Archi Classificati](https://i.imgur.com/cq1xivq.png)

*   🟩 **Verde (Tree Edges):** Archi che formano l'albero DFS.
*   🟧 **Arancione (Forward Edge):** Da `u` a `v` (`colore[v]`=`NERO`), con `d[u] < d[v]`.
*   🔵 **Blu (Cross Edge):** Da `u` a `v` (`colore[v]`=`NERO`), con `d[u] > d[v]`. **Questi vengono contati.**

---

### Esempio di Verifica con Tempi DFS

Assumiamo i seguenti tempi calcolati da una DFS:

| Nodo | d[] | f[] |
| ---- | --- | --- |
| A    | 1   | 10  |
| B    | 2   | 9   |
| C    | 3   | 4   |
| D    | 5   | 8   |
| E    | 6   | 7   |

**Analisi dell'arco `(u,v)` quando `colore[v]` è `NERO`:**

1.  **Arco `(B,C)` (ipotetico):**
    *   `u=B`, `v=C`. `colore[C]` è `NERO`.
    *   `d[B] = 2`, `d[C] = 3`.
    *   Poiché `d[B] < d[C]` (`2 < 3`), è un **Forward Edge**. Non viene contato.

2.  **Arco `(D,B)` (ipotetico):**
    *   `u=D`, `v=B`. `colore[B]` è `NERO`.
    *   `d[D] = 5`, `d[B] = 2`.
    *   Poiché `d[D] > d[B]` (`5 > 2`), è un **Cross Edge**. `CONTATORE-CROSS-EDGE` viene incrementato.

---

## Riassunto

L'algoritmo esegue una DFS, mantenendo per ogni nodo `u` il suo `colore`, e i tempi di scoperta `d[u]` e fine `f[u]`. Per ogni arco `(u,v)`:
*   Se `colore[v]` è `NERO` (cioè `v` è già stato completamente visitato) e `d[u] > d[v]` (cioè `u` è stato scoperto dopo `v`), allora `(u,v)` è un arco trasversale, e il contatore `CONTATORE-CROSS-EDGE` viene incrementato.
Il valore finale di `CONTATORE-CROSS-EDGE` è il risultato.

---
