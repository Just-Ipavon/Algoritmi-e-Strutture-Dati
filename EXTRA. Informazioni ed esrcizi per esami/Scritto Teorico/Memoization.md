# Memoization: Problema CALCOLA-NUMERI

## Problema

Risolvere con la tecnica della `memoization` il seguente problema `CALCOLA-NUMERI` descritto dall'equazione di ricorrenza:

`G(n) = G(n-1) + G(n-2) + G(n-3)` 

con i seguenti casi base:
*   `G(0) = 1`
*   `G(1) = 1`
*   `G(2) = 1`

---

## Spiegazione dell'Approccio

Il problema presenta una funzione definita da una relazione di ricorrenza lineare, simile alla sequenza di Fibonacci ma che dipende dai tre termini precedenti (a volte chiamata sequenza di Tribonacci, sebbene i casi base qui siano specifici).

Una semplice implementazione ricorsiva di `G(n)` comporterebbe il ricalcolo ripetuto degli stessi valori di `G(k)` per `k < n`, portando a una complessità esponenziale.

La tecnica della **memoization** (una forma di programmazione dinamica top-down) ottimizza questo processo. L'idea è di memorizzare il risultato di ogni chiamata `G(k)` la prima volta che viene calcolato.
Le volte successive che `G(k)` è necessario, il suo valore viene recuperato dalla memoria (ad esempio, una tabella o un dizionario) invece di essere ricalcolato. 
Questo riduce drasticamente il numero di calcoli, portando a una complessità temporale molto più efficiente (tipicamente lineare nel valore di `n` per questo tipo di ricorrenza, se consideriamo il numero di stati unici `G(0)...G(n)`).

---

## Algoritmo in Pseudocodice

```c
// 'memo' è una struttura dati (es. array o dizionario/mappa) usata per la memoization.


memo = DIZIONARIO_VUOTO 

FUNZIONE CALCOLA_NUMERI_MEMOIZED(n):
    // 1. Controlla se il risultato per n è già in memoria
    SE n È UNA CHIAVE IN memo ALLORA:
        RITORNA memo[n]
    FINE SE

    // 2. Calcola il risultato (se non in memoria)
    risultato <- 0 
    // Casi base specifici del problema: G(0)=1, G(1)=1, G(2)=1
    SE n <= 2 ALLORA:
        risultato <- 1
    // Passo ricorsivo per n > 2
    ALTRIMENTI: 
        risultato <- CALCOLA_NUMERI_MEMOIZED(n-1) + CALCOLA_NUMERI_MEMOIZED(n-2) + CALCOLA_NUMERI_MEMOIZED(n-3)
    FINE SE

    // 3. Memorizza il risultato prima di restituirlo
    memo[n] <- risultato
    RITORNA risultato
FINE FUNZIONE

```

---

**Valori della sequenza G(n) con G(0)=G(1)=G(2)=1:**
*   G(0) = 1
*   G(1) = 1
*   G(2) = 1
*   G(3) = G(2)+G(1)+G(0) = 1+1+1 = 3
*   G(4) = G(3)+G(2)+G(1) = 3+1+1 = 5
*   G(5) = G(4)+G(3)+G(2) = 5+3+1 = 9
*   ... e così via.

---

## Riassunto
L'algoritmo utilizza la memoization per memorizzare i risultati intermedi della funzione di ricorrenza `G(n)`. Questo evita ricalcoli ridondanti delle stesse sotto-problemi, trasformando una potenziale soluzione esponenziale in una lineare rispetto al numero di stati unici calcolati (da 0 a n). La tabella `memo` è cruciale per questa ottimizzazione.
