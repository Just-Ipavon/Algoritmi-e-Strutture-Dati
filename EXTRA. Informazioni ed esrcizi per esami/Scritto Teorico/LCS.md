# Longest Common Subsequence (LCS) tra Nome e Cognome

## Problema

Si scriva un algoritmo in pseudocodice che calcoli la **Longest Common Subsequence (LCS)** tra due stringhe date, specificamente applicato al proprio nome e cognome. 
L'algoritmo deve determinare la lunghezza della LCS e fornire un modo per ricostruire la sottosequenza stessa.

---

## Logica dell'Algoritmo

Il problema della Longest Common Subsequence (LCS) viene risolto classicamente utilizzando la **programmazione dinamica**. L'idea è di costruire una soluzione per il problema originale basandosi sulle soluzioni di sottoproblemi più piccoli.

Date due sequenze (stringhe) `X` e `Y` di lunghezze `m` e `n` rispettivamente:
1.  Si crea una tabella `c[0..m, 0..n]` dove `c[i,j]` memorizzerà la lunghezza della LCS tra i prefissi `X_i` (i primi `i` caratteri di `X`) e `Y_j` (i primi `j` caratteri di `Y`).
2.  La tabella viene riempita iterativamente. Per ogni cella `c[i,j]`:
    *   Se `x_i` (l'i-esimo carattere di `X`) è uguale a `y_j` (il j-esimo carattere di `Y`), allora questo carattere fa parte della LCS. La lunghezza `c[i,j]` sarà `1 + c[i-1,j-1]`.
    *   Se `x_i ≠ y_j`, allora il carattere non contribuisce direttamente. La lunghezza `c[i,j]` sarà il massimo tra `c[i-1,j]` (LCS senza `x_i`) e `c[i,j-1]` (LCS senza `y_j`).
3.  Una seconda tabella, `b[1..m, 1..n]`, viene usata per memorizzare le scelte fatte durante il calcolo di `c`, permettendo di ricostruire la LCS.

La lunghezza finale della LCS tra `X` e `Y` sarà `c[m,n]`. La sottosequenza effettiva viene ricostruita seguendo le direzioni memorizzate nella tabella `b` a partire da `b[m,n]`.

---

## Pseudocodice (Stile Cormen)

```c
// X e Y sono le due sequenze (stringhe) date.
// X = <x₁, x₂, ..., xₘ>, Y = <y₁, y₂, ..., yₙ>
// c[i,j] memorizza la lunghezza della LCS di Xᵢ e Yⱼ.
// b[i,j] memorizza la direzione ("↖", "↑", "←") usata per calcolare c[i,j].

LCS-LENGTH(X, Y)
  m ← |X| // Lunghezza di X
  n ← |Y| // Lunghezza di Y
  sia b[1..m, 1..n] e c[0..m, 0..n] nuove tabelle
  
  // Inizializza la riga 0 e la colonna 0 di c a 0
  PER i ← 0 TO m
    c[i,0] ← 0
  PER j ← 0 TO n
    c[0,j] ← 0
    
  // Popola le tabelle c e b
  PER i ← 1 TO m
    PER j ← 1 TO n
      SE xᵢ = yⱼ // Confronto tra i caratteri
        c[i,j] ← c[i-1,j-1] + 1
        b[i,j] ← "↖" 
      ALTRIMENTI SE c[i-1,j] ≥ c[i,j-1] // Confronto
        c[i,j] ← c[i-1,j]
        b[i,j] ← "↑" 
      ALTRIMENTI
        c[i,j] ← c[i,j-1]
        b[i,j] ← "←" 
  RITORNA c e b // Restituisce le tabelle popolate

PRINT-LCS(b, X, i, j)
  SE i = 0 O j = 0 // Confronto (caso base)
    RITORNA
  SE b[i,j] = "↖" // Confronto
    PRINT-LCS(b, X, i-1, j-1)
    STAMPA X[i] // Stampa l'elemento xᵢ che fa parte della LCS
  ALTRIMENTI SE b[i,j] = "↑" // Confronto
    PRINT-LCS(b, X, i-1, j)
  ALTRIMENTI // b[i,j] deve essere "←"
    PRINT-LCS(b, X, i, j-1)
```
---

## Esempio Pratico: "PASQUALE" e "RUOTOLO"

*   `X = P A S Q U A L E` (lunghezza `m = 8`)
    *   `x₁=P, x₂=A, x₃=S, x₄=Q, x₅=U, x₆=A, x₇=L, x₈=E`
*   `Y = R U O T O L O` (lunghezza `n = 7`)
    *   `y₁=R, y₂=U, y₃=O, y₄=T, y₅=O, y₆=L, y₇=O`

**1. Chiamata a `LCS-LENGTH("PASQUALE", "RUOTOLO")`:**

**Tabella `c` (lunghezze) finale:**
```
      j=0 Y="" R(1) U(2) O(3) T(4) O(5) L(6) O(7)
i=0 X=""  0    0    0    0    0    0    0    0
P(1)      0    0    0    0    0    0    0    0
A(2)      0    0    0    0    0    0    0    0
S(3)      0    0    0    0    0    0    0    0
Q(4)      0    0    0    0    0    0    0    0
U(5)      0    0    1    1    1    1    1    1  (x₅='U' == y₂='U')
A(6)      0    0    1    1    1    1    1    1
L(7)      0    0    1    1    1    1    2    2  (x₇='L' == y₆='L')
E(8)      0    0    1    1    1    1    2    2
```
La lunghezza della LCS è `c[8,7] = 2`.

**Tabella `b` (direzioni) finale (una possibile configurazione, preferendo "↑" in caso di parità `c[i-1,j] ≥ c[i,j-1]`):**
(Mostro solo le celle rilevanti per il percorso e i match)
```
      j=0 Y="" R(1) U(2) O(3) T(4) O(5) L(6) O(7)
i=0 X=""  .    .    .    .    .    .    .    .
P(1)      .    ↑    ↑    ↑    ↑    ↑    ↑    ↑
A(2)      .    ↑    ↑    ↑    ↑    ↑    ↑    ↑
S(3)      .    ↑    ↑    ↑    ↑    ↑    ↑    ↑
Q(4)      .    ↑    ↑    ↑    ↑    ↑    ↑    ↑
U(5)      .    ↑    ↖    ←    ←    ←    ←    ←  (x₅='U' == y₂='U')
A(6)      .    ↑    ↑    ↑    ↑    ↑    ↑    ↑
L(7)      .    ↑    ↑    ↑    ↑    ↑    ↖    ←  (x₇='L' == y₆='L')
E(8)      .    ↑    ↑    ↑    ↑    ↑    ↑    ↑
```

**2. Chiamata a `PRINT-LCS(b, "PASQUALE", 8, 7)` per stampare la LCS:**

1.  `PRINT-LCS(b, X, 8, 7)`: (`E` vs `O`)
    *   `b[8,7]` è `↑` (poiché `c[7,7]=2 ≥ c[8,6]=2`).
    *   Chiama `PRINT-LCS(b, X, 7, 7)`.

2.  `PRINT-LCS(b, X, 7, 7)`: (`L` vs `O`)
    *   `b[7,7]` è `←` (poiché `c[7,6]=2 > c[6,7]=1`).
    *   Chiama `PRINT-LCS(b, X, 7, 6)`.

3.  `PRINT-LCS(b, X, 7, 6)`: (`L` vs `L`)
    *   `x₇ = y₆` (`L` = `L`). `b[7,6]` è `↖`.
    *   Chiama `PRINT-LCS(b, X, 6, 5)`.
    *   *Dopo che la chiamata ritorna*, STAMPA `X[7]` (cioè `L`).

4.  `PRINT-LCS(b, X, 6, 5)`: (`A` vs `O`)
    *   `b[6,5]` è `↑` (poiché `c[5,5]=1 ≥ c[6,4]=1`).
    *   Chiama `PRINT-LCS(b, X, 5, 5)`.

5.  `PRINT-LCS(b, X, 5, 5)`: (`U` vs `O`)
    *   `b[5,5]` è `←` (poiché `c[5,4]=1 > c[4,5]=0`).
    *   Chiama `PRINT-LCS(b, X, 5, 4)`.

6.  `PRINT-LCS(b, X, 5, 4)`: (`U` vs `T`)
    *   `b[5,4]` è `←` (poiché `c[5,3]=1 > c[4,4]=0`).
    *   Chiama `PRINT-LCS(b, X, 5, 3)`.

7.  `PRINT-LCS(b, X, 5, 3)`: (`U` vs `O`)
    *   `b[5,3]` è `←` (poiché `c[5,2]=1 > c[4,3]=0`).
    *   Chiama `PRINT-LCS(b, X, 5, 2)`.

8.  `PRINT-LCS(b, X, 5, 2)`: (`U` vs `U`)
    *   `x₅ = y₂` (`U` = `U`). `b[5,2]` è `↖`.
    *   Chiama `PRINT-LCS(b, X, 4, 1)`.
    *   *Dopo che la chiamata ritorna*, STAMPA `X[5]` (cioè `U`).

9.  `PRINT-LCS(b, X, 4, 1)`: (`Q` vs `R`)
    *   `b[4,1]` è `↑` (poiché `c[3,1]=0 ≥ c[4,0]=0`).
    *   Chiama `PRINT-LCS(b, X, 3, 1)`.

10. `PRINT-LCS(b, X, 3, 1)`: (`S` vs `R`) ... `↑` ... Chiama `PRINT-LCS(b, X, 2, 1)`.
11. `PRINT-LCS(b, X, 2, 1)`: (`A` vs `R`) ... `↑` ... Chiama `PRINT-LCS(b, X, 1, 1)`.
12. `PRINT-LCS(b, X, 1, 1)`: (`P` vs `R`) ... `↑` ... Chiama `PRINT-LCS(b, X, 0, 1)`.
13. `PRINT-LCS(b, X, 0, 1)`: `i=0`. RITORNA.

**Ordine di Stampa e Risultato:**
La ricorsione di `PRINT-LCS` fa sì che i caratteri vengano stampati nell'ordine corretto:
1.  La chiamata più profonda che trova un `↖` è `PRINT-LCS(b, X, 5, 2)` (per `U`). Prima di stampare `U`, chiama `PRINT-LCS(b, X, 4, 1)`, che eventualmente ritorna. Poi stampa `U`.
2.  Poi la ricorsione risale. La successiva chiamata che trova un `↖` è `PRINT-LCS(b, X, 7, 6)` (per `L`). Prima di stampare `L`, chiama `PRINT-LCS(b, X, 6, 5)`, che eventualmente ritorna (dopo aver stampato `U` nel suo sotto-percorso). Poi stampa `L`.

Quindi, l'output stampato sarà: **"UL"**.

La Longest Common Subsequence tra "PASQUALE" e "RUOTOLO" è "UL", e la sua lunghezza è 2.

---

## Riassunto

L'algoritmo `LCS-LENGTH` calcola la lunghezza della sottosequenza comune più lunga tra due stringhe `X` e `Y` e riempie una tabella ausiliaria `b` che indica come è stata costruita la soluzione. 
La procedura `PRINT-LCS` utilizza la tabella `b` per ricostruire e stampare una delle LCS. Questo approccio di programmazione dinamica garantisce di trovare la lunghezza ottimale e una sottosequenza corrispondente.

---
