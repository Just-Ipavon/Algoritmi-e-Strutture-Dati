# Aereoporto e tempi di attesa
## Problema

L'aereoporto di Capodichino ha fatto costruire una nuova pista di decollo e di atterraggio. Il direttore dell'aereoporto decide di utilizzare la pista per servire i nuovi `N aerei` che dovranno decollare dall'aereoporto.
Supponiamo che `t[i]` sia il tempo necessario all'`i-simo aereo` per decollare, scrivere un algoritmo, in pseudocodice, che utilizzando la struttura dati `coda di priorità` minimizzi il tempo totale di attesa (o turnaround) degli `N aerei` per decollare

---

## Logica dell'Algoritmo
Per minimizzare il `tempo totale di attesa` per il decollo degli `N aerei`, bisogna far decollare prima quelli che impiegano meno tempo.
Questo è un classico problema risolvibile con una coda di `priorità (min-heap)`, dove la priorità è data dal tempo di decollo, `t[i]`.

---

## Algoritmo 

1. Inserisci tutti gli aerei con il loro tempo di decollo `t[i]` in una `coda di priorità (min-heap)`.
2. Estrai uno a uno gli aerei dalla coda (quello col tempo più basso viene estratto per primo).
3. Ad ogni estrazione, accumula il tempo trascorso e aggiornalo.
4. Somma i tempi di attesa di tutti gli aerei per ottenere il tempo totale minimo.


---

## Pseudocodice: 

```c
// Supponiamo che gli aerei siano dati come array t[1..N] dove t[i] è il tempo per l'i-simo aereo

funzione MinTempoAttesa(t[1..N]):
    crea una coda di priorità Q
    per i da 1 a N:
        inserisci Q, t[i]         // Inserisci il tempo di decollo nella coda di priorità

    tempo_totale = 0
    tempo_corrente = 0
    mentre Q non è vuota:
        ti = estrai_min(Q)        // Estrai l'aereo col tempo di decollo minore
        tempo_corrente = tempo_corrente + ti
        tempo_totale = tempo_totale + tempo_corrente

    ritorna tempo_totale
```
---

## Riassunto
L'algoritmo utilizza una coda di priorità per far decollare prima gli aerei che richiedono meno tempo, minimizzando così il tempo totale di attesa.
