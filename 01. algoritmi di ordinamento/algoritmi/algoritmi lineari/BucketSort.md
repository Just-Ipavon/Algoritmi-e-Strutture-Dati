### **Bucket Sort**

---

### **Descrizione**:
- **Bucket Sort** è un algoritmo di ordinamento che distribuisce gli elementi in un numero di "bucket" (secchi). Ogni bucket contiene gli elementi che cadono in un determinato intervallo. Gli elementi all'interno di ciascun bucket vengono poi ordinati separatamente, tipicamente utilizzando un altro algoritmo come **insertion sort**. Infine, i bucket ordinati vengono concatenati insieme per ottenere l'array ordinato.
  
- **Applicabilità**:
  - È particolarmente utile quando gli elementi sono distribuiti uniformemente su un intervallo conosciuto.

---

### **Invariante di ciclo**:
> Dopo ogni passaggio, gli elementi di ciascun bucket sono ordinati internamente, e l'array finale rispecchia la concatenazione dei bucket ordinati.

---

### **Passi Fondamentali**:
1. **Inizializzazione**:
   - Si calcola il numero massimo e minimo dell'array per determinare l'intervallo dei bucket.
   - Si crea un array di bucket vuoti, ognuno corrispondente a un intervallo di valori.

2. **Conservazione**:
   - Ogni elemento dell'array viene assegnato a un bucket in base al suo valore.
   - Una volta che gli elementi sono distribuiti nei bucket, ogni bucket viene ordinato separatamente.

3. **Conclusione**:
   - Dopo che ogni bucket è stato ordinato, i risultati vengono concatenati per ottenere l'array finale ordinato.

---

### **Codice in C++**:

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Funzione per ordinare un bucket usando Insertion Sort
void insertionSort(vector<int>& bucket) {
    int n = bucket.size();
    for (int i = 1; i < n; i++) {
        int key = bucket[i];
        int j = i - 1;
        while (j >= 0 && bucket[j] > key) {
            bucket[j + 1] = bucket[j];
            j--;
        }
        bucket[j + 1] = key;
    }
}

// Funzione per Bucket Sort
void bucketSort(vector<int>& arr) {
    int n = arr.size();
    
    // Trova il valore massimo nell'array per determinare l'intervallo dei bucket
    int maxValue = *max_element(arr.begin(), arr.end());

    // Crea i bucket
    vector<vector<int>> buckets(maxValue + 1); // Array di vettori (bucket)

    // Distribuisci gli elementi nei bucket
    for (int i = 0; i < n; i++) {
        int index = arr[i];
        buckets[index].push_back(arr[i]);
    }

    // Ordina ogni bucket e concatenali
    arr.clear();
    for (int i = 0; i <= maxValue; i++) {
        if (!buckets[i].empty()) {
            insertionSort(buckets[i]); // Ordina il bucket con Insertion Sort
            arr.insert(arr.end(), buckets[i].begin(), buckets[i].end()); // Concatenazione dei bucket ordinati
        }
    }
}

// Funzione per testare Bucket Sort
int main() {
    vector<int> arr = {10, 80, 30, 90, 40, 50, 70};
    
    cout << "Array originale: ";
    for (int i : arr) cout << i << " ";
    cout << endl;

    bucketSort(arr);

    cout << "Array ordinato: ";
    for (int i : arr) cout << i << " ";
    cout << endl;

    return 0;
}
```

---

### **Esempio di Esecuzione**:
Supponiamo di ordinare l'array `{10, 80, 30, 90, 40, 50, 70}`:

1. **Passaggio 1: Distribuzione negli "bucket"**:
   - Gli elementi sono distribuiti nei rispettivi bucket:
     - Bucket 10: `{10}`
     - Bucket 30: `{30}`
     - Bucket 40: `{40}`
     - Bucket 50: `{50}`
     - Bucket 70: `{70}`
     - Bucket 80: `{80}`
     - Bucket 90: `{90}`

2. **Passaggio 2: Ordinamento dei bucket**:
   - Ogni bucket viene ordinato utilizzando **Insertion Sort** (nel caso di bucket singoli, non è necessario fare nulla):
     - Bucket 10: `{10}`
     - Bucket 30: `{30}`
     - Bucket 40: `{40}`
     - Bucket 50: `{50}`
     - Bucket 70: `{70}`
     - Bucket 80: `{80}`
     - Bucket 90: `{90}`

3. **Passaggio 3: Concatenazione dei bucket ordinati**:
   - L'array finale ottenuto dopo aver concatenato i bucket ordinati è: `{10, 30, 40, 50, 70, 80, 90}`.

---

### **Analisi dell'Algoritmo**:

1. **Complessità Temporale**:
   - **Caso Migliore**: \(O(n + k)\), dove \(n\) è il numero di elementi e \(k\) è il numero di bucket.
   - **Caso Peggiore**: \(O(n^2)\), se tutti gli elementi finiscono nello stesso bucket e vengono ordinati con un algoritmo \(O(n^2)\).
   - **Caso Medio**: \(O(n + k)\), se i bucket sono distribuiti uniformemente.

2. **Complessità Spaziale**:
   - \(O(n + k)\): per memorizzare gli array dei bucket.

---

### **Punti Chiave**:
- **Distribuzione nei bucket**: Ogni elemento viene distribuito in un bucket in base al suo valore.
- **Ordinamento dei bucket**: Ogni bucket viene ordinato separatamente (utilizzando un algoritmo come **Insertion Sort**).
- **Concatenazione**: Alla fine, i bucket vengono concatenati per ottenere l'array finale ordinato.

---

### **Confronto con altri algoritmi**:

| **Caratteristica**      | **Bucket Sort**           | **Quick Sort**         | **Merge Sort**         |
|--------------------------|---------------------------|------------------------|------------------------|
| **Complessità Tempo (Medio)** | \(O(n + k)\)               | \(O(n  log n)\)         | \(O(n  log n)\)         |
| **Complessità Tempo (Peggiore)** | \(O(n^2)\)               | \(O(n^2)\)              | \(O(n  log n)\)         |
| **Complessità Spaziale** | \(O(n + k)\)               | \(O( log n)\)           | \(O(n)\)                |
| **Stabilità**            | Sì                        | No                     | Sì                     |