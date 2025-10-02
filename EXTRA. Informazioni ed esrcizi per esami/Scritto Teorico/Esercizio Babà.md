# Massimizzazione Babà con Budget Limitato (Zaino Frazionario)

## Problema

Gennaro è ghiotto di babà. Per il suo compleanno, sua madre si reca in pasticceria. La pasticceria vende `N` tipi di torte di babà. Ogni torta di tipo `i` ha un costo `C[i]` ed un numero di babà `B[i]`. La madre ha deciso di spendere al massimo `E_max` euro.
Si scriva un algoritmo in pseudocodice che riceva come input le `N` torte (con i loro `B[i]` e `C[i]`) e il budget `E_max`. 
L'algoritmo deve restituire il numero massimo di babà che possono essere acquistati. Si assuma che sia possibile acquistare parti di torta, ma che i babà ottenuti da queste parti debbano essere interi (la parte frazionaria di un babà viene scartata).
Si assuma inoltre che le torte abbiano un costo positivo (`C[i] > 0`).

---

## Logica dell'Algoritmo

Il problema può essere affrontato con un adattamento dell'approccio greedy tipico dello **zaino frazionario**. La strategia consiste nel dare priorità alle torte che offrono il maggior numero di babà per euro speso.

Si presuppone che i dati delle torte siano **già ordinati** in modo decrescente in base a questo rapporto `B[i]/C[i]`.

L'algoritmo itera sulle torte ordinate:
1.  Per ogni torta, si determina la massima frazione acquistabile con il budget corrente.
2.  Si calcola il numero di babà interi che si otterrebbero da tale frazione, utilizzando la funzione `FLOOR` (che restituisce il più grande numero intero minore o uguale al suo argomento, di fatto troncando la parte decimale).
3.  Si sommano i babà ottenuti e si decrementa il budget in base alla spesa effettiva per la frazione di torta acquistata.
4.  Si continua finché il budget non è esaurito o tutte le torte sono state considerate.
---

## Pseudocodice (Stile Cormen)

```c
// Input:
//   B[1..N]: array del numero di babà per ogni delle N torte
//   C[1..N]: array dei costi (>0) per ognuna delle N torte
//   (Si assume che le torte siano già ordinate in modo che B[i]/C[i] sia decrescente)
//   E_max: budget massimo (euro) a disposizione

// Output:
//   baba_totali_massimi: il massimo numero di babà INTERI che possono essere acquistati

BABA-INTERI-DA-TORTE-FRAZIONATE-PREORDINATI(B, C, E_max)
  n ← |B| // Numero di tipi di torte
  baba_totali_massimi ← 0
  budget_corrente ← E_max

  FOR i ← 1 TO n // Itera sulle torte già ordinate per convenienza
    SE budget_corrente = 0 // Confronto: budget esaurito
      INTERROMPI-CICLO // Non si può comprare più nulla
    END IF

    // Determina la frazione massima di torta 'i' che si può acquistare
    // costo_intera_torta_i è C[i]
    frazione_acquistata_i ← 0.0
    spesa_per_torta_i ← 0.0

    SE budget_corrente ≥ C[i] THEN
      // Si può comprare l'intera torta 'i'
      frazione_acquistata_i ← 1.0
      spesa_per_torta_i ← C[i]
    ALTRIMENTI
      // Si può comprare solo una parte della torta 'i'
      // (solo se budget_corrente > 0, altrimenti frazione e spesa restano 0)
      SE budget_corrente > 0 THEN
         frazione_acquistata_i ← budget_corrente / C[i]
         spesa_per_torta_i ← budget_corrente // Si spende tutto il budget rimanente
      END IF
    END IF
    
    baba_da_torta_i ← FLOOR(frazione_acquistata_i * B[i])

    baba_totali_massimi ← baba_totali_massimi + baba_da_torta_i
    budget_corrente ← budget_corrente - spesa_per_torta_i 
  END FOR
  RITORNA baba_totali_massimi 
```
---

## Esempio Pratico

Supponiamo i seguenti dati (già ordinati per babà/euro):
*   Torta 1: `B[1]=20` babà, `C[1]=10` euro (Rapporto: 2 babà/euro)
*   Torta 2: `B[2]=12` babà, `C[2]=8` euro (Rapporto: 1.5 babà/euro)
*   Torta 3: `B[3]=5` babà, `C[3]=5` euro (Rapporto: 1 babà/euro)
*   Budget `E_max = 20` euro.

**Svolgimento `BABA-INTERI-DA-TORTE-FRAZIONATE-PREORDINATI`:**

1.  `n ← 3`, `baba_totali_massimi ← 0`, `budget_corrente ← 20`.

2.  **Iterazione `i = 1` (Torta 1: B=20, C=10):**
    *   `budget_corrente` (20) `≥ C[1]` (10) → VERO.
    *   `frazione_acquistata_1 ← 1.0`.
    *   `spesa_per_torta_1 ← 10`.
    *   `baba_da_torta_1 ← FLOOR(1.0 * 20) = FLOOR(20) = 20`.
    *   `baba_totali_massimi ← 0 + 20 = 20`.
    *   `budget_corrente ← 20 - 10 = 10`.

3.  **Iterazione `i = 2` (Torta 2: B=12, C=8):**
    *   `budget_corrente` (10) `≥ C[2]` (8) → VERO.
    *   `frazione_acquistata_2 ← 1.0`.
    *   `spesa_per_torta_2 ← 8`.
    *   `baba_da_torta_2 ← FLOOR(1.0 * 12) = FLOOR(12) = 12`.
    *   `baba_totali_massimi ← 20 + 12 = 32`.
    *   `budget_corrente ← 10 - 8 = 2`.

4.  **Iterazione `i = 3` (Torta 3: B=5, C=5):**
    *   `budget_corrente` (2) `≥ C[3]` (5) → FALSO.
    *   `budget_corrente` (2) `> 0` → VERO.
    *   `frazione_acquistata_3 ← 2 / 5 = 0.4`.
    *   `spesa_per_torta_3 ← 2`.
    *   `baba_da_torta_3 ← FLOOR(0.4 * 5) = FLOOR(2.0) = 2`.
    *   `baba_totali_massimi ← 32 + 2 = 34`.
    *   `budget_corrente ← 2 - 2 = 0`.

5.  **Iterazione successiva (ciclo termina):**
    *   `budget_corrente` (0) `= 0` → VERO. `INTERROMPI-CICLO`.

6.  **RITORNA `baba_totali_massimi` che è 34.**

Numero massimo di babà acquistati: 34.

---

## Riassunto

L'algoritmo applica una strategia greedy, considerando le torte già ordinate per il loro rapporto babà/costo. Per ogni torta, acquista la massima frazione possibile con il budget rimanente. Il numero di babà ottenuti da questa frazione viene calcolato utilizzando la funzione `FLOOR` per assicurare che si contino solo babà interi. Il budget viene aggiornato di conseguenza. Questo processo continua finché il budget non si esaurisce o tutte le torte sono state considerate.

---
