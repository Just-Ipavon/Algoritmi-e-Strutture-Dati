# Matrix Chain Multiplication Order

Il problema del **Matrix Chain Multiplication Order** consiste nel determinare il modo ottimale di moltiplicare una sequenza di matrici per minimizzare il numero totale di moltiplicazioni scalari. La sequenza di matrici non viene effettivamente moltiplicata, ma viene calcolato l'ordine più efficiente per farlo.

## Definizione del Problema

Date `n` matrici `A1, A2, ..., An`, con dimensioni `p0 x p1, p1 x p2, ..., pn-1 x pn`, il problema è determinare il modo ottimale di posizionare le parentesi in modo che il costo totale della moltiplicazione sia minimo.

### Formula di Ricorrenza

Per risolvere il problema, utilizziamo la seguente ricorrenza:

- Se `i == j`, allora `m[i][j] = 0` (una singola matrice non richiede moltiplicazioni).
- Se `i < j`, allora:
  ```
  m[i][j] = min(m[i][k] + m[k+1][j] + p[i-1] * p[k] * p[j])
  ```
  Dove `k` varia da `i` a `j-1`.

Qui:
- `m[i][j]` rappresenta il costo minimo per moltiplicare le matrici da `Ai` a `Aj`.
- `p[i-1], p[k], p[j]` sono le dimensioni delle matrici coinvolte.

---

## Algoritmo della Matrix Chain Order

### Approccio

Utilizziamo la programmazione dinamica:
1. Creiamo una tabella `m` dove `m[i][j]` rappresenta il costo minimo per moltiplicare le matrici da `Ai` a `Aj`.
2. Calcoliamo i valori per sotto-problemi più piccoli e li usiamo per risolvere problemi più grandi.

### Codice C++ per Matrix Chain Order

```cpp
#include <iostream>
#include <vector>
#include <limits.h>

// Funzione per calcolare il costo minimo di moltiplicazione delle matrici
int matrixChainOrder(const std::vector<int>& p) {
    int n = p.size() - 1; // Numero di matrici
    std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));
    
    // Lunghezza della catena
    for (int l = 2; l <= n; ++l) {
        for (int i = 0; i < n - l + 1; ++i) {
            int j = i + l - 1;
            dp[i][j] = INT_MAX;
            for (int k = i; k < j; ++k) {
                int cost = dp[i][k] + dp[k+1][j] + p[i] * p[k+1] * p[j+1];
                dp[i][j] = std::min(dp[i][j], cost);
            }
        }
    }

    return dp[0][n - 1];
}

int main() {
    std::vector<int> dimensions = {10, 20, 30, 40, 30}; // Esempio: matrici 10x20, 20x30, 30x40, 40x30
    std::cout << "Costo minimo della moltiplicazione: " 
              << matrixChainOrder(dimensions) << std::endl;
    return 0;
}
```

---

## Complessità

- **Tempo**: `O(n^3)`, a causa della tripla iterazione sulla tabella.
- **Spazio**: `O(n^2)`, poiché utilizziamo una tabella di dimensioni `n x n`.

---

## Esempio

Consideriamo quattro matrici con le seguenti dimensioni:
- `A1`: 10 x 20
- `A2`: 20 x 30
- `A3`: 30 x 40
- `A4`: 40 x 30

Le dimensioni sono rappresentate da:
```
p = {10, 20, 30, 40, 30}
```

L'output del programma mostrerà il costo minimo per moltiplicare queste matrici, calcolato come segue:
1. Risolviamo i sotto-problemi più piccoli.
2. Combiniamo i risultati per calcolare il costo globale minimo.

---
