## **Alberi Binari di Ricerca (ABR)**
### Descrizione:
Un **Albero Binario di Ricerca** (ABR), o *Binary Search Tree* (BST), è una struttura dati basata su nodi in un albero binario, in cui ogni nodo ha al massimo due figli. La sua caratteristica fondamentale è che i dati sono organizzati in modo da permettere operazioni di ricerca, inserimento e cancellazione molto efficienti (in media).

La struttura è definita ricorsivamente e si basa su una semplice ma potente proprietà che governa la posizione di ogni chiave all'interno dell'albero.

---

### **Nomenclatura e Struttura del Nodo**
- **Nodo (Node)**: L'elemento base di un albero. Un nodo `x` ha i seguenti attributi:
    - `x.key`: La chiave (il valore) del nodo.
    - `x.p`: Un puntatore al **genitore**.
    - `x.left`: Un puntatore al **figlio sinistro**.
    - `x.right`: Un puntatore al **figlio destro**.
- **Radice (Root)**: L'unico nodo `x` dell'albero per cui `x.p == NIL`.
- **Foglia (Leaf)**: Un nodo i cui figli sono `NIL`.
- **NIL**: Un valore sentinella che rappresenta un puntatore nullo.
- **Altezza (Height)** di un albero: La lunghezza del percorso più lungo dalla radice a una foglia.

---

### **Proprietà Fondamentale dell'ABR**
Per ogni nodo `x` in un Albero Binario di Ricerca, vale la seguente proprietà:
> Se `y` è un nodo nel sottoalbero sinistro di `x`, allora `y.key ≤ x.key`.
> Se `y` è un nodo nel sottoalbero destro di `x`, allora `y.key ≥ x.key`.

Questa proprietà garantisce che un **attraversamento simmetrico** (in-order) dell'albero restituisca le chiavi in ordine crescente.

---

### **Operazioni sugli ABR**
Tutte le operazioni fondamentali hanno una complessità temporale proporzionale all'altezza dell'albero, `h`.

#### **1. Ricerca (Search)**
**Descrizione**: Cerca una chiave `k` partendo da un nodo `x`. A ogni passo, confronta `k` con la chiave del nodo corrente e decide se continuare nel sottoalbero sinistro (se `k` è più piccolo) o destro (se `k` è più grande), fino a trovare la chiave o a raggiungere un punto nullo (`NIL`).
**Complessità**: `O(h)`.

**Pseudocodice (Ricorsivo)**
```cpp
TREE-SEARCH(x, k)
    if x == NIL or k == x.key
        return x
    if k < x.key
        return TREE-SEARCH(x.left, k)
    else
        return TREE-SEARCH(x.right, k)
```

#### **2. Minimo e Massimo**
**Descrizione**: Per trovare il **minimo**, si parte da un nodo `x` e si segue il percorso più a sinistra possibile fino a raggiungere un nodo senza figlio sinistro. Per il **massimo**, si segue il percorso più a destra.
**Complessità**: `O(h)`.

**Pseudocodice (Minimo)**
```cpp
TREE-MINIMUM(x)
    while x.left != NIL
        x <- x.left
    return x
```

**Pseudocodice (Massimo)**
```cpp
TREE-MAXIMUM(x)
    while x.right != NIL
        x <- x.right
    return x
```

#### **3. Successore e Predecessore**
**Descrizione**:
- Il **Successore** di un nodo `x` è il nodo con la chiave più piccola tra tutte quelle maggiori di `x.key`.
- Il **Predecessore** di un nodo `x` è il nodo con la chiave più grande tra tutte quelle minori di `x.key`.

**Complessità**: `O(h)`.

**Pseudocodice (Successore)**
```cpp
TREE-SUCCESSOR(x)
    // Caso 1: Se esiste un sottoalbero destro, il successore è il minimo di quel sottoalbero.
    if x.right != NIL
        return TREE-MINIMUM(x.right)
    
    // Caso 2: Altrimenti, il successore è il primo antenato di x
    // il cui figlio sinistro è anche un antenato di x.
    y <- x.p
    while y != NIL and x == y.right
        x <- y
        y <- y.p
    return y
```

**Pseudocodice (Predecessore)**

```cpp
TREE-PREDECESSOR(x)
    // Caso 1: Se esiste un sottoalbero sinistro, il predecessore è il massimo di quel sottoalbero.
    if x.left != NIL
        return TREE-MAXIMUM(x.left)
        
    // Caso 2: Altrimenti, è il primo antenato di x che è anche un discendente destro.
    y <- x.p
    while y != NIL and x == y.left
        x <- y
        y <- y.p
    return y
```

#### **4. Inserimento (Insertion)**
**Descrizione**: Per inserire un nuovo nodo `z`, si cerca la sua posizione corretta scendendo nell'albero come in una `TREE-SEARCH`. Quando si raggiunge un puntatore `NIL`, si inserisce `z` in quella posizione, mantenendo i collegamenti con il genitore.
**Complessità**: `O(h)`.

**Pseudocodice**
```cpp
TREE-INSERT(T, z)
    y <- NIL
    x <- T.root
    while x != NIL
        y <- x
        if z.key < x.key
            x <- x.left
        else
            x <- x.right
    z.p <- y
    if y == NIL
        T.root <- z       // L'albero era vuoto
    else if z.key < y.key
        y.left <- z
    else
        y.right <- z
```

#### **5. Cancellazione (Deletion)**
**Descrizione**: Rimuove un nodo `z` dall'albero, gestendo tre casi principali per preservare la proprietà dell'ABR.
**Complessità**: `O(h)`.

**Casi di Cancellazione**:
1.  **`z` non ha figli (è una foglia)**: Si rimuove semplicemente il nodo, impostando a `NIL` il puntatore del genitore verso `z`.
2.  **`z` ha un solo figlio**: Si "scavalca" `z`, collegando direttamente il genitore di `z` con l'unico figlio di `z`.
3.  **`z` ha due figli**: Questo è il caso più complesso. Si trova il **successore** di `z` (chiamiamolo `y`), che per definizione non ha figlio sinistro. Si sostituisce `z` con `y`. Il successore `y` viene spostato al posto di `z`, e il figlio destro originale di `y` prende il posto di `y`.

**Pseudocodice (con funzione di supporto `TRANSPLANT`)**
```cpp
// Sostituisce il sottoalbero radicato in u con quello radicato in v
TRANSPLANT(T, u, v)
    if u.p == NIL
        T.root <- v
    else if u == u.p.left
        u.p.left <- v
    else
        u.p.right <- v
    if v != NIL
        v.p <- u.p

// Funzione principale per la cancellazione
TREE-DELETE(T, z)
    if z.left == NIL      // Gestisce il caso 1 (se anche z.right è NIL) e il caso 2
        TRANSPLANT(T, z, z.right)
    else if z.right == NIL // Gestisce il caso 2
        TRANSPLANT(T, z, z.left)
    else
        // Caso 3: z ha due figli
        y <- TREE-MINIMUM(z.right) // Trova il successore di z
        if y.p != z
            TRANSPLANT(T, y, y.right)
            y.right <- z.right
            y.right.p <- y
        TRANSPLANT(T, z, y)
        y.left <- z.left
        y.left.p <- y
```

---

### **Attraversamento dell'Albero (Tree Traversal)**
**Descrizione**: Modi sistematici per visitare tutti i nodi di un albero. La complessità è sempre **`Θ(n)`** perché ogni nodo viene visitato una sola volta.

1.  **Visita Simmetrica (In-order)**: Sinistra -> Radice -> Destra. **Produce le chiavi in ordine crescente.**
    ```cpp
    INORDER-TREE-WALK(x)
        if x != NIL
            INORDER-TREE-WALK(x.left)
            print x.key
            INORDER-TREE-WALK(x.right)
    ```cpp
2.  **Visita Anticipata (Pre-order)**: Radice -> Sinistra -> Destra. Utile per creare una copia dell'albero.
    ```cpp
    PREORDER-TREE-WALK(x)
        if x != NIL
            print x.key
            PREORDER-TREE-WALK(x.left)
            PREORDER-TREE-WALK(x.right)
    ```
3.  **Visita Posticipata (Post-order)**: Sinistra -> Destra -> Radice. Utile per deallocare la memoria di un albero.
    ```cpp
    POSTORDER-TREE-WALK(x)
        if x != NIL
            POSTORDER-TREE-WALK(x.left)
            POSTORDER-TREE-WALK(x.right)
            print x.key
    ```

---

### **Analisi dell'Algoritmo**

1.  **Complessità Temporale**:
    - **Caso Migliore e Medio (Albero Bilanciato)**: L'altezza `h` è $O(\log n)$. Le operazioni sono molto veloci: **$O(\log n)$**.
    - **Caso Peggiore (Albero Degenerato)**: L'albero si comporta come una lista concatenata (es. inserendo elementi già ordinati). L'altezza `h` è $O(n)$. Le operazioni diventano lente: **$O(n)$**.

2.  **Complessità Spaziale**:
    - **$O(n)$** per memorizzare gli `n` nodi dell'albero.

---

### **Vantaggi e Svantaggi**

| Vantaggi | Svantaggi |
| :--- | :--- |
| Mantiene i dati sempre ordinati. | Le performance dipendono dal bilanciamento dell'albero. |
| Ricerca, inserimento e cancellazione efficienti in media ($O(\log n)$). | Il caso peggiore ($O(n)$) è inefficiente. |
| La visita simmetrica è molto efficiente. | Meno veloce di una Hash Table per la sola ricerca. |
| Flessibile, non richiede una dimensione predefinita. | L'implementazione della cancellazione è complessa. |

Per ovviare al problema del caso peggiore, sono state create varianti di ABR auto-bilancianti come gli **Alberi AVL** e gli **[Alberi Rosso-Neri](alberiRB.md)**, che garantiscono sempre un'altezza $O(\log n)$.