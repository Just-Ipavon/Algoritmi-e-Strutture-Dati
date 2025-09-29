## **Insertion Sort**
### Descrizione:
- L'Insertion Sort ordina l'array dividendo l'array in una parte **ordinata** e una parte **non ordinata**.
- Per ogni elemento della parte non ordinata, lo inserisce nella posizione corretta all'interno della parte ordinata.

---

### **Invariante di ciclo**:
> Dopo la \(i\)-esima iterazione del ciclo esterno, i primi \(i+1\) elementi dell'array sono ordinati.

Questa proprietà guida tutto l'algoritmo.

---

### **Passi fondamentali**:
1.  **Inizializzazione**:
    -   All'inizio del ciclo, l'array è diviso in una parte ordinata (solo il primo elemento) e una non ordinata (tutti gli altri elementi).
    -   L'invariante è vera perché un singolo elemento è già ordinato per definizione.

2.  **Conservazione**:
    -   Per ogni elemento nella parte non ordinata, si trova la sua posizione corretta nella parte ordinata e lo si inserisce lì.
    -   L'invariante è preservata poiché la parte ordinata rimane sempre corretta.

3.  **Conclusione**:
    -   Alla fine del ciclo, tutti gli elementi sono stati inseriti nella posizione corretta e l'array è completamente ordinato.

---

### **Pseudocodice (secondo Cormen)**:

```cpp
INSERTION-SORT(A)
  for j <- 2 to A.length
      chiave <- A[j]
      // Inserisci A[j] nella sequenza ordinata A[1..j-1]
      i <- j - 1
      while i > 0 and A[i] > chiave
          A[i + 1] <- A[i]
          i <- i - 1
      A[i + 1] <- chiave
```

---

### **Esempio di Esecuzione**:
Supponiamo di ordinare l'array iniziale `{12, 11, 13, 5, 6}`.
1.  **Iterazione 1**:
    -   Chiave: \(11\), confronta con \(12\).
    -   Sposta \(12\) verso destra e inserisci \(11\).
    -   Array: `{11, 12, 13, 5, 6}`.
2.  **Iterazione 2**:
    -   Chiave: \(13\), nessuno spostamento.
    -   Array: `{11, 12, 13, 5, 6}`.
3.  **Iterazione 3**:
    -   Chiave: \(5\), sposta \(13, 12, 11\) verso destra.
    -   Inserisci \(5\).
    -   Array: `{5, 11, 12, 13, 6}`.
4.  **Iterazione 4**:
    -   Chiave: \(6\), sposta \(13, 12, 11\) verso destra.
    -   Inserisci \(6\).
    -   Array: `{5, 6, 11, 12, 13}`.

---

### **Analisi dell'algoritmo**:
1.  **Complessità temporale**:
    -   Caso migliore: \(O(n)\), quando l'array è già ordinato.
    -   Caso peggiore: \(O(n^2)\), quando l'array è ordinato al contrario.
    -   Caso medio: \(O(n^2)\).

2.  **Complessità spaziale**:
    -   \(O(1)\): utilizza solo memoria aggiuntiva costante.

---

### **Punti chiave sull'invariante**:
1.  Dopo ogni iterazione, la parte ordinata dell'array (i primi \(i+1\) elementi) è corretta.
2.  L'invariante garantisce che l'algoritmo produca un array ordinato alla fine.

---

### **Confronto con Bubble Sort**:
| **Caratteristica** | **Bubble Sort** | **Insertion Sort** |
| :--- | :--- | :--- |
| **Complessità Caso Medio** | \(O(n^2)\) | \(O(n^2)\) |
| **Complessità Caso Migliore** | \(O(n)\) | \(O(n)\) |
| **Efficienza su array ordinati** | Mediocre | Alta |
| **Stabilità** | Sì | Sì |
