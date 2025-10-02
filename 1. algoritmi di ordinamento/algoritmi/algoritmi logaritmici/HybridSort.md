## **Hybrid Sort (Quicksort + Insertion Sort)**
### Descrizione:
- Questo Hybrid Sort è un algoritmo di ordinamento ottimizzato che combina i punti di forza di **Quicksort** e **Insertion Sort**.
- L'obiettivo è ottenere la massima velocità pratica, sfruttando la performance di Quicksort su array grandi e l'efficienza di Insertion Sort su quelli piccoli.
- La strategia è la seguente:
  1.  Inizia con **Quicksort** per partizionare ricorsivamente l'array, data la sua eccellente performance media.
  2.  Quando la dimensione di un sotto-array da ordinare scende al di sotto di una certa soglia **M**, l'algoritmo passa a **Insertion Sort**, che è più veloce per piccoli insiemi di dati a causa del suo basso overhead.

---

### **Invariante di ciclo**:
> L'algoritmo mantiene il progresso verso un array ordinato. I sotto-array più grandi della soglia M vengono partizionati correttamente da Quicksort, mentre i sotto-array più piccoli vengono ordinati completamente da Insertion Sort.

---

### **Passi Fondamentali**:
1. **Inizializzazione**:
   - Si avvia l'algoritmo Quicksort con una soglia di dimensione predefinita `M`.

2. **Conservazione**:
   - Ad ogni chiamata ricorsiva, si controlla la dimensione del sotto-array:
     - **Soglia di dimensione**: Se il sotto-array è piccolo (dimensione `<= M`), si usa Insertion Sort e la ricorsione per quel ramo termina.
     - **Caso standard**: Altrimenti, si sceglie un pivot, si partiziona con Quicksort e si continua la ricorsione sulle due metà.

3. **Conclusione**:
   - L'algoritmo termina quando tutti i sotto-array sono stati ordinati (o perché partizionati fino a diventare piccoli, o perché ordinati direttamente da Insertion Sort).

---

### **Pseudocodice (Stile Implementativo)**:

```cpp
const M <- 10

// Scambia due elementi in un array A nelle posizioni i e j
SWAP(A, i, j)
    temp <- A[i]
    A[i] <- A[j]
    A[j] <- temp

// Confronta due elementi in A e li scambia se sono nell'ordine sbagliato.
COMPSWAP(A, i, j)
    if A[i] > A[j]
        SWAP(A, i, j)

// --- Insertion Sort (per piccoli array) ---
INSERTION-SORT(A, p, r)
    for j <- p + 1 to r
        chiave <- A[j]
        i <- j - 1
        while i >= p and A[i] > chiave
            A[i + 1] <- A[i]
            i <- i - 1
        A[i + 1] <- chiave

// --- Partizionamento di Quicksort ---
PARTITION(A, p, r)
    x <- A[r]
    i <- p - 1
    for j <- p to r - 1
        if A[j] <= x
            i <- i + 1
            SWAP(A, i, j)
    SWAP(A, i + 1, r)
    return i + 1

// --- Algoritmo Principale: Hybrid Quicksort ---
QUICKSORT(A, p, r)
    if (r - p + 1) > M
        // Se l'array è grande, usa Quicksort
        mid <- floor((p + r) / 2) 
        COMPSWAP(A, p, mid)       
        COMPSWAP(A, p, r)         
        COMPSWAP(A, mid, r)      
        SWAP(A, mid, r)

        q <- PARTITION(A, p, r) 

        QUICKSORT(A, p, q - 1)
        QUICKSORT(A, q + 1, r)
    else
        // Se l'array è piccolo, usa Insertion Sort
        INSERTION-SORT(A, p, r)
```

---

### **Esempio di Esecuzione Concettuale**:
Supponiamo di ordinare un array di 1000 elementi con `M = 10`.
1. **Inizio**: Si chiama `QUICKSORT(A, 1, 1000)`. La dimensione (1000) è maggiore di 10, quindi l'algoritmo parte in modalità **Quicksort**.
2. **Partizionamento normale**: Per molte iterazioni, Quicksort divide l'array in partizioni sempre più piccole usando la tecnica "median-of-three" per scegliere un buon pivot.
3. **Scenario di partizione piccola**: A un certo punto, una chiamata ricorsiva si trova a dover ordinare un sotto-array di 8 elementi. Poiché la sua dimensione è minore o uguale a `M`, la condizione `if` fallisce e viene eseguito il blocco `else`.
4. **Cambio di strategia**: Viene chiamato **Insertion Sort** per ordinare questo piccolo pezzo di 8 elementi. La ricorsione per questo ramo si ferma qui, evitando l'overhead di ulteriori chiamate a Quicksort.

---

### **Analisi dell'algoritmo**:
1. **Complessità temporale**:
   - **Caso migliore**: $O(n \log n)$ (performance di Quicksort).
   - **Caso peggiore**: **$O(n^2)$**. Questa ottimizzazione migliora la velocità media ma **non** previene il caso peggiore di Quicksort.
   - **Caso medio**: $O(n \log n)$ (con una costante di tempo inferiore rispetto a Quicksort puro).

2. **Complessità spaziale**:
   - $O(\log n)$: per lo stack ricorsivo.

---

### **Punti chiave sull'algoritmo**:
1. L'algoritmo è un'**ottimizzazione di performance** per il caso medio di Quicksort.
2. La combinazione dei due algoritmi sfrutta i punti di forza di ciascuno: la velocità di Quicksort su grandi dati e quella di Insertion Sort su piccoli dati.

---

### **Confronto con altri algoritmi**:
| **Caratteristica**      | **Hybrid Sort (QS + IS)** | **Quick Sort (Randomized)** | **Merge Sort**         |
|--------------------------|-----------------------------|-----------------------------|------------------------|
| **Caso Migliore**         | $O(n \log n)$             | $O(n \log n)$             | $O(n \log n)$        |
| **Caso Peggiore**         | **$O(n^2)$**              | $O(n^2)$ (improbabile)    | $O(n \log n)$        |
| **Spazio Aggiuntivo**     | $O(\log n)$                 | $O(\log n)$                 | $O(n)$               |
| **In-place**              | Sì                          | Sì                          | No                     |
| **Performance Pratica** | **Generalmente molto alta** | Molto alta                  | Leggermente più lenta  |
