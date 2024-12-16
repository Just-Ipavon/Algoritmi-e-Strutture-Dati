La programmazione dinamica (DP) è una tecnica algoritmica utilizzata per risolvere problemi complessi suddividendoli in sottoproblemi più semplici e risolvendo ciascuno di essi una sola volta.
È particolarmente efficace per problemi che presentano tre caratteristiche principali:

1. **Sottostruttura ottimale**: la soluzione ottima del problema contiene la soluzione ottima dei sottoproblemi.
2. **Sovrapposizione dei sottoproblemi**: I sottoproblemi si ripetono molte volte durante il calcolo, rendendo inefficiente il calcolo ripetitivo.
3. **Complessità polinomiale**: I sottoproblemi sono risolvibili in tempo polinomiale

## Principi Fondamentali

### 1. Memorizzazione
La DP utilizza una tabella (array, matrice, o struttura dati simile) per memorizzare i risultati dei sottoproblemi già risolti, evitando così di ricalcolarli.

### 2. Approccio Bottom-Up vs Top-Down
- **Bottom-Up**: Si costruisce la soluzione del problema partendo dai sottoproblemi più semplici, riempiendo gradualmente la tabella fino a raggiungere la soluzione desiderata.
- **Top-Down**: Utilizza la tecnica del memoization, risolvendo il problema principale ricorsivamente e memorizzando i risultati dei sottoproblemi.

## Struttura di un Problema di DP
1. **Definizione dei sottoproblemi**: Identificare come suddividere il problema principale in sottoproblemi.
2. **Relazione di ricorrenza**: Stabilire una formula che collega la soluzione di un problema ai suoi sottoproblemi.
3. **Caso base**: Definire i casi più semplici per cui la soluzione è nota.
4. **Costruzione della soluzione**: Implementare il procedimento (in modo iterativo o ricorsivo).

## Esempi Classici

### 1. Fibonacci
Un esempio semplice di DP è il calcolo della sequenza di Fibonacci:

- **Relazione di ricorrenza**: `F(n) = F(n-1) + F(n-2)`
- **Caso base**: `F(0) = 0`, `F(1) = 1`

### 2. LCS
La Longest Common String è la sottostringa di dimensione massima composta dai caratteri comuni, ovvero date due sequenze `X` e `Y`, `Z` è la **LCS** di `X` e `Y` se `Z ∈ CS ∧ ∄ W ∈ CS : |W| > |Z|` dove:
- **Z ∈ CS**: Z appartiene all'insieme delle sequenze comuni (CS) di X e Y. In altre parole, Z è una sottosequenza sia di X che di Y.
- **∄ W ∈ CS : ∣W∣ > ∣Z∣**: Non esiste alcuna altra sottosequenza comune (W) di X e Y che abbia lunghezza maggiore di Z.

### 3. Distanza di Editing
La distanza di editing è una misura che quantifica quanto due stringhe siano diverse tra loro, calcolando il numero minimo di operazioni necessarie per trasformarne una nell'altra. Esistono diverse varianti, tra cui:

- **Distanza di Hamming**:
  Misura il numero di posizioni in cui due stringhe di uguale lunghezza differiscono. È utile quando si confrontano stringhe della stessa dimensione, ad esempio nel campo della genetica o nella correzione di errori nei codici.

   - **Esempio**:  
      `X = "1011101", Y = "1001001"`
      Distanza di Hamming = 2 (le differenze sono nelle posizioni 2 e 4).

- **Distanza di Levenshtein**:
  Calcola il numero minimo di operazioni di inserimento, cancellazione e sostituzione necessarie per trasformare una stringa in un'altra. A differenza della distanza di Hamming, funziona anche con stringhe di lunghezza diversa.

   - **Esempio**:  
      `X = "kitten", Y = "sitting"`
      Distanza di Levenshtein = 3 (sostituire `k → s`, `e → i`, aggiungere `g`).

Ecco la versione corretta del testo originale per il Markdown di GitHub:

### 4. Prodotto di Sequenza di Matrici (Matrix Chain Order)

Il problema del **Matrix Chain Order** consiste nel determinare il modo ottimale di moltiplicare una sequenza di matrici per minimizzare il numero totale di operazioni scalari necessarie. La moltiplicazione non è commutativa, ma è associativa, quindi è possibile cambiare l'ordine delle parentesi.

- **Input**: Una sequenza di matrici `A1, A2, ..., An`, dove la matrice `Ai` ha dimensione `p[i-1] x p[i]`.
- **Output**: L'ordine ottimale di moltiplicazione che minimizza il costo computazionale.

- **Relazione di ricorrenza**:  
  Il costo minimo per moltiplicare le matrici da `Ai` a `Aj` è dato da:  
  ```
  m[i][j] = min(m[i][k] + m[k+1][j] + p[i-1] * p[k] * p[j])
  ```
  Dove `k` varia tra `i` e `j-1`.

- **Caso base**:  
  ```
  m[i][i] = 0
  ```
  poiché moltiplicare una singola matrice non ha costo.
  
### 5. Catena di Montaggio
Un altro esempio applicativo della DP è la **catena di montaggio** per trovare il percorso più veloce tra due linee di produzione. Ogni stazione di una linea ha un costo di elaborazione, e spostarsi da una linea all'altra comporta un costo di trasferimento.

- **Input**: Due linee con \( n \) stazioni ciascuna, costi di lavorazione per ogni stazione e costi di trasferimento tra le linee.
- **Relazione di ricorrenza**:  
  \[
  f_1[j] = \min(f_1[j-1] + a_1[j], f_2[j-1] + t_2[j] + a_1[j])
  \]
  \[
  f_2[j] = \min(f_2[j-1] + a_2[j], f_1[j-1] + t_1[j] + a_2[j])
  \]
  dove \( f_1[j] \) e \( f_2[j] \) rappresentano i costi cumulativi per arrivare alla \( j \)-esima stazione rispettivamente sulla prima e sulla seconda linea.

- **Caso base**: \( f_1[1] = e_1 + a_1[1], f_2[1] = e_2 + a_2[1] \), dove \( e_1, e_2 \) sono i costi di ingresso iniziali.

### 6. Memoization
La **memoization** è una tecnica per ottimizzare le chiamate ricorsive memorizzando i risultati dei sottoproblemi già calcolati in una struttura dati, spesso una tabella o un dizionario. Questo approccio riduce il numero di calcoli duplicati e migliora l'efficienza.

---

## Vantaggi della DP
- Riduce la complessità computazionale rispetto a metodi puramente ricorsivi.
- Consente di risolvere problemi che sarebbero altrimenti intrattabili con tecniche brute-force.

## Limiti
- Può richiedere molta memoria per memorizzare i risultati intermedi.
- Non applicabile se i sottoproblemi non si sovrappongono o se non esiste una sottostruttura ottimale.

---
