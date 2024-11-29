# Capitolo: Notazioni Asintotiche e Algoritmi di Ordinamento

## **1. Notazioni Asintotiche**

Le **notazioni asintotiche** vengono utilizzate per esprimere la complessità di un algoritmo in relazione alla dimensione dell'input, specialmente per grandi valori di `n`. Le principali notazioni sono:

### 1.1 **Notazione Big O (O)**
La notazione **Big O** descrive il limite superiore del tempo di esecuzione di un algoritmo, ossia il comportamento peggiore possibile.

- **Complessità Temporale**: Rappresenta il tempo che un algoritmo impiega in relazione alla dimensione dell'input.
- **Complessità Spaziale**: Rappresenta la quantità di memoria richiesta da un algoritmo.

### 1.2 **Notazione Omega (Ω)**
La notazione **Omega** fornisce il limite inferiore del tempo di esecuzione, ossia il miglior caso possibile.

### 1.3 **Notazione Theta (Θ)**
La notazione **Theta** descrive la complessità esatta, sia nel caso peggiore che in quello migliore.

---

## **2. Algoritmi di Ordinamento**

Gli algoritmi di ordinamento sono tecniche utilizzate per riordinare gli elementi di un array o lista in ordine crescente o decrescente. Di seguito, una panoramica dei principali algoritmi di ordinamento:

### 2.1 **Bubble Sort**
Il **Bubble Sort** è un algoritmo semplice che ordina confrontando elementi adiacenti e scambiandoli se sono nell'ordine sbagliato. Questo processo viene ripetuto fino a che l'array è ordinato.

- **Complessità Temporale**:
  - Caso peggiore: `O(n^2)`
  - Caso medio: `O(n^2)`
  - Caso migliore: `O(n)` (quando l'array è già ordinato)
- **Complessità Spaziale**: `O(1)` (in-place)

### 2.2 **Insertion Sort**
L'**Insertion Sort** è un algoritmo che costruisce gradualmente l'array ordinato spostando un elemento alla volta nella posizione corretta, partendo da un array parzialmente ordinato.

- **Complessità Temporale**:  
  - Caso peggiore: `O(n^2)` (quando l'array è ordinato in ordine inverso)  
  - Caso medio: `O(n^2)`  
  - Caso migliore: `O(n)` (quando l'array è già ordinato)  
- **Complessità Spaziale**: `O(1)` (in-place)  



### 2.3 **Quick Sort**
Il **Quick Sort** è un algoritmo basato sul paradigma "divide et impera". Sceglie un elemento come pivot e partiziona l'array in due sotto-array, uno con gli elementi minori del pivot e l'altro con gli elementi maggiori, ordinando ricorsivamente i sotto-array.

- **Complessità Temporale**:
  - Caso peggiore: `O(n^2)` (quando il pivot è sempre l'elemento più grande o più piccolo)
  - Caso medio: `O(n log n)`
  - Caso migliore: `O(n log n)`
- **Complessità Spaziale**: `O(log n)` per lo stack ricorsivo

### 2.4 **Merge Sort**
Il **Merge Sort** è un algoritmo "divide et impera" che divide l'array in due metà, le ordina ricorsivamente e poi le unisce in ordine crescente.

- **Complessità Temporale**:
  - Caso peggiore: `O(n log n)`
  - Caso medio: `O(n log n)`
  - Caso migliore: `O(n log n)`
- **Complessità Spaziale**: `O(n)` (richiede spazio aggiuntivo per l'unione degli array)

### 2.5 **Heap Sort**
Il **Heap Sort** è un algoritmo basato su una struttura dati chiamata **heap**, che è una rappresentazione parziale di un albero binario. L'algoritmo costruisce un heap massimo o minimo, e successivamente estrae ripetutamente l'elemento massimo o minimo per costruire l'array ordinato.

- **Complessità Temporale**:
  - Caso peggiore: `O(n log n)`
  - Caso medio: `O(n log n)`
  - Caso migliore: `O(n log n)`
- **Complessità Spaziale**: `O(1)` (in-place)

### 2.6 **Bucket Sort**
Il **Bucket Sort** è un algoritmo di ordinamento che distribuisce gli elementi dell'array in un numero di "secchi" (bucket), ordina ciascun secchio e quindi unisce i secchi per ottenere l'array ordinato. È utile quando gli elementi sono distribuiti uniformemente in un intervallo limitato.

- **Complessità Temporale**:
  - Caso peggiore: `O(n^2)` (quando ogni secchio contiene più di un elemento e l'ordinamento dei secchi richiede un algoritmo inefficiente)
  - Caso medio: `O(n + k)`, dove `k` è il numero di secchi
- **Complessità Spaziale**: `O(n + k)`

### 2.7 **Counting Sort**
Il **Counting Sort** è un algoritmo di ordinamento che conta il numero di occorrenze di ciascun valore nell'array e utilizza queste informazioni per posizionare ogni valore nella posizione corretta. È particolarmente efficiente quando gli elementi sono numeri interi con un intervallo limitato.

- **Complessità Temporale**:
  - Caso peggiore: `O(n + k)`, dove `k` è l'intervallo dei valori
  - Caso medio: `O(n + k)`
- **Complessità Spaziale**: `O(n + k)`

### 2.8 **Radix Sort**
Il **Radix Sort** è un algoritmo di ordinamento che ordina i numeri a partire dal loro meno significativo (digit) fino al più significativo. L'algoritmo utilizza un altro algoritmo di ordinamento stabile, come il Counting Sort, per ordinare i numeri basandosi sui singoli digit.

- **Complessità Temporale**:
  - Caso peggiore: `O(n * k)`, dove `n` è il numero di elementi e `k` è il numero di digit
  - Caso medio: `O(n * k)`
- **Complessità Spaziale**: `O(n + k)`

---
