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

## Riassunto

L'approccio consiste nel:
1.  Eseguire Bellman-Ford per ottenere l'albero dei cammini minimi dalla sorgente `s` (memorizzato come array di distanze `d` e predecessori `pi`).
2.  Se vengono rilevati cicli negativi, il problema non ha soluzione definita.
3.  Altrimenti, per ogni nodo `v` raggiungibile, si calcola la sua profondità (numero di archi) nel cammino minimo risalendo da `v` a `s` tramite i predecessori `pi`.
4.  La profondità massima trovata tra tutti i nodi raggiungibili è il risultato.
