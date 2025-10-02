Certamente. Ho aggiornato il file Markdown inserendo i link alle immagini che hai fornito nei rispettivi spazi.

---

## **Notazioni Asintotiche (O, Ω, Θ)**
### Descrizione:
- Le notazioni asintotiche sono un linguaggio matematico usato per descrivere l'**efficienza** di un algoritmo in termini di come il suo tempo di esecuzione o il suo utilizzo di memoria crescono all'aumentare della dimensione dell'input (`n`).
- L'obiettivo non è calcolare il tempo esatto, ma analizzare il **tasso di crescita** (o "ordine di grandezza") della funzione di costo, ignorando le costanti e i termini di ordine inferiore.
- Le tre notazioni principali sono:
  1.  **O-Grande**: Fornisce un **limite superiore** (upper bound).
  2.  **Ω-Grande (Omega)**: Fornisce un **limite inferiore** (lower bound).
  3.  **Θ-Grande (Theta)**: Fornisce un **limite stretto** (tight bound).

---

### **O-Grande (O): Limite Superiore**
Rappresenta il **caso peggiore** o una garanzia che la performance di un algoritmo **non sarà mai peggiore** di un certo limite, per input sufficientemente grandi.

![Definizione di O-Grande](https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fajdillhoff.github.io%2Fox-hugo%2F2023-09-26_17-43-51_screenshot.png&f=1&nofb=1&ipt=8dacd1f44682ec57f506dd3c8d8e39f4546a7aaf9dc5a54bf1b807063a7122dc)

#### **Definizione Formale:**
Una funzione `f(n)` appartiene a `O(g(n))` se esistono due costanti positive `c` e `n₀` tali che:
`0 ≤ f(n) ≤ c * g(n)` per ogni `n ≥ n₀`.

In parole semplici: da un certo punto `n₀` in poi, la funzione `f(n)` è sempre al di sotto della funzione `g(n)` moltiplicata per una costante `c`.

---

### **Ω-Grande (Omega): Limite Inferiore**
Rappresenta il **caso migliore** o una garanzia che la performance di un algoritmo **non sarà mai migliore** di un certo limite, per input sufficientemente grandi.

![Definizione di Omega-Grande](https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fajdillhoff.github.io%2Fox-hugo%2F2023-09-26_18-17-07_screenshot.png&f=1&nofb=1&ipt=cbc5d7105b5312b3259dcebbd702743cd156f5c48fbcfb8941d45bcfc0ec318c)

#### **Definizione Formale:**
Una funzione `f(n)` appartiene a `Ω(g(n))` se esistono due costanti positive `c` e `n₀` tali che:
`0 ≤ c * g(n) ≤ f(n)` per ogni `n ≥ n₀`.

In parole semplici: da un certo punto `n₀` in poi, la funzione `f(n)` è sempre al di sopra della funzione `g(n)` moltiplicata per una costante `c`.

---

### **Θ-Grande (Theta): Limite Stretto (Tight Bound)**
Rappresenta una stima **precisa** della crescita di un algoritmo. Si usa quando il caso migliore e il caso peggiore hanno lo stesso ordine di grandezza.

![Definizione di Theta-Grande](https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fajdillhoff.github.io%2Fox-hugo%2F2023-09-26_18-23-25_screenshot.png&f=1&nofb=1&ipt=8421bf06cd390add5a86b1606e4f5456ef317b85f06368a974fdbfa77006b8e3)

#### **Definizione Formale:**
Una funzione `f(n)` appartiene a `Θ(g(n))` se esistono tre costanti positive `c₁`, `c₂` e `n₀` tali che:
`0 ≤ c₁ * g(n) ≤ f(n) ≤ c₂ * g(n)` per ogni `n ≥ n₀`.

In parole semplici: da un certo punto `n₀` in poi, la funzione `f(n)` è "stretta" o "compresa" tra due versioni di `g(n)`, una moltiplicata per `c₁` e una per `c₂`.

---

### **Esempi Pratici**:
- **Ciclo `for` singolo**: Un ciclo che itera `n` volte ha complessità `Θ(n)`. È anche `O(n)` e `Ω(n)`.
  ```cpp
  for (int i = 0; i < n; i++) {
      // operazione a costo costante
  }
  ```
- **Cicli `for` annidati**: Due cicli `for` uno dentro l'altro, entrambi fino a `n`, hanno complessità `Θ(n²)`.
  ```cpp
  for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
          // operazione a costo costante
      }
  }
  ```
- **Quicksort**:
  - **Caso Peggiore**: `O(n²)`.
  - **Caso Migliore**: `Ω(n log n)`.
  - Poiché il limite superiore e inferiore non coincidono, non possiamo descrivere Quicksort con una singola notazione `Θ`.
- **Merge Sort**:
  - **Caso Peggiore e Migliore**: sono entrambi `Θ(n log n)`, quindi l'algoritmo ha un comportamento molto prevedibile.

---

### **Analisi e Scopo**:
1. **Perché usare O-Grande?**
   - Per dare una **garanzia sul caso peggiore**. È la notazione più comune perché ci dice "quanto male possono andare le cose al massimo".

2. **Perché usare Ω-Grande?**
   - Per definire un **limite inferiore invalicabile**. Ci dice "l'algoritmo dovrà fare *almeno* questo lavoro, anche nelle condizioni più fortunate". Utile per dimostrare che un algoritmo è ottimale.

3. **Perché usare Θ-Grande?**
   - Per dare una **descrizione precisa e completa** del comportamento di un algoritmo. Se un algoritmo è `Θ(g(n))`, sappiamo esattamente come la sua performance scala.

---

### **Punti Chiave sulle Notazioni**:
1. Descrivono il **tasso di crescita**, non il tempo di esecuzione esatto. Un algoritmo `O(n)` non è sempre più veloce di uno `O(n²)`, specialmente per `n` piccoli.
2. Le **costanti moltiplicative** vengono ignorate (`5n` è `O(n)`).
3. I **termini di ordine inferiore** vengono ignorati (`n² + 2n + 100` è `O(n²)`).
4. `f(n) = Θ(g(n))` se e solo se `f(n) = O(g(n))` e `f(n) = Ω(g(n))`.

---

### **Tabella di Confronto**:
| **Caratteristica**      | **O-Grande**                | **Ω-Grande (Omega)**      | **Θ-Grande (Theta)**      |
|--------------------------|-----------------------------|---------------------------|---------------------------|
| **Analogia**             | Limite Superiore (Upper Bound) | Limite Inferiore (Lower Bound) | Limite Stretto (Tight Bound) |
| **Significato**          | "Non cresce più velocemente di..." | "Non cresce più lentamente di..." | "Cresce esattamente come..." |
| **Utilizzo Tipico**      | Analisi del **caso peggiore** | Analisi del **caso migliore** | Analisi precisa del comportamento |
| **Esempio**              | Quicksort è `O(n²)`         | Quicksort è `Ω(n log n)`  | Merge Sort è `Θ(n log n)` |