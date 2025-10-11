## **Introduzione agli Alberi di Ricerca: Dagli ABR agli Alberi Auto-Bilancianti**

Per provare gli algoritmi recarsi su [questo sito ](https://just-ipavon.github.io/ABR-RB/)
### Descrizione:
Nel campo delle strutture dati, una delle sfide più comuni è quella di gestire un insieme dinamico di elementi. Questo significa poter eseguire in modo efficiente operazioni come la **ricerca**, l'**inserimento** e la **cancellazione** di dati. Mentre un semplice array ordinato è eccellente per la ricerca (usando la ricerca binaria), le operazioni di inserimento e cancellazione sono costose, richiedendo lo spostamento di molti elementi.

Gli **alberi di ricerca** offrono una soluzione elegante a questo problema, combinando la flessibilità delle liste concatenate con l'efficienza di ricerca degli array ordinati. Questo documento introduce il concetto fondamentale di **Albero Binario di Ricerca (ABR)** e la sua evoluzione in una struttura più robusta e performante: l'**Albero Rosso-Nero (ARN)**.

---

### **1. Il Concetto Base: [L'Albero Binario di Ricerca (ABR)](algortmi/AlberiRicercaBinaria.md)**
L'**Albero Binario di Ricerca (ABR)** è la struttura di partenza. Si tratta di un albero binario basato su nodi, dove ogni nodo contiene una chiave. La sua potenza deriva da una singola, semplice regola, nota come **proprietà degli ABR**:

> Per ogni nodo `x`, tutte le chiavi nel suo sottoalbero sinistro sono minori o uguali alla chiave di `x`, e tutte le chiavi nel suo sottoalbero destro sono maggiori o uguali.

#### **Perché è utile?**
Questa proprietà permette di navigare l'albero in modo molto efficiente. Per cercare un valore, si parte dalla radice e, a ogni passo, si decide se andare a sinistra o a destra, dimezzando di fatto lo spazio di ricerca. Questo porta a performance medie eccellenti.

- **Operazioni Principali**: Ricerca, Inserimento, Cancellazione, Minimo, Massimo.
- **Performance Media (Caso Tipico)**: `O(log n)`, dove `n` è il numero di nodi. Questo si verifica quando l'albero è **bilanciato**, ovvero ha una struttura simile a un cespuglio.

#### **Il Tallone d'Achille: Il Caso Peggiore**
Il grande limite di un ABR è la sua vulnerabilità all'ordine di inserimento dei dati. Se gli elementi vengono inseriti in ordine (crescente o decrescente), l'albero non cresce in larghezza, ma solo in altezza, diventando un **albero degenere** (essenzialmente una lista concatenata).

- **Performance nel Caso Peggiore**: `O(n)`. L'albero perde tutti i suoi vantaggi, e le operazioni diventano lente come in una lista non ordinata.

---

### **2. La Soluzione Robusta: [L'Albero Rosso-Nero (ARN)](algortmi/alberiRB.md)**
Per risolvere il problema del caso peggiore, sono stati introdotti gli **alberi auto-bilancianti**. L'**Albero Rosso-Nero (ARN)** è una delle implementazioni più famose e utilizzate di questo concetto.

Un ARN è, prima di tutto, un ABR. Mantiene la proprietà fondamentale di ordinamento, ma aggiunge un insieme di **regole aggiuntive** (le "proprietà rosso-nere") per garantire che l'albero non diventi mai troppo sbilanciato.

#### **Come funziona?**
Ogni nodo ha un colore (rosso o nero). Dopo ogni operazione di inserimento o cancellazione, l'albero verifica se le proprietà rosso-nere sono state violate. Se lo sono, l'albero esegue una serie di **ricolorazioni** e **rotazioni** (operazioni locali a tempo costante) per "riparare" la sua struttura e ripristinare il bilanciamento.

- **Operazioni Principali**: Le stesse di un ABR, ma con una logica di "riparazione" aggiuntiva.
- **Performance Garantita**: `O(log n)` **in tutti i casi** (migliore, medio e peggiore).

#### **Il Compromesso**
Questa garanzia di performance ha un costo:
- **Maggiore Complessità**: L'implementazione di un ARN, specialmente per l'operazione di cancellazione, è notevolmente più complessa di quella di un ABR.
- **Leggero Overhead**: Le operazioni di "riparazione" aggiungono un piccolo costo computazionale a ogni inserimento e cancellazione, anche se questo costo è trascurabile rispetto ai benefici ottenuti nel prevenire il caso peggiore.

---

### **Tabella Riassuntiva del Percorso**

| Caratteristica | Albero Binario di Ricerca (ABR) | Albero Rosso-Nero (ARN) |
| :--- | :--- | :--- |
| **Scopo Principale** | Fornire una struttura dati ordinata e dinamica. | Garantire che le operazioni su un ABR siano sempre veloci. |
| **Proprietà Chiave** | Ordinamento (sinistra < radice < destra). | Proprietà ABR + 5 regole su colori e altezze nere. |
| **Bilanciamento** | **Nessuno**. Dipende dall'ordine di inserimento. | **Auto-bilanciante**. Mantiene l'altezza `h = O(log n)`. |
| **Performance (Caso Medio)** | `O(log n)` | `O(log n)` |
| **Performance (Caso Peggiore)** | **`O(n)`** | **`O(log n)`** |
| **Quando usarlo?** | Quando si è sicuri che i dati in input siano sufficientemente casuali da non creare un albero degenere. Ideale per prototipi o contesti non critici. | Quando sono necessarie garanzie sulle performance del caso peggiore. Fondamentale in database, scheduler di sistemi operativi e altre applicazioni critiche. |

---

### **Prossimi Passi**
Ora che abbiamo introdotto i concetti di base, i prossimi documenti approfondiranno nel dettaglio:
1.  **Alberi Binari di Ricerca**: Analisi completa delle operazioni e dello pseudocodice.
2.  **Alberi Rosso-Neri**: Analisi delle proprietà, delle rotazioni e delle complesse procedure di inserimento e cancellazione.
