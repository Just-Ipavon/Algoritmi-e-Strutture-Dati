# Algoritmo della LCS (Longest Common String)

![Simulatore LCS Online](https://lcs-demo.sourceforge.net/)

La **Longest Common String** (LCS) è una sequenza di caratteri che appare in entrambi i sequenze date (senza necessariamente essere consecutiva, ma mantenendo l'ordine). 
L'obiettivo dell'algoritmo LCS è trovare la lunghezza della sequenza comune più lunga tra due sequenze date.

## Approccio alla Soluzione

La soluzione più efficiente per il problema della LCS utilizza la programmazione dinamica. Creiamo una matrice bidimensionale `dp` dove `dp[i][j]` rappresenta la lunghezza della LCS delle sottosequenze `X[0...i-1]` e `Y[0...j-1]`.

#### Relazione di ricorrenza:
- Se `X[i-1] == Y[j-1]`, allora `dp[i][j] = dp[i-1][j-1] + 1`.
- Se `X[i-1] != Y[j-1]`, allora `dp[i][j] = max(dp[i-1][j], dp[i][j-1])`.

### Esempio in C++:

```cpp
#include <iostream>
#include <vector>
#include <string>

int lcsLength(const std::string& X, const std::string& Y) {
    int m = X.size();
    int n = Y.size();
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));

    // Calcoliamo la matrice dp
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;  // Se i caratteri sono uguali
            } else {
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);  // Se sono diversi
            }
        }
    }

    return dp[m][n];  // La lunghezza della LCS
}

int main() {
    std::string X = "ABCBDAB";
    std::string Y = "BDCABB";
    std::cout << "La lunghezza della LCS è: " << lcsLength(X, Y) << std::endl;
    return 0;
}
```


## Confronto degli Approcci

| Approccio              | Complessità Temporale | Complessità Spaziale |
|------------------------|-----------------------|----------------------|
| Programmazione Dinamica | \( O(m * n) \)     | \( O(m * n) \)    |



# Teorema della Sottostruttura Ottima - LCS

Il **Teorema della Sottostruttura Ottima** per il problema della **Longest Common Subsequence (LCS)** afferma che:

**"La soluzione ottima del problema LCS su due stringhe può essere costruita utilizzando le soluzioni ottime dei sotto-problemi."**

In altre parole, la sequenza comune più lunga tra due stringhe `X` e `Y` può essere ottenuta combinando le sequenze comuni più lunghe di sotto-sequenze di `X` e `Y`.

## Formulazione del Teorema

Dato un problema LCS per due stringhe `X = X[0...m-1]` e `Y = Y[0...n-1]`, la soluzione ottima può essere descritta ricorsivamente come segue:

### Caso Base:
- Se una delle due stringhe è vuota (`m = 0` o `n = 0`), la LCS è vuota:
  
  LCS(X, Y) = 0
  

### Passo Ricorsivo:
- Se `X[m-1] == Y[n-1]`, il carattere finale delle due stringhe è parte della LCS. In questo caso, la LCS delle due stringhe è data da:

  LCS(X[0...m-2], Y[0...n-2]) + 1

- Se `X[m-1] != Y[n-1]`, allora l'elemento finale non è parte della LCS. In tal caso, la LCS è il massimo tra la LCS delle sottostrutture `X[0...m-2]` e `Y[0...n-1]` e la LCS delle sottostrutture `X[0...m-1]` e `Y[0...n-2]`:

  LCS(X[0...m-2], Y[0...n-1])  or  LCS(X[0...m-1], Y[0...n-2])

## Riflessione sul Teorema

Il teorema della sottostruttura ottima per l'LCS implica che possiamo risolvere il problema in modo ricorsivo e che la soluzione di un problema più grande (la LCS delle stringhe complete) dipende dalle soluzioni di problemi più piccoli (LCS delle sottostringhe). Questo rende l'LCS un problema ideale per la programmazione dinamica, poiché possiamo memorizzare i risultati dei sotto-problemi in una matrice per evitare calcoli ridondanti.

## Esempio Esplicativo

Consideriamo le due stringhe `X = "ABCBDAB"` e `Y = "BDCABB"`. Per calcolare la LCS di queste due stringhe, possiamo suddividere il problema in sotto-problemi più piccoli:

- Se `X[6] == Y[5]` (cioè, `B == B`), la LCS include questo carattere, e la soluzione sarà data dalla LCS delle sottostringhe `X[0...5]` e `Y[0...4]`.
- Se `X[6] != Y[5]`, dobbiamo confrontare le LCS delle sottostringhe `X[0...5]` e `Y[0...5]`, e così via.

Combinando i risultati di questi sotto-problemi, otteniamo la LCS finale.
