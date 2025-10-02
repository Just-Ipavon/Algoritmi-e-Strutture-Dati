## **Randomized Quick Sort**
### Descrizione:
Il **Randomized Quick Sort** è una variante del Quick Sort che sceglie il **pivot** in modo casuale, invece di seguire una strategia predefinita come scegliere l'ultimo elemento, il primo elemento o un elemento centrale. Questo approccio aiuta a evitare il caso peggiore \(O(n^2)\), che si verifica quando l'array è già ordinato o parzialmente ordinato, ed è più probabile che accada quando il pivot è scelto in modo sistematico.

Il Randomized Quick Sort funziona in modo simile al Quick Sort tradizionale:
1. Sceglie un **pivot casuale**.
2. **Partiziona** l'array in due sotto-array: uno con elementi minori o uguali al pivot e l'altro con elementi maggiori.
3. Applica ricorsivamente il processo ai due sotto-array.

---

### **Invariante di ciclo**:
> Al termine di ogni passaggio di partizionamento, il pivot casuale è nella sua posizione corretta nell'array ordinato, e tutti gli elementi a sinistra sono minori o uguali, mentre quelli a destra sono maggiori.

---

### **Passi Fondamentali**:
1. **Inizializzazione**:
   - Si sceglie un pivot casuale (anziché l'ultimo, il primo o un altro punto fisso dell'array).
   - L'invariante è vera perché il pivot non ha ancora partizionato l'array.

2. **Conservazione**:
   - Durante il partizionamento, si riorganizzano gli elementi rispetto al pivot scelto casualmente.
   - L'invariante è preservata perché il pivot viene collocato correttamente.

3. **Conclusione**:
   - Alla fine, l'array è ordinato poiché tutti i sotto-array sono stati processati ricorsivamente.

---

### **Pseudocodice Cormen**:

```cpp

RANDOMIZEDPARTITION(A, p, r)
   i <- Random(p,r)
   exchange A[i] with A[p]
   Partition(A,p.r)


// Funzione per partizionare l'array (Cormen)
PARTITION(A, p, r)
    x <- A[r]         
    i <- p - 1
    for j <- p to r - 1
        if A[j] <= x
            i <- i + 1
            exchange A[i] with A[j]
    exchange A[i + 1] with A[r]
    return i + 1

// Funzione ricorsiva Quick Sort
RANDOMIZEDQUICKSORT(A, p, r)
    if p < r
        q <- RANDOMIZEDPARTITION(A, p, r) // Indice del pivot
        RANDOMIZEDQUICKSORT(A, p, q )
        RANDOMIZEDQUICKSORT(A, q + 1, r)
```

---

### **Esempio di Esecuzione**:
Supponiamo di ordinare `{10, 80, 30, 90, 40, 50, 70}` con il Randomized Quick Sort:
1. **Primo passaggio**:
   - Supponiamo che il pivot scelto casualmente sia \(40\).
   - Partizionamento: `{10, 30, 40, 90, 80, 50, 70}`. Il pivot \(40\) è nella posizione corretta.
2. **Secondo passaggio (sotto-array sinistro)**:
   - Pivot casuale scelto: \(30\).
   - Partizionamento: `{10, 30}`.
3. **Ricorsione continua** fino all'array ordinato: `{10, 30, 40, 50, 70, 80, 90}`.

---

### **Analisi dell'algoritmo**:
1. **Complessità temporale**:
   - **Caso migliore**: \(O(n  log n)\), quando il pivot divide l'array in parti uguali.
   - **Caso peggiore**: \(O(n^2)\), ma con una probabilità molto bassa, dato che la scelta casuale del pivot riduce drasticamente il rischio di avere una partizione sbilanciata.
   - **Caso medio**: \(O(n  log n)\), che si verifica con alta probabilità.

2. **Complessità spaziale**:
   - **Spazio dello stack ricorsivo**: \(O( log n)\), come per il Quick Sort tradizionale.
   - **Spazio ausiliario**: Nessun array ausiliario necessario.

---

### **Punti chiave sull'invariante**:
1. Dopo ogni partizionamento, il pivot casuale è nella posizione corretta.
2. Gli elementi a sinistra sono sempre minori o uguali al pivot, quelli a destra sempre maggiori.

---

### **Confronto con altri algoritmi**:
| **Caratteristica**      | **Randomized Quick Sort**  | **Merge Sort**         | **Insertion Sort**    |
|--------------------------|----------------------------|------------------------|-----------------------|
| **Caso Migliore**         | \(O(n  log n)\)           | \(O(n  log n)\)        | \(O(n)\)              |
| **Caso Peggiore**         | \(O(n^2)\)                | \(O(n  log n)\)        | \(O(n^2)\)            |
| **Spazio Aggiuntivo**     | \(O( log n)\)             | \(O(n)\)               | \(O(1)\)              |
| **Stabilità**             | No                        | Sì                     | Sì                    |
