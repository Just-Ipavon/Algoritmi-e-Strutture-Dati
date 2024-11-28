### **Radix Sort**

---

### **Descrizione**:
- **Radix Sort** è un algoritmo di ordinamento che ordina gli elementi considerando le loro cifre, a partire dalla meno significativa (LSD, Least Significant Digit) o dalla più significativa (MSD, Most Significant Digit). Funziona ordinando i numeri in base alle cifre in più passaggi, utilizzando un algoritmo di ordinamento stabile (tipicamente **Counting Sort**) per ogni passaggio.
  
- **Applicabilità**:
  - È particolarmente utile quando si ordina un gran numero di numeri interi o stringhe con una lunghezza fissa, e la dimensione dei numeri è relativamente piccola rispetto alla lunghezza dell'array.

---

### **Invariante di ciclo**:
> Dopo ogni passaggio, gli elementi sono ordinati secondo una cifra specifica e la posizione finale di ciascun elemento viene definita in modo incrementale, fino a che non vengono ordinati completamente.

---

### **Passi Fondamentali**:
1. **Inizializzazione**:
   - Si decide se ordinare dalla cifra più significativa o dalla meno significativa.
   
2. **Ordinamento per cifra**:
   - Si esegue un ordinamento stabile su ogni cifra (ad esempio, utilizzando **Counting Sort**).

3. **Ripetizione**:
   - Si ripete il processo per ciascuna cifra, da quella meno significativa a quella più significativa, o viceversa.

4. **Conclusione**:
   - Alla fine del processo, l'array è ordinato.

---

### **Codice in C++**:
Ecco l'implementazione di **Radix Sort** per numeri interi utilizzando **Counting Sort** per ordinare le cifre.

```cpp
#include <iostream>
#include <vector>
using namespace std;

// Funzione per eseguire Counting Sort sulla base di una cifra
void countingSortForRadix(vector<int>& arr, int exp) {
    int n = arr.size();
    vector<int> output(n);
    vector<int> count(10, 0);

    // Conteggio delle occorrenze delle cifre
    for (int i = 0; i < n; i++) {
        count[(arr[i] / exp) % 10]++;
    }

    // Calcola le posizioni cumulative
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // Costruzione dell'array ordinato
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // Copia l'array ordinato nell'array originale
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

// Funzione principale per eseguire Radix Sort
void radixSort(vector<int>& arr) {
    // Trova il numero massimo per determinare il numero di passaggi necessari
    int maxVal = *max_element(arr.begin(), arr.end());

    // Esegui Counting Sort per ogni cifra
    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        countingSortForRadix(arr, exp);
    }
}

// Funzione principale per testare Radix Sort
int main() {
    vector<int> arr = {170, 45, 75, 90, 802, 24, 2, 66};

    cout << "Array originale: ";
    for (int i : arr) cout << i << " ";
    cout << endl;

    radixSort(arr);

    cout << "Array ordinato: ";
    for (int i : arr) cout << i << " ";
    cout << endl;

    return 0;
}
```

---

### **Esempio di Esecuzione**:
Supponiamo di ordinare l'array `{170, 45, 75, 90, 802, 24, 2, 66}`:

1. **Passaggio 1 (ordinamento sulla prima cifra, unità)**:
   - Ordinamento dei numeri secondo la loro ultima cifra:
     ```
     [170, 90, 802, 2, 24, 45, 75, 66]
     ```
   
2. **Passaggio 2 (ordinamento sulla seconda cifra, decine)**:
   - Ordinamento dei numeri secondo la loro seconda cifra (decine):
     ```
     [802, 2, 24, 45, 66, 170, 75, 90]
     ```

3. **Passaggio 3 (ordinamento sulla terza cifra, centinaia)**:
   - Ordinamento dei numeri secondo la loro terza cifra (centinaia):
     ```
     [2, 24, 45, 66, 75, 90, 170, 802]
     ```

Alla fine, l'array è ordinato come `{2, 24, 45, 66, 75, 90, 170, 802}`.

---

### **Analisi dell'Algoritmo**:

1. **Complessità Temporale**:
   - **Caso Migliore**: \(O(n \cdot k)\), dove \(n\) è il numero di elementi e \(k\) è il numero di cifre (dipende dalla dimensione dei numeri).
   - **Caso Peggiore**: \(O(n \cdot k)\), poiché il tempo di esecuzione dipende dal numero di cifre e dal numero di elementi.
   - **Caso Medio**: \(O(n \cdot k)\).

2. **Complessità Spaziale**:
   - \(O(n + k)\), dove \(n\) è il numero di elementi e \(k\) è il numero di possibili valori per ciascuna cifra (solitamente 10, per le cifre decimali).

---

### **Punti Chiave**:
- **Stabilità**: Radix Sort è stabile, il che significa che mantiene l'ordine relativo degli elementi con lo stesso valore.
- **Efficienza**: È molto efficace per ordinare numeri con una lunghezza di cifra relativamente piccola rispetto alla dimensione dell'array.
- **Limitazioni**: Non è adatto per ordinare dati non numerici o con una gamma di valori molto ampia.

---

### **Confronto con altri algoritmi**:

| **Caratteristica**      | **Radix Sort**           | **Quick Sort**         | **Merge Sort**         |
|--------------------------|--------------------------|------------------------|------------------------|
| **Complessità Tempo (Medio)** | \(O(n \cdot k)\)         | \(O(n  log n)\)        | \(O(n  log n)\)        |
| **Complessità Tempo (Peggiore)** | \(O(n \cdot k)\)         | \(O(n^2)\)             | \(O(n  log n)\)        |
| **Complessità Spaziale** | \(O(n + k)\)             | \(O( log n)\)          | \(O(n)\)               |
| **Stabilità**            | Sì                       | No                     | Sì                     |