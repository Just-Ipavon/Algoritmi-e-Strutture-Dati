# Algoritmo di Fibonacci

La sequenza di Fibonacci è definita come:

- Caso base: `F(0) = 0`, `F(1) = 1`
- Relazione di ricorrenza: `F(n) = F(n-1) + F(n-2)` per `n >= 2`.

La programmazione dinamica (DP) è una tecnica che permette di calcolare la sequenza in modo efficiente memorizzando i risultati intermedi per evitare calcoli ridondanti.

## Approcci alla Soluzione

### 1. Memoization (Top-Down)
Nell'approccio top-down, utilizziamo la ricorsione e una struttura dati per memorizzare i risultati intermedi.

Esempio in C++:
```cpp
#include <iostream>
#include <vector>

int fibonacciMemo(int n, std::vector<int>& memo) {
    if (n <= 1) {
        return n;
    }
    if (memo[n] != -1) {
        return memo[n];
    }
    memo[n] = fibonacciMemo(n - 1, memo) + fibonacciMemo(n - 2, memo);
    return memo[n];
}

int main() {
    int n = 10; // Cambia questo valore per calcolare altri termini
    std::vector<int> memo(n + 1, -1);
    std::cout << "Fibonacci(" << n << ") = " << fibonacciMemo(n, memo) << std::endl;
    return 0;
}
```

### 2. Divide et Impera
Nell'approccio Divide et Impera, calcoliamo i valori partendo dai casi base e stampiamo solo il valore alla posizione richiesta.

Esempio in C++:
```cpp
#include <iostream>

int fibonacciDei(int n) {
    if (n <= 1) 
        return 1;
    int num = fibonacciDei(n-1) + fibonacciDei(n-2);
    return num;
}

int main() {
    int n = 10; // Cambia questo valore per calcolare altri termini
    std::cout << "Fibonacci(" << n << ") = " << fibonacciDei(n) << std::endl;
    return 0;
}
```

### 3. Ottimizzazione dello Spazio
Possiamo ottimizzare ulteriormente l'approccio bottom-up utilizzando solo due variabili invece di un array, poiché ogni valore dipende solo dai due precedenti.

Esempio in C++:
```cpp
#include <iostream>

int fibonacciOptimized(int n) {
    if (n <= 1) {
        return n;
    }
    int prev2 = 0, prev1 = 1;
    int current;
    for (int i = 2; i <= n; ++i) {
        current = prev1 + prev2;
        prev2 = prev1;
        prev1 = current;
    }
    return current;
}

int main() {
    int n = 10; // Cambia questo valore per calcolare altri termini
    std::cout << "Fibonacci(" << n << ") = " << fibonacciOptimized(n) << std::endl;
    return 0;
}
```

## Confronto degli Approcci

| Approccio             | Complessità Temporale | Complessità Spaziale |
|-----------------------|-----------------------|-----------------------|
| Memoization (Top-Down) | \( O(n) \)           | \( O(n) \)           |
| Divede et Impera       | \( O(n) \)           | \( O(n) \)           |
| Ottimizzato            | \( O(n) \)           | \( O(1) \)           |

## Conclusioni
L'algoritmo di Fibonacci può essere ottimizzato utilizzando tecniche di programmazione dinamica. La scelta dell'approccio dipende dalle esigenze specifiche: 
- **Memoization** è utile quando il problema può essere facilmente strutturato in modo ricorsivo.
- **Divide et Impera** è preferibile per un controllo su un singolo valore.
- **Ottimizzazione dello spazio** è ideale per risparmiare memoria senza sacrificare la velocità.
