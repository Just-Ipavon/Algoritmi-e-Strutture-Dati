### Introduzione alla Programmazione Greedy

La **programmazione greedy** (o tecnica golosa) è un paradigma algoritmico utilizzato per risolvere problemi di ottimizzazione. Si basa sul principio di effettuare scelte locali ottimali a ogni passo, con l'obiettivo di trovare una soluzione globale ottimale. Questo approccio è particolarmente efficace quando il problema soddisfa le seguenti proprietà:

- **Scelta Greedy (Greedy Choice Property)**: Una scelta locale ottimale porta sempre a una soluzione globale ottimale.
- **Sottostruttura Ottimale (Optimal Substructure)**: Una soluzione ottimale del problema può essere costruita a partire da soluzioni ottimali dei suoi sottoproblemi.

Di seguito vengono presentati alcuni algoritmi fondamentali basati sulla programmazione greedy.

---

## 1. Greedy Activity Selector

L'**activity selector** è un problema in cui, dato un insieme di attività con tempi di inizio e fine, l'obiettivo è selezionare il numero massimo di attività che non si sovrappongono.

### Problema
- **Input**: Un insieme di \( n \) attività, ciascuna caratterizzata da un tempo di inizio \( s[i] \) e un tempo di fine \( f[i] \), dove \( s[i] < f[i] \).
- **Output**: Il numero massimo di attività che possono essere eseguite senza sovrapposizioni.

### Complessità
- Ordinamento iniziale: \( O(n log n) \)
- Selezione delle attività: \( O(n) \)
- Complessità totale: \( O(n log n) \), dove \( n \) è il numero di attività.

---

## 2. Codifica di Huffman

La **codifica di Huffman** è un algoritmo greedy per la compressione dati senza perdita. L'obiettivo è ridurre la lunghezza media del codice utilizzando lunghezze di codice variabili basate sulla frequenza dei simboli.

### Problema
- **Input**: Un insieme di simboli con frequenze associate.
- **Output**: Un albero di codifica binario che minimizza la lunghezza totale del codice.

### Complessità
- Costruzione dell'heap: \( O(n log n) \)
- Costruzione dell'albero: \( O(n log n) \)
- Complessità totale: \( O(n log n) \), dove \( n \) è il numero di simboli.

---

## 3. Zaino 0/1 (Knapsack Problem)

Nel **problema dello zaino 0/1**, si vuole massimizzare il valore totale degli oggetti inseriti in uno zaino con una capacità massima, senza poter dividere gli oggetti.

### Problema
- **Input**: \( n \) oggetti, ciascuno con un valore \( v[i] \) e un peso \( w[i] \), e una capacità massima \( W \).
- **Output**: Il valore massimo che può essere ottenuto riempiendo lo zaino.

### Metodo Greedy (Fallimento)
- Selezionare gli oggetti con il rapporto \( v[i]/w[i] \) più alto. Questo approccio non garantisce una soluzione ottimale per il problema 0/1.

### Complessità
- Ordinamento per rapporto valore/peso: \( O(n log n) \)
- Complessità totale: \( O(n \log n) \), dove \( n \) è il numero di oggetti.

---

## 4. Zaino Frazionario (Fractional Knapsack)

Nel **problema dello zaino frazionario**, a differenza dello zaino 0/1, gli oggetti possono essere divisi, consentendo di prendere frazioni di essi.

### Problema
- **Input**: \( n \) oggetti con valore \( v[i] \) e peso \( w[i] \), e una capacità massima \( W \).
- **Output**: Il valore massimo che può essere ottenuto riempiendo lo zaino.

### Metodo Greedy
- Ordinare gli oggetti in base al rapporto \( v[i]/w[i] \).
- Riempire lo zaino partendo dall'oggetto con il rapporto maggiore.
- Fermarsi quando la capacità \( W \) è esaurita.

### Complessità
- Ordinamento per rapporto valore/peso: \( O(n log n) \)
- Iterazione sugli oggetti: \( O(n) \)
- Complessità totale: \( O(n log n) \), dove \( n \) è il numero di oggetti.

---