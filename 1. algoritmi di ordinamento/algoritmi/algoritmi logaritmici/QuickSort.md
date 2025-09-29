## **Quick Sort**
### Descrizione:
- Il Quick Sort funziona scegliendo un **pivot** (un elemento dell'array) e poi **partizionando** l'array in due sotto-array:
  - Uno con elementi **minori o uguali al pivot**.
  - Uno con elementi **maggiori del pivot**.
- Si applica ricorsivamente il processo ai due sotto-array.

---

### **Invariante di ciclo**:
> Al termine di ogni passaggio di partizionamento, il pivot è nella sua posizione corretta nell'array ordinato (schema di Lomuto), o l'array è partizionato in modo tale che tutti gli elementi a sinistra dell'indice di divisione sono minori o uguali a tutti gli elementi a destra (schema di Hoare).

---

### **Passi Fondamentali**:
1. **Inizializzazione**:
   - Si sceglie un pivot.
   - L'invariante è vera perché il pivot non ha ancora partizionato l'array.

2. **Conservazione**:
   - Durante il partizionamento, si riorganizzano gli elementi rispetto al pivot.
   - L'invariante è preservata perché gli elementi vengono scambiati per soddisfare la condizione.

3. **Conclusione**:
   - Alla fine, l'array è ordinato poiché tutti i sotto-array sono stati processati ricorsivamente.

---

### **Pseudocodice (Schema di Partizionamento Cormen)**:
Questo è lo schema più comune usata anche nel Cormen. Garantisce che il pivot si trovi nella sua posizione finale dopo ogni partizionamento.

```cpp
// Funzione per partizionare l'array (Cormen)
PARTITION(A, p, r)
    x <- A[r]         // Il pivot è l'ultimo elemento
    i <- p - 1
    for j <- p to r - 1
        if A[j] <= x
            i <- i + 1
            exchange A[i] with A[j]
    exchange A[i + 1] with A[r]
    return i + 1

// Funzione ricorsiva Quick Sort
QUICKSORT(A, p, r)
    if p < r
        q <- PARTITION(A, p, r) // Indice del pivot
        QUICKSORT(A, p, q - 1)
        QUICKSORT(A, q + 1, r)
```

---

### **Pseudocodice (Schema di Partizionamento di Hoare)**:
Questo è lo schema originale proposto da C.A.R. Hoare. È generalmente più veloce di quello di Lomuto perché esegue meno scambi in media. A differenza di Lomuto, **non** garantisce che l'elemento pivot sia nella sua posizione finale, ma restituisce un indice che divide l'array in due partizioni.

```cpp
// Funzione per partizionare l'array (Hoare)
HOARE-PARTITION(A, p, r)
    x <- A[p]  // Il pivot è il primo elemento
    i <- p - 1
    j <- r + 1
    while TRUE
        repeat
            j <- j - 1
        until A[j] <= x
        
        repeat
            i <- i + 1
        until A[i] >= x
        
        if i < j
            exchange A[i] with A[j]
        else
            return j

// Funzione ricorsiva Quick Sort con partizionamento di Hoare
QUICKSORT-HOARE(A, p, r)
    if p < r
        q <- HOARE-PARTITION(A, p, r)
        // Le chiamate ricorsive includono l'indice di partizione
        QUICKSORT-HOARE(A, p, q)
        QUICKSORT-HOARE(A, q + 1, r)

```

---

### **Esempio di Esecuzione (Schema Cormen)**:
Supponiamo di ordinare `{10, 80, 30, 90, 40, 50, 70}`:
1. **Primo passaggio**:
   - Pivot: \(70\).
   - Partizionamento: `{10, 30, 40, 50, 70, 90, 80}`. Il pivot \(70\) è nella posizione corretta.
2. **Secondo passaggio (sotto-array sinistro)**:
   - Pivot: \(50\).
   - Partizionamento: `{10, 30, 40, 50}`.
3. **Ricorsione continua** fino all'array ordinato: `{10, 30, 40, 50, 70, 80, 90}`.

---

### **Analisi dell'algoritmo**:
1. **Complessità temporale**:
   - Caso migliore: \(O(n log n)\), quando il pivot divide l'array in parti uguali.
   - Caso peggiore: \(O(n^2)\), quando il pivot è il minimo o massimo elemento (divisione sbilanciata).
   - Caso medio: \(O(n log n)\).

2. **Complessità spaziale**:
   - \(O(log n)\): per lo stack ricorsivo (nella versione in-place).
   - Non richiede array ausiliari.

---

### **Punti chiave sull'invariante**:
1. Dopo ogni partizionamento, l'array è diviso in due sezioni rispetto a un punto.
2. Gli elementi a sinistra sono sempre minori o uguali a quelli a destra.

---

### **Confronto con altri algoritmi**:
| **Caratteristica**      | **Quick Sort**          | **Merge Sort**         | **Insertion Sort**    |
|--------------------------|-------------------------|-------------------------|-----------------------|
| **Caso Migliore**         | \(O(n \log n)\)        | \(O(n \log n)\)        | \(O(n)\)             |
| **Caso Peggiore**         | \(O(n^2)\)             | \(O(n \log n)\)        | \(O(n^2)\)           |
| **Spazio Aggiuntivo**     | \(O(\log n)\)          | \(O(n)\)               | \(O(1)\)             |
| **Stabilità**             | No                     | Sì                     | Sì                   |
