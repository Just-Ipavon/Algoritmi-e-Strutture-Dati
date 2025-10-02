# Fastest Way (Catena di Montaggio)

Il problema della **Fastest Way** consiste nel trovare il percorso più veloce tra due linee di produzione con più stazioni, minimizzando il costo totale. Ogni stazione ha un costo di elaborazione, e spostarsi da una linea all'altra comporta un costo di trasferimento.

## Descrizione del Problema

- **Input**:  
  - Due linee di produzione (`L1` e `L2`) con `n` stazioni ciascuna.
  - Costi di lavorazione `a1[j]` e `a2[j]` per le stazioni `j` sulla linea 1 e 2 rispettivamente.
  - Costi di trasferimento `t1[j]` (da `L2` a `L1`) e `t2[j]` (da `L1` a `L2`) tra le stazioni `j-1` e `j`.
  - Costi di ingresso iniziali `e1` e `e2` per entrare rispettivamente nella linea 1 e 2.
  - Costi di uscita finali `x1` e `x2` per uscire rispettivamente dalla linea 1 e 2.

- **Output**: Il costo minimo per completare la produzione e il percorso ottimale attraverso le linee.

---

## Relazione di Ricorrenza

Il costo cumulativo per arrivare alla stazione `j` su `L1` e `L2` è dato da:

```
f1[j] = min(f1[j-1] + a1[j], f2[j-1] + t2[j] + a1[j])
f2[j] = min(f2[j-1] + a2[j], f1[j-1] + t1[j] + a2[j])
```

Dove:
- `f1[j]`: Costo minimo per raggiungere la stazione `j` su `L1`.
- `f2[j]`: Costo minimo per raggiungere la stazione `j` su `L2`.

### Caso Base

Per iniziare dalla prima stazione:

```
f1[1] = e1 + a1[1]
f2[1] = e2 + a2[1]
```

---

## Algoritmo in C++

Ecco un'implementazione in C++:

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

pair<int, vector<int>> fastestWay(int n, vector<int>& a1, vector<int>& a2, vector<int>& t1, vector<int>& t2, int e1, int e2, int x1, int x2) {
    vector<int> f1(n), f2(n), path1(n), path2(n);

    // Caso base
    f1[0] = e1 + a1[0];
    f2[0] = e2 + a2[0];

    // Relazione di ricorrenza
    for (int j = 1; j < n; ++j) {
        if (f1[j-1] + a1[j] <= f2[j-1] + t2[j] + a1[j]) {
            f1[j] = f1[j-1] + a1[j];
            path1[j] = 1;
        } else {
            f1[j] = f2[j-1] + t2[j] + a1[j];
            path1[j] = 2;
        }

        if (f2[j-1] + a2[j] <= f1[j-1] + t1[j] + a2[j]) {
            f2[j] = f2[j-1] + a2[j];
            path2[j] = 2;
        } else {
            f2[j] = f1[j-1] + t1[j] + a2[j];
            path2[j] = 1;
        }
    }

    // Aggiungi i costi di uscita
    int cost;
    vector<int> path;

    if (f1[n-1] + x1 <= f2[n-1] + x2) {
        cost = f1[n-1] + x1;
        path.push_back(1);
    } else {
        cost = f2[n-1] + x2;
        path.push_back(2);
    }

    // Ricostruisci il percorso
    for (int j = n - 1; j > 0; --j) {
        if (path.back() == 1) {
            path.push_back(path1[j]);
        } else {
            path.push_back(path2[j]);
        }
    }

    reverse(path.begin(), path.end());
    return {cost, path};
}

int main() {
    int n = 6;
    vector<int> a1 = {7, 9, 3, 4, 8, 4};
    vector<int> a2 = {8, 5, 6, 4, 5, 7};
    vector<int> t1 = {2, 3, 1, 3, 4};
    vector<int> t2 = {2, 1, 2, 2, 1};
    int e1 = 2, e2 = 4, x1 = 3, x2 = 2;

    auto result = fastestWay(n, a1, a2, t1, t2, e1, e2, x1, x2);

    cout << "Costo minimo: " << result.first << endl;
    cout << "Percorso ottimale: ";
    for (int station : result.second) {
        cout << station << " ";
    }
    cout << endl;

    return 0;
}
```

---

## Complessità

| Aspetto             | Complessità |
|---------------------|-------------|
| **Temporale**       | `O(n)`     |
| **Spaziale**        | `O(n)`     |

---
