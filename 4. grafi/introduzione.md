# Introduzione ai Grafi

## Cos'è un Grafo?

Un grafo è una struttura matematica utilizzata per modellare le relazioni tra oggetti. Un grafo è composto da:

- **Nodi (o vertici)**: rappresentano gli oggetti.
- **Archi (o spigoli)**: rappresentano le relazioni tra gli oggetti.

## Proprietà dei Grafi

### Tipi di Grafi

- **Grafo non orientato**: gli archi non hanno una direzione.
- **Grafo orientato (o digrafo)**: gli archi hanno una direzione.

### Connettività

- **Grafo connesso**: esiste un percorso tra ogni coppia di nodi.
- **Grafo fortemente connesso**: esiste un percorso diretto tra ogni coppia di nodi (solo per grafi orientati).

## Nozioni di Base

### Percorsi e Cicli

- **Percorso**: una sequenza di nodi collegati da archi.
- **Ciclo**: un percorso che inizia e termina nello stesso nodo.

### Alberi

- **Albero**: un grafo connesso senza cicli.
- **Radice**: il nodo principale di un albero.
- **Foglie**: nodi senza figli.

### Matrici di Adiacenza e Liste di Adiacenza

- **Matrice di adiacenza**: una matrice che rappresenta la presenza di archi tra i nodi.
- **Lista di adiacenza**: una lista che rappresenta i nodi adiacenti a ciascun nodo.

### Proprietà

- **Adiacenza**: due nodi sono adiacenti se esiste un arco che li collega direttamente.
- **Cammino**: una sequenza di nodi in cui ogni coppia consecutiva di nodi è collegata da un arco.
- **Lunghezza**: il numero di archi in un cammino.
- **Cammino semplice**: un cammino che non contiene nodi ripetuti.

## Visite dei Grafi

### Visita in Ampiezza (BFS)

La visita in ampiezza esplora i nodi di un grafo livello per livello, partendo da un nodo iniziale e visitando tutti i suoi vicini prima di passare ai vicini dei vicini.

### Visita in Profondità (DFS)

La visita in profondità esplora i nodi di un grafo andando il più lontano possibile lungo ogni ramo prima di tornare indietro.

### Applicazioni delle Visite

- **Ricerca di percorsi**: trovare un percorso tra due nodi.
- **Rilevamento di cicli**: determinare se un grafo contiene cicli.
- **Componenti connesse**: identificare le componenti connesse di un grafo.
- **Ordinamento topologico**: ordinare i nodi di un grafo orientato aciclico (DAG).

## Algoritmi sui Grafi
### Algoritmo di Dijkstra

L'algoritmo di Dijkstra è un algoritmo goloso utilizzato per risolvere il problema del percorso minimo da un nodo sorgente a tutti gli altri nodi in un grafo con pesi non negativi. Ecco una descrizione più dettagliata del suo funzionamento:

1. **Inizializzazione**: Si inizializzano le distanze di tutti i nodi dalla sorgente a infinito, eccetto la sorgente stessa che ha distanza zero. Si utilizza una coda di priorità per tenere traccia dei nodi da esplorare.
2. **Esplorazione**: Si estrae il nodo con la distanza minima dalla coda di priorità e si aggiornano le distanze dei suoi vicini. Se la distanza trovata è minore della distanza attuale, si aggiorna e si inserisce il nodo nella coda di priorità.
3. **Ripetizione**: Si ripete il processo fino a quando la coda di priorità è vuota.

### Algoritmo di Bellman-Ford

L'algoritmo di Bellman-Ford è utilizzato per trovare il percorso più breve da un nodo sorgente a tutti gli altri nodi in un grafo, anche se i pesi degli archi possono essere negativi. Ecco una descrizione più dettagliata del suo funzionamento:

1. **Inizializzazione**: Si inizializzano le distanze di tutti i nodi dalla sorgente a infinito, eccetto la sorgente stessa che ha distanza zero.
2. **Rilassamento**: Si ripete il processo di rilassamento per tutti gli archi del grafo per un numero di volte pari al numero di nodi meno uno. Il rilassamento consiste nell'aggiornare la distanza di un nodo se si trova un percorso più corto.
3. **Controllo dei cicli negativi**: Dopo il rilassamento, si esegue un controllo aggiuntivo per verificare la presenza di cicli di peso negativo. Se si trova un ciclo di peso negativo, significa che non esiste una soluzione valida.
