## **Bubble Sort**: Ordinamento Polinomiale
### Descrizione:
- **Bubble Sort** è un algoritmo semplice, di complessità temporale \(O(n^2)\) nel caso peggiore e medio. 
- Funziona confrontando coppie di elementi adiacenti in un array e scambiandoli se sono fuori ordine. Questo processo viene ripetuto fino a quando l'array è ordinato.

---

### **Invariante di ciclo**:
>Dopo \(i\) iterazioni del ciclo esterno, gli ultimi \(i\) elementi nell'array sono ordinati e non saranno più modificati.

---

### **Passi fondamentali**:
1. **Inizializzazione**:
   - Prima dell'inizio del ciclo, l'array potrebbe essere in qualsiasi ordine.
   - L'invariante è vera poiché nessun elemento è stato ancora confrontato.

2. **Conservazione**:
   - Durante ogni iterazione del ciclo interno, gli elementi più grandi "galleggiano" verso la fine dell'array.
   - L'invariante è preservata perché gli scambi avvengono solo se necessario.

3. **Conclusione**:
   - Dopo \(n-1\) iterazioni, l'intero array è ordinato. L'invariante garantisce che nessun ulteriore scambio sia necessario.

---

### **Codice in C++**:
```cpp
#include <iostream>
using namespace std;

// Funzione Bubble Sort
void bubbleSort(int arr[], int n) {
    // Ciclo esterno: numero di iterazioni
    for (int i = 0; i < n - 1; i++) {
        // Inizializzazione: nessuno scambio è avvenuto
        bool scambioEffettuato = false;

        // Ciclo interno: confronto coppie di elementi adiacenti
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Scambio se i valori sono fuori ordine
                swap(arr[j], arr[j + 1]);
                scambioEffettuato = true; // Scambio effettuato
            }
        }

        // Conservazione: interrompi se non ci sono stati scambi
        if (!scambioEffettuato) break;
    }
}

// Funzione principale per testare Bubble Sort
int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Array originale: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    bubbleSort(arr, n);

    cout << "Array ordinato: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    return 0;
}
```

---

### **Analisi dell'algoritmo**:
1. **Complessità temporale**:
   - Caso migliore: \(O(n)\), se l'array è già ordinato (grazie alla variabile `scambioEffettuato`).
   - Caso peggiore e medio: \(O(n^2)\), perché ogni coppia viene confrontata.

2. **Complessità spaziale**:
   - \(O(1)\): usa solo una quantità fissa di spazio aggiuntivo.

---

### **Esempio di Esecuzione**:
Con l'array iniziale `{64, 34, 25, 12, 22, 11, 90}`:
1. **Prima iterazione**:
   - Scambia \(64 \leftrightarrow 34\), \(64 \leftrightarrow 25\), ecc., fino a mettere \(90\) in fondo.
   - Array: `{34, 25, 12, 22, 11, 64, 90}`.
2. **Seconda iterazione**:
   - Scambia \(34 \leftrightarrow 25\), \(34 \leftrightarrow 12\), ecc., fino a mettere \(64\) in penultima posizione.
   - Array: `{25, 12, 22, 11, 34, 64, 90}`.
3. Continua fino all'array ordinato.

---

### **Punti chiave sull'invariante**:
1. Dopo ogni iterazione del ciclo esterno, gli ultimi \(i\) elementi sono ordinati.
2. La proprietà dell'array ordinato è preservata ad ogni passaggio.

---