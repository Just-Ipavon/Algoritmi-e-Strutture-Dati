## **Heap Sort**
### Descrizione:
**Heap Sort** è un algoritmo di ordinamento basato su una **heap** (un albero binario completo), che può essere di tipo **max-heap** o **min-heap**. Nella versione più comune, viene utilizzata una **max-heap** per ordinare gli elementi in ordine crescente. Il funzionamento di Heap Sort si divide in due fasi principali:
1. **Costruzione della heap**: L'array viene trasformato in una max-heap.
2. **Estrazione degli elementi**: L'elemento massimo (la radice della heap) viene estratto e scambiato con l'ultimo elemento dell'array. L'array viene ridotto di uno e la heap viene ricostruita per ripristinare la proprietà di max-heap.

Questo processo viene ripetuto fino a quando tutti gli elementi sono stati ordinati.

---

### **Invariante di ciclo**:
> Dopo ogni estrazione della radice della heap, l'array contiene una parte ordinata (gli ultimi elementi) e il resto è una max-heap. L'invariante è che la proprietà di max-heap viene sempre mantenuta durante il processo di scambio e ricostruzione della heap.

---

### **Passi Fondamentali**:
1. **Inizializzazione**:
   - Trasforma l'array in una **max-heap**.
   - In una max-heap, ogni nodo ha un valore maggiore o uguale ai valori dei suoi figli.

2. **Conservazione**:
   - Scambia il massimo elemento (radice) con l'ultimo elemento non ordinato.
   - Riduci la dimensione dell'array e ricostruisci la heap per ripristinare la proprietà di max-heap.

3. **Conclusione**:
   - Alla fine, l'array sarà ordinato, con gli elementi estratti e messi nella parte finale dell'array.

---

### **Codice in C++**:

```cpp
#include <iostream>
using namespace std;

// Funzione per fare il "heapify" (ripristinare la proprietà di heap)
void heapify(int arr[], int n, int i) {
    int largest = i;    // Inizializza il più grande come radice
    int left = 2 * i + 1;  // Sinistro
    int right = 2 * i + 2; // Destro

    // Se il figlio sinistro è maggiore della radice
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    // Se il figlio destro è maggiore del più grande finora
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // Se il più grande non è la radice
    if (largest != i) {
        swap(arr[i], arr[largest]);  // Scambia i nodi

        // Ricorsivamente ripristina la proprietà di heap
        heapify(arr, n, largest);
    }
}

// Funzione principale di Heap Sort
void heapSort(int arr[], int n) {
    // Costruisce una max-heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    // Estrai gli elementi uno per uno dalla heap
    for (int i = n - 1; i >= 0; i--) {
        // Sposta l'elemento corrente (la radice) alla fine
        swap(arr[0], arr[i]);

        // Ripristina la proprietà di max-heap per la parte rimanente dell'array
        heapify(arr, i, 0);
    }
}

// Funzione principale per testare Heap Sort
int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Array originale: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    heapSort(arr, n);

    cout << "Array ordinato: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    return 0;
}
```

---

### **Esempio di Esecuzione**:
Supponiamo di ordinare `{12, 11, 13, 5, 6, 7}` con Heap Sort:
1. **Costruzione della heap**:
   - Trasformiamo l'array in una max-heap: `{13, 12, 7, 5, 6, 11}`.
2. **Estrazione e scambio**:
   - Scambia la radice \(13\) con l'ultimo elemento \(11\), quindi eseguiamo l'heapify: `{12, 11, 7, 5, 6, 13}`.
   - Ripeti l'operazione fino a che l'array è ordinato.

L'array finale ordinato sarà: `{5, 6, 7, 11, 12, 13}`.

---

### **Analisi dell'algoritmo**:
1. **Complessità temporale**:
   - **Caso migliore**: \(O(n  log n)\), poiché la costruzione della heap e ogni operazione di heapify richiedono \(O( log n)\) e l'ordinamento esegue \(n\) operazioni.
   - **Caso peggiore**: \(O(n  log n)\), poiché ogni chiamata di heapify avviene per ogni livello dell'albero e avviene \(n\) volte.
   - **Caso medio**: \(O(n  log n)\), anche se non è influenzato dal tipo di distribuzione degli elementi.
   
2. **Complessità spaziale**:
   - \(O(1)\), Heap Sort è un algoritmo in-place, quindi non richiede spazio aggiuntivo oltre all'array stesso.

---

### **Punti chiave sull'invariante**:
1. Dopo ogni estrazione della radice della heap, l'array è parzialmente ordinato, con gli ultimi elementi posti correttamente.
2. La proprietà di max-heap viene sempre ripristinata dopo ogni scambio.

---

### **Confronto con altri algoritmi**:
| **Caratteristica**      | **Heap Sort**            | **Quick Sort**           | **Merge Sort**            |
|--------------------------|--------------------------|--------------------------|---------------------------|
| **Caso Migliore**         | \(O(n  log n)\)          | \(O(n  log n)\)          | \(O(n  log n)\)           |
| **Caso Peggiore**         | \(O(n  log n)\)          | \(O(n^2)\)               | \(O(n  log n)\)           |
| **Spazio Aggiuntivo**     | \(O(1)\)                 | \(O( log n)\)            | \(O(n)\)                  |
| **Stabilità**             | No                       | No                       | Sì                        |

---

### **Heap Sort con Max-Heap e Min-Heap**

In questa versione, vediamo come funzionano **Max-Heap** e **Min-Heap** con Heap Sort. La differenza principale tra i due è che:
- **Max-Heap** è una struttura in cui ogni nodo è maggiore o uguale ai suoi figli, il che permette di estrarre l'elemento massimo.
- **Min-Heap** è una struttura in cui ogni nodo è minore o uguale ai suoi figli, il che permette di estrarre l'elemento minimo.

#### **1. Max-Heap**
Nella **Max-Heap**, l'elemento massimo si trova sempre alla radice. Heap Sort utilizza questa struttura per ordinare l'array in ordine crescente, estraendo gli elementi più grandi e spostandoli alla fine dell'array.

---

#### **Codice Max-Heap**:

```cpp
#include <iostream>
using namespace std;

// Funzione per fare il "heapify" (ripristinare la proprietà di heap) per Max-Heap
void maxHeapify(int arr[], int n, int i) {
    int largest = i;       // Inizializza il più grande come radice
    int left = 2 * i + 1;  // Figlio sinistro
    int right = 2 * i + 2; // Figlio destro

    // Se il figlio sinistro è maggiore della radice
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    // Se il figlio destro è maggiore del più grande finora
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // Se il più grande non è la radice
    if (largest != i) {
        swap(arr[i], arr[largest]);  // Scambia i nodi

        // Ricorsivamente ripristina la proprietà di heap
        maxHeapify(arr, n, largest);
    }
}

// Funzione principale di Heap Sort usando Max-Heap
void heapSortMax(int arr[], int n) {
    // Costruisce una Max-Heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        maxHeapify(arr, n, i);
    }

    // Estrai gli elementi uno per uno dalla Max-Heap
    for (int i = n - 1; i >= 0; i--) {
        // Sposta l'elemento corrente (la radice) alla fine
        swap(arr[0], arr[i]);

        // Ripristina la proprietà di Max-Heap per la parte rimanente dell'array
        maxHeapify(arr, i, 0);
    }
}

// Funzione principale per testare Heap Sort con Max-Heap
int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Array originale: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    heapSortMax(arr, n);

    cout << "Array ordinato (Max-Heap): ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    return 0;
}
```

---

#### **Esempio di Esecuzione (Max-Heap)**:

Supponiamo di ordinare l'array `{12, 11, 13, 5, 6, 7}` con **Max-Heap**:

1. **Costruzione della Max-Heap**:
   - Trasformiamo l'array in una Max-Heap: `{13, 12, 7, 5, 6, 11}`.
2. **Estrazione e scambio**:
   - Scambia la radice \(13\) con l'ultimo elemento \(11\), quindi eseguiamo `maxHeapify`: `{12, 11, 7, 5, 6, 13}`.
   - Ripeti il processo per tutti gli altri elementi finché l'array è ordinato.

L'array finale ordinato sarà: `{5, 6, 7, 11, 12, 13}`.

---

#### **2. Min-Heap**
Nella **Min-Heap**, l'elemento minimo si trova sempre alla radice. Heap Sort utilizza questa struttura per ordinare l'array in ordine decrescente, estraendo gli elementi più piccoli e spostandoli alla fine dell'array.

---

#### **Codice Min-Heap**:

```cpp
#include <iostream>
using namespace std;

// Funzione per fare il "heapify" (ripristinare la proprietà di heap) per Min-Heap
void minHeapify(int arr[], int n, int i) {
    int smallest = i;       // Inizializza il più piccolo come radice
    int left = 2 * i + 1;   // Figlio sinistro
    int right = 2 * i + 2;  // Figlio destro

    // Se il figlio sinistro è minore della radice
    if (left < n && arr[left] < arr[smallest]) {
        smallest = left;
    }

    // Se il figlio destro è minore del più piccolo finora
    if (right < n && arr[right] < arr[smallest]) {
        smallest = right;
    }

    // Se il più piccolo non è la radice
    if (smallest != i) {
        swap(arr[i], arr[smallest]);  // Scambia i nodi

        // Ricorsivamente ripristina la proprietà di heap
        minHeapify(arr, n, smallest);
    }
}

// Funzione principale di Heap Sort usando Min-Heap
void heapSortMin(int arr[], int n) {
    // Costruisce una Min-Heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        minHeapify(arr, n, i);
    }

    // Estrai gli elementi uno per uno dalla Min-Heap
    for (int i = n - 1; i >= 0; i--) {
        // Sposta l'elemento corrente (la radice) alla fine
        swap(arr[0], arr[i]);

        // Ripristina la proprietà di Min-Heap per la parte rimanente dell'array
        minHeapify(arr, i, 0);
    }
}

// Funzione principale per testare Heap Sort con Min-Heap
int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Array originale: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    heapSortMin(arr, n);

    cout << "Array ordinato (Min-Heap): ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    return 0;
}
```

---

#### **Esempio di Esecuzione (Min-Heap)**:

Supponiamo di ordinare l'array `{12, 11, 13, 5, 6, 7}` con **Min-Heap**:

1. **Costruzione della Min-Heap**:
   - Trasformiamo l'array in una Min-Heap: `{5, 6, 7, 12, 11, 13}`.
2. **Estrazione e scambio**:
   - Scambia la radice \(5\) con l'ultimo elemento \(13\), quindi eseguiamo `minHeapify`: `{6, 11, 7, 12, 13, 5}`.
   - Ripeti il processo per tutti gli altri elementi finché l'array è ordinato.

L'array finale ordinato sarà: `{13, 12, 11, 7, 6, 5}` (ordinato in ordine decrescente).

---

### **Conclusione**:
- **Max-Heap** è utile quando desideriamo ordinare in ordine crescente, poiché possiamo sempre estrarre l'elemento massimo.
- **Min-Heap** è utile quando desideriamo ordinare in ordine decrescente, poiché possiamo sempre estrarre l'elemento minimo.

Entrambi gli algoritmi hanno una **complessità temporale** di \(O(n  log n)\) e una **complessità spaziale** di \(O(1)\) se usiamo un algoritmo in-place.