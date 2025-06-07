# Esercizio: Codifica di Huffman

## Problema

Si consideri un file `F` costituito da `300000 simboli { ! ( £ ) & = ? }` le cui frequenze sono rispettivamente `33%, 6%, 4%, 26%, 13%, 10%, 8%`. Si scriva un programma, in pseudocodice, che costruisca l'albero di codifica di Huffman e determini per ogni simbolo la sua codifica di Huffman. Calcolare l'eventuale risparmio di memoria che si otterrebbe codificando il file con la codifica di Huffman invece di una codifica a lunghezza fissa.

---

## Spiegazione dell'Approccio

Il problema chiede di applicare l'algoritmo di Huffman per comprimere un file basandosi sulle frequenze dei simboli dati. I passaggi principali sono:

1.  **Preparazione dei Dati:** Associare ogni simbolo alla sua frequenza.
2.  **Costruzione dell'Albero di Huffman:**
    *   Creare un nodo foglia per ogni simbolo, con un peso pari alla sua frequenza.
    *   Utilizzare una coda di priorità (min-heap) per gestire questi nodi.
    *   Ripetutamente, estrarre i due nodi con la frequenza minima.
    *   Creare un nuovo nodo interno la cui frequenza è la somma delle frequenze dei due nodi estratti, che diventano i suoi figli.
    *   Inserire il nuovo nodo interno nella coda di priorità.
    *   Continuare finché non rimane un solo nodo (la radice).
3.  **Determinazione delle Codifiche:** Attraversare l'albero di Huffman dalla radice (assegnando 0 per un ramo sinistro e 1 per un ramo destro, o viceversa) per trovare il codice binario di ogni simbolo.
4.  **Calcolo del Risparmio di Memoria:** Confrontare il costo totale in bit della codifica di Huffman con quello di una codifica a lunghezza fissa.

---

## Dati del Problema e Preparazione

*   **Numero totale di simboli nel file:** 300.000
*   **Simboli e Frequenze (in percentuale):**
    *   `!` : 33%
    *   `(` : 6%
    *   `£` : 4%
    *   `)` : 26%
    *   `&` : 13%
    *   `=` : 10%
    *   `?` : 8%

**Simboli con Frequenze (ordinati per facilità di tracciamento manuale):**

| Simbolo Originale | Frequenza (%) |
|-------------------|---------------|
| `£`               | 4             |
| `(`               | 6             |
| `?`               | 8             |
| `=`               | 10            |
| `&`               | 13            |
| `)`               | 26            |
| `!`               | 33            |

---

## Algoritmo di Costruzione dell'Albero di Huffman (Pseudocodice Semplificato)

```c
// C: insieme dei simboli con le loro frequenze, rappresentati come nodi foglia
// Ogni nodo ha: simbolo (opzionale), frequenza, figlioSinistro, figlioDestro

Funzione COSTRUISCI_HUFFMAN(C)
  n = |C| // Numero di simboli/nodi foglia iniziali
  Q = C   // Inizializza la coda di priorità (min-heap) con i nodi foglia

  PER i DA 1 A n-1 FA // Esegui n-1 fusioni
    z = NUOVO_NODO() // Alloca un nuovo nodo interno

    // Estrai i due nodi con frequenza minima e assegnali come figli di z
    // (la scelta di quale sia sinistro/destro è arbitraria se le frequenze sono diverse,
    //  se uguali, si segue una regola consistente o arbitraria)
    z.figlioSinistro = Q.ESTRAI_MIN() 
    z.figlioDestro = Q.ESTRAI_MIN()
    
    // Calcola la frequenza del nuovo nodo z
    z.frequenza = z.figlioSinistro.frequenza + z.figlioDestro.frequenza
    
    // Inserisci z nella coda di priorità
    Q.INSERISCI(z)
  FINE PER
  
  // L'unico nodo rimasto in Q è la radice dell'albero di Huffman
  RITORNA Q.ESTRAI_MIN() 
FINE FUNZIONE
```

---
## Costruzione dell'Albero (Passo Passo)

Utilizziamo le frequenze: {£:4, (:6, ?:8, =:10, &:13, ):26, !:33}

1.  **Inizializzazione Coda di Priorità (Q):**
    `Q = [(£:4), (:6), (?:8), (=:10), (&:13), ():26), (!:33)]`

2.  **Iterazione 1:**
    *   Estrai `(£:4)` e `(:6)`
    *   Nuovo nodo `N1` (freq = 4+6 = 10). Figli: (£:4), (:6)
    *   `Q = [(?:8), (=:10), (N1:10), (&:13), ():26), (!:33)]`

3.  **Iterazione 2:**
    *   Estrai `(?:8)` e `(=:10)`
    *   Nuovo nodo `N2` (freq = 8+10 = 18). Figli: (?:8), (=:10)
    *   `Q = [(N1:10), (&:13), (N2:18), ():26), (!:33)]`

4.  **Iterazione 3:**
    *   Estrai `(N1:10)` e `(&:13)`
    *   Nuovo nodo `N3` (freq = 10+13 = 23). Figli: (N1:10), (&:13)
    *   `Q = [(N2:18), (N3:23), ():26), (!:33)]`

5.  **Iterazione 4:**
    *   Estrai `(N2:18)` e `(N3:23)`
    *   Nuovo nodo `N4` (freq = 18+23 = 41). Figli: (N2:18), (N3:23)
    *   `Q = [():26), (!:33), (N4:41)]`

6.  **Iterazione 5:**
    *   Estrai `():26)` e `(!:33)`
    *   Nuovo nodo `N5` (freq = 26+33 = 59). Figli: ():26), (!:33)
    *   `Q = [(N4:41), (N5:59)]`

7.  **Iterazione 6 (Ultima):**
    *   Estrai `(N4:41)` e `(N5:59)`
    *   Nuovo nodo `Radice(N6)` (freq = 41+59 = 100). Figli: (N4:41), (N5:59)
    *   `Q = [(Radice:100)]`

La radice dell'albero è `N6`.

![Albero](https://i.imgur.com/isoSRTF.png)

## Determinazione dei Codici di Huffman

Attraversiamo l'albero dalla radice (N6), assegnando '0' al ramo sinistro e '1' al ramo destro.

*   **Radice (N6, freq 100)**
    *   `0`: **N4 (freq 41)**
        *   `00`: **N2 (freq 18)**
            *   `000`: **? (freq 8)**
            *   `001`: **= (freq 10)**
        *   `01`: **N3 (freq 23)**
            *   `010`: **N1 (freq 10)**
                *   `0100`: **£ (freq 4)**
                *   `0101`: **( (freq 6)**
            *   `011`: **& (freq 13)**
    *   `1`: **N5 (freq 59)**
        *   `10`: **) (freq 26)**
        *   `11`: **! (freq 33)**

**Tabella dei Codici di Huffman:**

| Simbolo Originale | Frequenza (%) | Codice Huffman | Lunghezza Codice |
|-------------------|---------------|----------------|------------------|
| `!`               | 33            | `11`           | 2                |
| `)`               | 26            | `10`           | 2                |
| `&`               | 13            | `011`          | 3                |
| `=`               | 10            | `001`          | 3                |
| `?`               | 8             | `000`          | 3                |
| `(`               | 6             | `0101`         | 4                |
| `£`               | 4             | `0100`         | 4                |

## Calcolo del Risparmio di Memoria

**1. Costo con Codifica a Lunghezza Fissa:**
*   Numero di simboli unici = 7.
*   Bit per simbolo = `ceil(log2(7))` = **3 bit**.
*   Costo totale fisso = 300.000 simboli * 3 bit/simbolo = **900.000 bit**.

**2. Costo con Codifica di Huffman:**
Lunghezza media del codice (L_media) = Σ (frequenza_i * lunghezza_codice_i)
*   `!`: 0.33 * 2 = 0.66
*   `)`: 0.26 * 2 = 0.52
*   `&`: 0.13 * 3 = 0.39
*   `=`: 0.10 * 3 = 0.30
*   `?`: 0.08 * 3 = 0.24
*   `(`: 0.06 * 4 = 0.24
*   `£`: 0.04 * 4 = 0.16
L_media = 0.66 + 0.52 + 0.39 + 0.30 + 0.24 + 0.24 + 0.16 = **2.51 bit/simbolo**.

Costo totale Huffman = 300.000 simboli * 2.51 bit/simbolo = **753.000 bit**.

**3. Risparmio di Memoria:**
*   Risparmio in bit = 900.000 bit - 753.000 bit = **147.000 bit**.
*   Risparmio percentuale = (147.000 / 900.000) * 100% = **16.33%** (circa).

---

## Riassunto

L'algoritmo di Huffman genera una codifica a lunghezza variabile ottimale, assegnando codici più corti ai simboli più frequenti.
Per il file dato, la codifica di Huffman riduce la dimensione da **900.000 bit** (con codifica fissa a 3 bit) a **753.000 bit**, ottenendo un risparmio di **147.000 bit** (circa il **16.33%**).

```
