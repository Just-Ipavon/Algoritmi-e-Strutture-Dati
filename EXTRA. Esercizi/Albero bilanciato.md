# Controllo di un Albero Bilanciato

## Problema
Un albero binaio `T` è bilanciato se la profondità di ogni fogli anon è maggiore di 1 rispetto alla profondità delle altre foglie. Scrivere un algoritmo in pseudocodice ricororsivo che restituisca `TRUE` se `T` è bilanciato o `FALSE` altrimenti.

---

## Logica dell'Algoritmo

1.  **Analisi dell'albero:** Utilizzare l'algoritmo DFS per per controllare la profondità dell'albero
2.  **Analisi Bilanciamento:** Controllare se la differenza tra la `profondità massima` e la `profondità minima` sia minore o uguale a `1`

---

## Algoritmo DFS
L'algoritmo di DFS calcola ricorsivamente la profondità dell'albero preso in esame, fermandosi quando non ha più nodi da esaminare

---

## Pseudocodice: Calcolo Profondità e controllo Bilanciamento

```c
funzione isBalanced(Albero T): // Rinominato T per coerenza con l'input
    // Assumiamo che T sia l'albero, e T.radice sia il nodo radice.
    // Oppure che T sia direttamente il nodo radice.

    // Gestione caso albero vuoto o radice nulla
    SE T == NIL O T.radice == NIL ALLORA // Se T è un puntatore al nodo radice o l'albero ha una radice nulla
        RITORNA VERO // Convenzione: albero vuoto è bilanciato
    FINE SE

    profonditaFoglie = NUOVA_LISTA_VUOTA // Inizializza una lista vuota

    // Chiamata alla dfs partendo dalla radice
    // Se T è l'albero, si chiamerebbe dfs(T.radice, ...)
    // Se T è già il nodo radice, dfs(T, ...)
    dfs(T.radice, 0, profonditaFoglie) // Assumendo profondità radice = 0

    // Gestione caso in cui non ci sono foglie (solo se l'albero era solo la radice)
    // o una sola foglia. In entrambi i casi è bilanciato.
    SE profonditaFoglie.dimensione() <= 1 ALLORA
        RITORNA VERO
    FINE SE
    
    minProf = minimo(profonditaFoglie) // Trova il minimo nella lista
    maxProf = massimo(profonditaFoglie) // Trova il massimo nella lista
    
    RITORNA (maxProf - minProf) <= 1
FINE FUNZIONE


PROCEDURA dfs(nodo, prof, RIFERIMENTO profonditaFoglie): // 'profonditaFoglie' passata per riferimento
    SE nodo == NIL ALLORA: // Caso base per nodi nulli
        RITORNA
    FINE SE
    
    SE nodo.sinistro == NIL ET nodo.destro == NIL ALLORA: // Controlla se è una foglia
        AGGIUNGI prof A profonditaFoglie
        // Non c'è bisogno di ritornare qui, la ricorsione sui figli (NIL) terminerà subito.
        // Ma per chiarezza, si potrebbe anche mettere un return se si vuole evitare
        // le chiamate a dfs(NIL, ...).
    FINE SE
    
    dfs(nodo.sinistro, prof + 1, profonditaFoglie)
    dfs(nodo.destro, prof + 1, profonditaFoglie)
FINE PROCEDURA
```
---

**Esempio 1: Albero Bilanciato**

**Definizione di Bilanciamento:** 
> "la profondità di ogni foglia non è maggiore di 1 rispetto alla profondità delle altre foglie."

**Albero T1:**

```
      A (prof 0)
     / \
    B   C (prof 1)
   /   / \
  D   E   F (prof 2)
     /
    G (prof 3)
```

*   **Nodo A:** Radice, profondità 0
*   **Nodi B, C:** Figli di A, profondità 1
*   **Nodi D, E, F:** Figli di B o C, profondità 2
*   **Nodo G:** Figlio di E, profondità 3

**Foglie e Loro Profondità (T1):**
*   **D:** profondità 2 (percorso A -> B -> D)
*   **G:** profondità 3 (percorso A -> C -> E -> G)
*   **F:** profondità 2 (percorso A -> C -> F)

**Svolgimento dell'Algoritmo `isBalanced(T1)`:**

1.  `profonditaFoglie = []`
2.  `dfs(A, 0, profonditaFoglie)`:
    *   `dfs(B, 1, profonditaFoglie)`:
        *   `dfs(D, 2, profonditaFoglie)`: D è foglia. `profonditaFoglie.aggiungi(2)`. Lista: `[2]`
        *   `dfs(NIL, 2, ...)` (figlio destro di B)
    *   `dfs(C, 1, profonditaFoglie)`:
        *   `dfs(E, 2, profonditaFoglie)`:
            *   `dfs(G, 3, profonditaFoglie)`: G è foglia. `profonditaFoglie.aggiungi(3)`. Lista: `[2, 3]`
            *   `dfs(NIL, 3, ...)` (figlio destro di G)
            *   `dfs(NIL, 3, ...)` (figlio sinistro di G)
        *   `dfs(F, 2, profonditaFoglie)`: F è foglia. `profonditaFoglie.aggiungi(2)`. Lista: `[2, 3, 2]`
        *   `dfs(NIL, 2, ...)` (figlio destro di C)
3.  Dopo tutte le chiamate DFS, `profonditaFoglie = [2, 3, 2]`.
4.  `profonditaFoglie.dimensione()` è 3, che non è `<= 1`.
5.  `minProf = minimo([2, 3, 2]) = 2`
6.  `maxProf = massimo([2, 3, 2]) = 3`
7.  `ritorna (maxProf - minProf) <= 1`
    `ritorna (3 - 2) <= 1`
    `ritorna (1) <= 1` che è **VERO**.

**Conclusione per T1:** L'albero è **BILANCIATO**. Le foglie si trovano a profondità 2 e 3, e la differenza è 1.

---

**Esempio 2: Albero NON Bilanciato**

**Albero T2:**

```

      A (prof 0)
     / \
    B   F (prof 1)  <-- FOGLIA
   /
  C (prof 2)
 /
D (prof 3)
 \
  E (prof 4)   <-- FOGLIA
```

**Foglie e Loro Profondità (T2):**
*   **F:** profondità 1 (percorso A -> F)
*   **E:** profondità 4 (percorso A -> B -> C -> D -> E)

**Svolgimento dell'Algoritmo `isBalanced(T2)`:**

1.  `profonditaFoglie = []`
2.  `dfs(A, 0, profonditaFoglie)`:
    *   `dfs(B, 1, profonditaFoglie)`:
        *   `dfs(C, 2, profonditaFoglie)`:
            *   `dfs(D, 3, profonditaFoglie)`:
                *   `dfs(NIL, 4, ...)` (figlio sinistro di D)
                *   `dfs(E, 4, profonditaFoglie)`: E è foglia. `profonditaFoglie.aggiungi(4)`. Lista: `[4]`
    *   `dfs(F, 1, profonditaFoglie)`: F è foglia. `profonditaFoglie.aggiungi(1)`. Lista: `[4, 1]`
3.  Dopo tutte le chiamate DFS, `profonditaFoglie = [4, 1]`.
4.  `profonditaFoglie.dimensione()` è 2, che non è `<= 1`.
5.  `minProf = minimo([4, 1]) = 1`
6.  `maxProf = massimo([4, 1]) = 4`
7.  `ritorna (maxProf - minProf) <= 1`
    `ritorna (4 - 1) <= 1`
    `ritorna (3) <= 1` che è **FALSO**.

**Conclusione per T2:** L'albero è **NON BILANCIATO**. Le foglie si trovano a profondità 1 e 4, e la differenza è 3, che è maggiore di 1.

---
