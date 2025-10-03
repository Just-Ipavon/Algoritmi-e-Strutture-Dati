## **Alberi Rosso-Neri (Red-Black Trees)**
### Descrizione:
Un **Albero Rosso-Nero** (ARN), o *Red-Black Tree* (RBT), è un tipo di **Albero Binario di Ricerca auto-bilanciante**. Mantiene tutte le proprietà di un ABR, ma aggiunge un'ulteriore serie di vincoli, noti come "proprietà rosso-nere", per garantire che l'albero rimanga approssimativamente bilanciato durante le operazioni di inserimento e cancellazione.

Lo scopo principale di un albero rosso-nero è risolvere il problema del **caso peggiore** di un ABR standard. Impedendo la formazione di alberi degenerati (simili a liste concatenate), un ARN garantisce che l'altezza dell'albero sia sempre logaritmica rispetto al numero di nodi, `h = O(log n)`. Questo assicura che tutte le operazioni principali (ricerca, inserimento, cancellazione) abbiano una complessità garantita di `O(log n)` nel caso peggiore.

---

### **Proprietà Fondamentali (Invariant)**
Ogni nodo in un albero rosso-nero memorizza un bit extra che rappresenta il suo **colore** (rosso o nero). Per essere un albero rosso-nero valido, una struttura deve soddisfare le seguenti cinque proprietà in ogni momento:

1.  **Proprietà del Colore**: Ogni nodo è o **rosso** o **nero**.
2.  **Proprietà della Radice**: La radice dell'albero è sempre **nera**.
3.  **Proprietà delle Foglie**: Ogni foglia (rappresentata da `NIL`) è **nera**.
4.  **Proprietà del Nodo Rosso**: Se un nodo è **rosso**, allora entrambi i suoi figli devono essere **neri**. (Questo implica che non possono esistere due nodi rossi consecutivi su un percorso dalla radice a una foglia).
5.  **Proprietà della Profondità Nera**: Per ogni nodo, tutti i percorsi semplici da quel nodo alle foglie sue discendenti contengono lo stesso numero di nodi **neri**. Questo numero è chiamato **altezza nera** (*black-height*) del nodo, denotata con `bh(x)`.

### **Altezza di un Albero Rosso-Nero**
Da queste proprietà deriva un risultato fondamentale: un albero rosso-nero con `n` nodi interni ha un'altezza `h ≤ 2 * log₂(n + 1)`. Questo dimostra matematicamente che l'altezza è **sempre logaritmica**, garantendo così performance `O(log n)`.

---

### **Operazioni sugli Alberi Rosso-Neri**
Le operazioni di sola lettura sono identiche a quelle di un ABR. Le operazioni di modifica (inserimento e cancellazione) richiedono passaggi aggiuntivi per "riparare" eventuali violazioni delle proprietà rosso-nere.

#### **Operazioni non modificatrici (`O(log n)`)**
Le operazioni `TREE-SEARCH`, `TREE-MINIMUM`, `TREE-MAXIMUM`, `TREE-SUCCESSOR`, e `TREE-PREDECESSOR` sono **identiche** a quelle di un ABR standard. Poiché l'altezza `h` è garantita essere `O(log n)`, anche queste operazioni hanno una complessità garantita di `O(log n)`.

#### **Rotazioni (Operazione di base per il bilanciamento)**
**Descrizione**: Le rotazioni sono operazioni locali a tempo costante (`O(1)`) che ristrutturano l'albero per ripristinare le proprietà rosso-nere. Una rotazione preserva la proprietà fondamentale degli ABR (l'ordine delle chiavi).

**Pseudocodice (Rotazione a Sinistra)**
```cpp
LEFT-ROTATE(T, x)
    y <- x.right
    x.right <- y.left
    if y.left != T.NIL
        y.left.p <- x
    y.p <- x.p
    if x.p == T.NIL
        T.root <- y
    else if x == x.p.left
        x.p.left <- y
    else
        x.p.right <- y
    y.left <- x
    x.p <- y
```

**Pseudocodice (Rotazione a Destra)**
```cpp
RIGHT-ROTATE(T, y)
    x <- y.left
    y.left <- x.right
    if x.right != T.NIL
        x.right.p <- y
    x.p <- y.p
    if y.p == T.NIL
        T.root <- x
    else if y == y.p.right
        y.p.right <- x
    else
        y.p.left <- x
    x.right <- y
    y.p <- x
```

#### **Inserimento (Insertion)**
**Descrizione**: Per inserire un nodo `z`, si segue una procedura in due fasi:
1.  Si esegue un `TREE-INSERT` standard come in un ABR.
2.  Si colora il nuovo nodo `z` di **rosso**. Colorarlo di rosso può violare solo la proprietà 4 (due nodi rossi consecutivi), ma non la proprietà 5 (altezza nera), che è più difficile da ripristinare.
3.  Si chiama una procedura di "riparazione", `RB-INSERT-FIXUP`, che attraverso ricolorazioni e rotazioni ripristina le proprietà rosso-nere in tempo `O(log n)`.

**Complessità**: `O(log n)`.

**Pseudocodice**
```cpp
RB-INSERT(T, z)
    y <- T.NIL
    x <- T.root
    while x != T.NIL
        y <- x
        if z.key < x.key
            x <- x.left
        else
            x <- x.right
    z.p <- y
    if y == T.NIL
        T.root <- z
    else if z.key < y.key
        y.left <- z
    else
        y.right <- z
    z.left <- T.NIL
    z.right <- T.NIL
    z.color <- RED
    RB-INSERT-FIXUP(T, z)

RB-INSERT-FIXUP(T, z)
    while z.p.color == RED
        if z.p == z.p.p.left
            y <- z.p.p.right  // y è lo "zio" di z
            // Caso 1: Lo zio y è ROSSO
            if y.color == RED
                z.p.color <- BLACK
                y.color <- BLACK
                z.p.p.color <- RED
                z <- z.p.p
            else
                // Caso 2: Lo zio y è NERO e z è un figlio destro (forma un "triangolo")
                if z == z.p.right
                    z <- z.p
                    LEFT-ROTATE(T, z)
                // Caso 3: Lo zio y è NERO e z è un figlio sinistro (forma una "linea")
                z.p.color <- BLACK
                z.p.p.color <- RED
                RIGHT-ROTATE(T, z.p.p)
        else
            // Casi simmetrici (se z.p è un figlio destro)
            ...
    T.root.color <- BLACK
```

#### **Cancellazione (Deletion)**
**Descrizione**: La cancellazione è l'operazione più complessa. Similmente all'inserimento, si esegue prima una cancellazione standard da ABR (con `TRANSPLANT`), ma si tiene traccia del colore del nodo effettivamente rimosso.
- Se il nodo rimosso era **rosso**, le proprietà rosso-nere sono ancora valide.
- Se il nodo rimosso era **nero**, si viola la proprietà 5 (altezza nera). Il nodo `x` che prende il suo posto eredita un "nero extra".
- La procedura `RB-DELETE-FIXUP` viene chiamata su questo nodo `x` per ripristinare l'equilibrio, spingendo il "nero extra" verso l'alto nell'albero o eliminandolo tramite rotazioni e ricolorazioni.

**Complessità**: `O(log n)`.

**Pseudocodice (semplificato, la versione completa è più lunga)**
```cpp
// Versione di TRANSPLANT per ARN
RB-TRANSPLANT(T, u, v)
    // ... identico a TRANSPLANT per ABR

RB-DELETE(T, z)
    y <- z
    y-original-color <- y.color
    if z.left == T.NIL
        x <- z.right
        RB-TRANSPLANT(T, z, z.right)
    else if z.right == T.NIL
        x <- z.left
        RB-TRANSPLANT(T, z, z.left)
    else
        y <- TREE-MINIMUM(z.right)
        y-original-color <- y.color
        x <- y.right
        if y.p == z
            x.p <- y
        else
            RB-TRANSPLANT(T, y, y.right)
            y.right <- z.right
            y.right.p <- y
        RB-TRANSPLANT(T, z, y)
        y.left <- z.left
        y.left.p <- y
        y.color <- z.color
    if y-original-color == BLACK
        RB-DELETE-FIXUP(T, x)

RB-DELETE-FIXUP(T, x)
    while x != T.root and x.color == BLACK
        // ... Logica complessa con 4 casi principali e i loro simmetrici
        // per gestire il "nero extra" in base al colore del fratello di x (w)
        // e dei figli di w.
        ...
    x.color <- BLACK
```

---

### **Analisi dell'Algoritmo**

1.  **Complessità Temporale**:
    - Grazie alla garanzia che l'altezza `h` è sempre `O(log n)`, tutte le operazioni — **ricerca, inserimento e cancellazione** — hanno una complessità nel **caso peggiore** di **$O(\log n)$**.
    - Le procedure di "fixup" richiedono al massimo `O(log n)` ricolorazioni e un numero costante di rotazioni (`O(1)`) per terminare.

2.  **Complessità Spaziale**:
    - **$O(n)$** per memorizzare gli `n` nodi e il bit di colore aggiuntivo per ciascuno.

---

### **Vantaggi e Confronto**

| Caratteristica | Albero Binario di Ricerca (ABR) | Albero Rosso-Nero (ARN) |
| :--- | :--- | :--- |
| **Performance (Caso Peggiore)** | $O(n)$ | **$O(\log n)$ (Garantita)** |
| **Bilanciamento** | Nessuno | Auto-bilanciante |
| **Complessità Implementativa** | Semplice | **Complessa** (specialmente la cancellazione) |
| **Spazio per Nodo** | `key`, `p`, `left`, `right` | `key`, `p`, `left`, `right`, **`color`** |
| **Utilizzo** | Adatto quando i dati in input sono casuali. | Adatto per applicazioni critiche dove le performance del caso peggiore non sono accettabili (es. database, scheduler del kernel dei sistemi operativi). |