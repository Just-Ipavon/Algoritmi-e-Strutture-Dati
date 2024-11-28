## **Quick Sort**
### Descrizione:
- Il Quick Sort funziona scegliendo un **pivot** (un elemento dell'array) e poi **partizionando** l'array in due sotto-array:
  - Uno con elementi **minori o uguali al pivot**.
  - Uno con elementi **maggiori del pivot**.
- Si applica ricorsivamente il processo ai due sotto-array.

---

### **Invariante di ciclo**:
> Al termine di ogni passaggio di partizionamento, il pivot è nella sua posizione corretta nell'array ordinato, e tutti gli elementi a sinistra sono minori o uguali, mentre quelli a destra sono maggiori.

---

### **Passi Fondamentali**:
1. **Inizializzazione**:
   - Si sceglie un pivot (generalmente il primo elemento, l'ultimo, o uno casuale).
   - L'invariante è vera perché il pivot non ha ancora partizionato l'array.

2. **Conservazione**:
   - Durante il partizionamento, si riorganizzano gli elementi rispetto al pivot.
   - L'invariante è preservata perché il pivot viene collocato correttamente.

3. **Conclusione**:
   - Alla fine, l'array è ordinato poiché tutti i sotto-array sono stati processati ricorsivamente.

---

### **Codice in C++**:
Ecco l'implementazione completa di Quick Sort con una funzione di partizionamento.

```cpp
#include <iostream>
using namespace std;

// Funzione per partizionare l'array
int partizione(int arr[], int low, int high) {
    int pivot = arr[high]; // Pivot scelto come ultimo elemento
    int i = low - 1;       // Indice per gli elementi più piccoli

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++; // Incrementa l'indice degli elementi più piccoli
            swap(arr[i], arr[j]);
        }
    }
    // Posiziona il pivot nella sua posizione corretta
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Funzione ricorsiva Quick Sort
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        // Partizione: ottieni l'indice del pivot
        int pi = partizione(arr, low, high);

        // Ordina ricorsivamente le sottosezioni
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Funzione principale per testare Quick Sort
int main() {
    int arr[] = {10, 80, 30, 90, 40, 50, 70};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Array originale: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    quickSort(arr, 0, n - 1);

    cout << "Array ordinato: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    return 0;
}
```

---

### **Esempio di Esecuzione**:
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
   - Caso migliore: \(O(n  log n)\), quando il pivot divide l'array in parti uguali.
   - Caso peggiore: \(O(n^2)\), quando il pivot è il minimo o massimo elemento (divisione sbilanciata).
   - Caso medio: \(O(n  log n)\).

2. **Complessità spaziale**:
   - \(O( log n)\): per lo stack ricorsivo (nella versione in-place).
   - Non richiede array ausiliari.

---

### **Punti chiave sull'invariante**:
1. Dopo ogni partizionamento, il pivot è nella posizione corretta.
2. Gli elementi a sinistra sono sempre minori o uguali al pivot, quelli a destra sempre maggiori.

---

### **Confronto con altri algoritmi**:
| **Caratteristica**      | **Quick Sort**          | **Merge Sort**         | **Insertion Sort**    |
|--------------------------|-------------------------|-------------------------|-----------------------|
| **Caso Migliore**         | \(O(n  log n)\)        | \(O(n  log n)\)        | \(O(n)\)             |
| **Caso Peggiore**         | \(O(n^2)\)             | \(O(n  log n)\)        | \(O(n^2)\)           |
| **Spazio Aggiuntivo**     | \(O( log n)\)          | \(O(n)\)               | \(O(1)\)             |
| **Stabilità**             | No                     | Sì                     | Sì                   |

---