
# Distanza di Editing (Levenshtein e Hamming)

La **distanza di editing** misura la differenza tra due stringhe. Esistono diversi metodi per calcolare questa distanza, i più comuni sono:

- **Distanza di Levenshtein**: misura il numero minimo di operazioni necessarie per trasformare una stringa in un'altra. Le operazioni consentite sono inserimento, eliminazione e sostituzione.
- **Distanza di Hamming**: misura il numero di posizioni in cui le due stringhe di uguale lunghezza differiscono. È limitata a stringhe di uguale lunghezza e permette solo la sostituzione di caratteri.

## 1. Distanza di Levenshtein

La **distanza di Levenshtein** è definita come il numero minimo di operazioni necessarie per trasformare una stringa nell'altra. Le operazioni consentite sono:

- **Inserimento** di un carattere.
- **Eliminazione** di un carattere.
- **Sostituzione** di un carattere con un altro.

### Algoritmo della Distanza di Levenshtein

L'algoritmo può essere implementato usando **programmazione dinamica**. La matrice `dp[i][j]` rappresenta la distanza tra le prime `i` lettere della stringa `X` e le prime `j` lettere della stringa `Y`.

### Codice C++ per la Distanza di Levenshtein

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

// Funzione per calcolare la distanza di Levenshtein
int levenshtein_distance(const std::string& X, const std::string& Y) {
    int m = X.length();
    int n = Y.length();
    
    // Matrice dp per memorizzare i risultati intermedi
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));
    
    // Caso base: se una delle stringhe è vuota
    for (int i = 0; i <= m; ++i) {
        dp[i][0] = i;
    }
    for (int j = 0; j <= n; ++j) {
        dp[0][j] = j;
    }
    
    // Calcolo della distanza di Levenshtein
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];  // Nessuna operazione necessaria
            } else {
                dp[i][j] = 1 + std::min({dp[i - 1][j],    // Eliminazione
                                          dp[i][j - 1],    // Inserimento
                                          dp[i - 1][j - 1] // Sostituzione
                });
            }
        }
    }

    return dp[m][n];  // La distanza finale si trova in dp[m][n]
}

int main() {
    std::string X = "kitten";
    std::string Y = "sitting";
    
    std::cout << "Distanza di Levenshtein tra \"" << X << "\" e \"" << Y << "\" è: " 
              << levenshtein_distance(X, Y) << std::endl;
    
    return 0;
}
```

### Complessità

- **Tempo**: \( O(m * n) \), dove `m` è la lunghezza della stringa `X` e `n` la lunghezza della stringa `Y`.
- **Spazio**: \( O(m * n) \), per memorizzare la matrice.

---

## 2. Distanza di Hamming

La **distanza di Hamming** è una misura della differenza tra due stringhe di uguale lunghezza. La distanza è definita come il numero di posizioni in cui `X[i] != Y[i]`.

### Algoritmo della Distanza di Hamming

La distanza di Hamming tra due stringhe `X` e `Y` di uguale lunghezza è semplicemente il numero di posizioni in cui `X[i] != Y[i]`.

### Codice C++ per la Distanza di Hamming

```cpp
#include <iostream>
#include <string>

using namespace std;

// Funzione per calcolare la distanza di Hamming
int hamming_distance(const string& X, const string& Y) {
    int distance = 0;
    // Calcola la distanza
    for (size_t i = 0; i < X.length(); ++i) {
        if (X[i] != Y[i]) {
            ++distance;
        }
    }
    return distance;
}

int main() {
    string X = "karolin";
    string Y = "kathrin";

    // Controlla se le stringhe hanno la stessa lunghezza
    if (X.length() != Y.length()) {
        cout << "Errore: le stringhe devono avere la stessa lunghezza." << endl;
        return 1; // Esci con codice di errore
    }

    cout << "Distanza di Hamming tra \"" << X << "\" e \"" << Y << "\" è: "
         << hamming_distance(X, Y) << endl;

    return 0;
}
```

### Complessità

- **Tempo**: \( O(n) \), dove `n` è la lunghezza delle stringhe.
- **Spazio**: \( O(1) \), poiché la memoria utilizzata è costante.

---

## Confronto tra Distanza di Levenshtein e Distanza di Hamming

| Caratteristica            | Distanza di Levenshtein        | Distanza di Hamming           |
|---------------------------|--------------------------------|-------------------------------|
| **Tipo di operazioni**    | Inserimento, Eliminazione, Sostituzione | Sostituzione                 |
| **Applicabilità**          | Stringhe di qualsiasi lunghezza | Solo per stringhe di uguale lunghezza |
| **Tempo di calcolo**       | \( O(m * n) \)            | \( O(n) \)                    |
| **Spazio**                 | \( O(m * n) \)            | \( O(1) \)                    |
| **Flessibilità**           | Alta, applicabile a stringhe di lunghezze diverse | Limitata a stringhe di lunghezza uguale |

---

## Conclusioni

- **Distanza di Levenshtein** è più flessibile, poiché può essere applicata a stringhe di lunghezza diversa e supporta più operazioni (inserimento, eliminazione, sostituzione).
- **Distanza di Hamming** è più semplice e veloce, ma è limitata a stringhe della stessa lunghezza e permette solo la sostituzione dei caratteri.
