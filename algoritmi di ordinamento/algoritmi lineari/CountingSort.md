### **Counting Sort**

---

### **Descrizione**:
- **Counting Sort** è un algoritmo di ordinamento che funziona contando il numero di occorrenze di ogni valore nell'array. Utilizza una "tabella di conteggio" per determinare la posizione finale di ciascun elemento nell'array ordinato. È un algoritmo non comparativo, quindi non confronta direttamente gli elementi.
  
- **Applicabilità**:
  - È particolarmente utile quando i valori nell'array sono limitati e ben definiti, come numeri interi in un intervallo ristretto.
  
- **Limitazioni**:
  - **Counting Sort** è adatto solo per valori numerici discreti o simboli con un numero finito di possibili valori.

---

### **Invariante di ciclo**:
> Dopo ogni passaggio, la tabella di conteggio tiene traccia della posizione corretta per ogni elemento, e alla fine gli elementi sono distribuiti nell'array finale secondo le loro frequenze.

---

### **Passi Fondamentali**:
1. **Inizializzazione**:
   - Si crea una tabella di conteggio, dove ogni indice rappresenta un valore possibile dell'array.
   
2. **Conteggio delle occorrenze**:
   - Ogni elemento dell'array viene utilizzato per incrementare il valore corrispondente nella tabella di conteggio.

3. **Calcolo delle posizioni cumulative**:
   - Si calcola il numero cumulativo di occorrenze in modo che ogni indice della tabella contenga la posizione finale di un elemento nell'array ordinato.

4. **Costruzione dell'array ordinato**:
   - Ogni elemento viene posizionato nell'array finale usando la tabella di conteggio, riducendo il valore di contatore ad ogni inserimento.

---

### **Codice in C++**:
Ecco l'implementazione di **Counting Sort** per un array di numeri interi.

```cpp
#include <iostream>
#include <vector>
using namespace std;

// Funzione per eseguire Counting Sort
void countingSort(vector<int>& arr) {
    if (arr.empty()) return;

    // Trova il valore massimo nell'array
    int maxVal = *max_element(arr.begin(), arr.end());

    // Crea la tabella di conteggio
    vector<int> count(maxVal + 1, 0);

    // Conta le occorrenze di ogni numero nell'array
    for (int i = 0; i < arr.size(); i++) {
        count[arr[i]]++;
    }

    // Modifica la tabella di conteggio per essere cumulativa
    for (int i = 1; i <= maxVal; i++) {
        count[i] += count[i - 1];
    }

    // Costruisci l'array ordinato
    vector<int> output(arr.size());
    for (int i = arr.size() - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    // Copia l'array ordinato nell'array originale
    for (int i = 0; i < arr.size(); i++) {
        arr[i] = output[i];
    }
}

// Funzione principale per testare Counting Sort
int main() {
    vector<int> arr = {10, 80, 30, 90, 40, 50, 70};

    cout << "Array originale: ";
    for (int i : arr) cout << i << " ";
    cout << endl;

    countingSort(arr);

    cout << "Array ordinato: ";
    for (int i : arr) cout << i << " ";
    cout << endl;

    return 0;
}
```

---

### **Esempio di Esecuzione**:
Supponiamo di ordinare l'array `{10, 80, 30, 90, 40, 50, 70}`:

1. **Passaggio 1: Conteggio delle occorrenze**:
   - La tabella di conteggio per l'array sarà:
     ```
     [0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
     ```
     Dove ogni indice rappresenta il numero di occorrenze di quel valore nell'array.

2. **Passaggio 2: Calcolo delle posizioni cumulative**:
   - La tabella di conteggio cumulativo sarà:
     ```
     [0, 0, 0, 0, 1, 2, 2, 3, 4, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6]
     ```

3. **Passaggio 3: Costruzione dell'array ordinato**:
   - L'array ordinato finale è: `{10, 30, 40, 50, 70, 80, 90}`.

---

### **Analisi dell'Algoritmo**:

1. **Complessità Temporale**:
   - **Caso Migliore**: \(O(n + k)\), dove \(n\) è il numero di elementi e \(k\) è il range di valori nell'array (ad esempio, \(max(arr) - min(arr)\)).
   - **Caso Peggiore**: \(O(n + k)\), poiché il tempo è influenzato solo dalla dimensione dell'array e dalla gamma di valori.
   - **Caso Medio**: \(O(n + k)\), in quanto non dipende dalla distribuzione degli elementi.

2. **Complessità Spaziale**:
   - \(O(n + k)\), dove \(n\) è la lunghezza dell'array e \(k\) è il range di valori possibili.

---

### **Punti Chiave**:
- **Contare le occorrenze**: Per ogni elemento dell'array, viene incrementato il valore corrispondente nella tabella di conteggio.
- **Posizioni cumulative**: La tabella di conteggio viene modificata per rappresentare le posizioni finali degli elementi nell'array ordinato.
- **Stabilità**: Counting Sort è stabile, poiché mantiene l'ordine relativo degli elementi con lo stesso valore.

---

### **Confronto con altri algoritmi**:

| **Caratteristica**      | **Counting Sort**         | **Quick Sort**         | **Merge Sort**         |
|--------------------------|---------------------------|------------------------|------------------------|
| **Complessità Tempo (Medio)** | \(O(n + k)\)              | \(O(n  log n)\)         | \(O(n  log n)\)         |
| **Complessità Tempo (Peggiore)** | \(O(n + k)\)              | \(O(n^2)\)              | \(O(n  log n)\)         |
| **Complessità Spaziale** | \(O(n + k)\)               | \(O( log n)\)           | \(O(n)\)                |
| **Stabilità**            | Sì                        | No                     | Sì                     |