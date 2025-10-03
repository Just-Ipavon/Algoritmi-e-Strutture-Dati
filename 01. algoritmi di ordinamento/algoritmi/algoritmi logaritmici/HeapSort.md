## **Heap Sort**
### Definizioni Preliminari: Alberi Binari
Prima di analizzare l'Heap Sort, è utile definire i tipi di alberi binari. Un **albero binario** è una struttura dati gerarchica in cui ogni nodo ha al massimo due figli (un figlio sinistro e un figlio destro).

- **Albero Binario Pieno (Full)**: Un albero in cui ogni nodo ha 0 o 2 figli.
- **Albero Binario Perfetto (Perfect)**: Un albero pieno in cui tutte le foglie (nodi senza figli) si trovano allo stesso livello.
- **Albero Binario Completo (Complete)**: Un albero in cui tutti i livelli, ad eccezione forse dell'ultimo, sono completamente riempiti e le foglie dell'ultimo livello sono allineate il più a sinistra possibile. **Una heap è implementata come un albero binario completo**, il che permette di rappresentarla efficientemente tramite un array.

### Descrizione:
**Heap Sort** è un algoritmo di ordinamento basato su una **heap** (un albero binario completo), che può essere di tipo **max-heap** o **min-heap**. Nella versione più comune, viene utilizzata una **max-heap** per ordinare gli elementi in ordine crescente. Il funzionamento di Heap Sort si divide in due fasi principali:
1. **Costruzione della heap**: L'array viene trasformato in una max-heap.
2. **Estrazione degli elementi**: L'elemento massimo (la radice della heap) viene estratto e scambiato con l'ultimo elemento dell'array. La dimensione della heap viene ridotta di uno e la sua struttura viene ripristinata.

Questo processo viene ripetuto fino a quando tutti gli elementi sono stati ordinati.

![esempio heap](../../assets/Heap_sort_example.gif)
---

### **Invariante di ciclo**:
> All'inizio di ogni iterazione del ciclo di ordinamento (dopo la costruzione iniziale), i primi `i` elementi dell'array `A[1..i]` formano una max-heap valida, e gli elementi in `A[i+1..n]` costituiscono la parte già ordinata dell'array.

---

### **Passi Fondamentali**:
1. **Inizializzazione**:
   - Trasforma l'array disordinato in una **max-heap** usando la procedura `BUILD-MAX-HEAP`. In una max-heap, ogni nodo genitore è maggiore o uguale ai suoi figli.

2. **Conservazione**:
   - Scambia il massimo elemento (`A[1]`) con l'ultimo elemento della heap (`A[i]`).
   - Riduci la dimensione della heap (`A.heap-size`) e richiama `MAX-HEAPIFY` sulla radice per ripristinare la proprietà di max-heap.

3. **Conclusione**:
   - L'algoritmo termina quando la heap contiene un solo elemento. L'array `A` è ora completamente ordinato.

---

### **Pseudocodice (Stile Cormen)**:
*Nota: Lo stile Cormen usa array con indicizzazione a base 1. Le funzioni `PARENT(i)`, `LEFT(i)` e `RIGHT(i)` calcolano gli indici del genitore e dei figli.*

```cpp
// Ripristina la proprietà di max-heap per il sottoalbero radicato in i
// Assumiamo che i sottoalberi sinistro e destro di i siano già max-heap.
MAX-HEAPIFY(A, i)
    l <- LEFT(i)      // Indice figlio sinistro (2*i)
    r <- RIGHT(i)     // Indice figlio destro (2*i + 1)
    
    // Trova il più grande tra il nodo i, il figlio sinistro e il figlio destro
    if l <= A.heap-size and A[l] > A[i]
        largest <- l
    else
        largest <- i
    if r <= A.heap-size and A[r] > A[largest]
        largest <- r
    
    // Se il più grande non è il nodo corrente, scambiali e continua ricorsivamente
    if largest != i
        exchange A[i] with A[largest]
        MAX-HEAPIFY(A, largest)

// Costruisce una max-heap a partire da un array disordinato
BUILD-MAX-HEAP(A)
    A.heap-size <- A.length
    for i <- floor(A.length / 2) downto 1
        MAX-HEAPIFY(A, i)

// Funzione principale di Heap Sort
HEAPSORT(A)
    BUILD-MAX-HEAP(A)
    for i <- A.length downto 2
        // Sposta la radice (massimo) alla fine
        exchange A[1] with A[i]
        // Riduci la dimensione della heap
        A.heap-size <- A.heap-size - 1
        // Ripristina la proprietà di max-heap
        MAX-HEAPIFY(A, 1)
```

---

### **Esempio di Esecuzione**:
Supponiamo di ordinare `{12, 11, 13, 5, 6, 7}` con Heap Sort:
1. **Costruzione della heap (`BUILD-MAX-HEAP`)**:
   - L'array viene trasformato in una max-heap. A livello concettuale, l'array diventa `{13, 12, 7, 5, 6, 11}`.
2. **Estrazione e scambio (`HEAPSORT` loop)**:
   - Scambia la radice `13` (`A[1]`) con l'ultimo elemento `11` (`A[6]`). L'array diventa `{11, 12, 7, 5, 6, 13}`. La dimensione della heap diventa 5.
   - Chiama `MAX-HEAPIFY(A, 1)` per ripristinare la heap. L'array diventa `{12, 11, 7, 5, 6, 13}`.
   - Ripeti il processo: scambia `12` con `6`, riduci la heap, e così via.

L'array finale ordinato sarà: `{5, 6, 7, 11, 12, 13}`.

---

### **Analisi dell'algoritmo**:
1. **Complessità temporale**:
   - **Caso migliore, peggiore e medio**: $O(n \log n)$. La costruzione della heap (`BUILD-MAX-HEAP`) costa $O(n)$, mentre il ciclo di ordinamento esegue `n-1` chiamate a `MAX-HEAPIFY`, ciascuna con un costo di $O(\log n)$.
   
2. **Complessità spaziale**:
   - $O(1)$. Heap Sort è un algoritmo **in-place**, quindi non richiede spazio aggiuntivo proporzionale alla dimensione dell'input.

---

### **Heap Sort con Max-Heap e Min-Heap**

La differenza principale tra le due strutture è:
- **Max-Heap**: Ogni nodo è maggiore o uguale ai suoi figli. Permette di estrarre l'elemento **massimo** in tempo $O(1)$ (dopo la costruzione).
- **Min-Heap**: Ogni nodo è minore o uguale ai suoi figli. Permette di estrarre l'elemento **minimo** in tempo $O(1)$.

#### **1. Max-Heap (Ordinamento Crescente)**
L'uso di una Max-Heap è lo standard per ordinare un array in **ordine crescente**. Come visto sopra, si estrae ripetutamente l'elemento massimo e lo si sposta alla fine dell'array.

---

#### **Pseudocodice Max-Heap**:
Lo pseudocodice per `MAX-HEAPIFY`, `BUILD-MAX-HEAP` e `HEAPSORT` è quello già mostrato nella sezione principale.

---

#### **2. Min-Heap (Ordinamento Decrescente)**
Se si desidera ordinare un array in **ordine decrescente**, si può usare una Min-Heap. Il processo è simmetrico: si costruisce una Min-Heap, poi si estrae ripetutamente l'elemento minimo (`A[1]`) e lo si sposta alla fine della porzione di array considerata.

---

#### **Pseudocodice Min-Heap**:

```cpp
// Ripristina la proprietà di min-heap per il sottoalbero radicato in i
MIN-HEAPIFY(A, i)
    l <- LEFT(i)
    r <- RIGHT(i)
    
    // Trova il più piccolo tra il nodo i, il figlio sinistro e il figlio destro
    if l <= A.heap-size and A[l] < A[i]
        smallest <- l
    else
        smallest <- i
    if r <= A.heap-size and A[r] < A[smallest]
        smallest <- r
    
    // Se il più piccolo non è il nodo corrente, scambiali e continua
    if smallest != i
        exchange A[i] with A[smallest]
        MIN-HEAPIFY(A, smallest)

// Costruisce una min-heap a partire da un array disordinato
BUILD-MIN-HEAP(A)
    A.heap-size <- A.length
    for i <- floor(A.length / 2) downto 1
        MIN-HEAPIFY(A, i)

// Funzione di ordinamento (decrescente) usando Min-Heap
HEAPSORT-MIN(A)
    BUILD-MIN-HEAP(A)
    for i <- A.length downto 2
        exchange A[1] with A[i]
        A.heap-size <- A.heap-size - 1
        MIN-HEAPIFY(A, 1)
```

---

#### **Esempio di Esecuzione (Min-Heap)**:
Supponiamo di ordinare `{12, 11, 13, 5, 6, 7}` con una Min-Heap:

1. **Costruzione della Min-Heap**: L'array diventa `{5, 6, 7, 12, 11, 13}`.
2. **Estrazione e scambio**: Scambia la radice `5` con l'ultimo elemento `13`. L'array diventa `{13, 6, 7, 12, 11, 5}`. Riduci la heap e ripristina con `MIN-HEAPIFY`.

L'array finale ordinato sarà: `{13, 12, 11, 7, 6, 5}` (ordinato in ordine decrescente).

---

### **Conclusione**:
- **Max-Heap** è la scelta standard per l'ordinamento **crescente**.
- **Min-Heap** è la scelta standard per l'ordinamento **decrescente**.

Entrambi gli approcci garantiscono una complessità temporale di $O(n \log n)$ e una complessità spaziale di $O(1)$.