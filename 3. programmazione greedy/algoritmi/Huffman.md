
# Codici di Huffman

I **Codici di Huffman** sono un metodo di compressione dati senza perdita che assegna codici binari di lunghezza variabile ai simboli di un alfabeto in base alla loro frequenza. I simboli più frequenti ricevono codici più brevi, mentre quelli meno frequenti ricevono codici più lunghi.

---

## Descrizione del Problema

- **Input**: Un insieme di simboli `S = {s1, s2, ..., sn}` con frequenze associate `f = {f1, f2, ..., fn}`, dove `n` è il numero di simboli.
- **Output**: Un albero binario ottimale che rappresenta i codici di Huffman, con il costo totale minimo della compressione.

---

## Lemma della Sottostruttura Ottima

Un problema soddisfa la **sottostruttura ottima** se la soluzione ottima complessiva può essere costruita combinando le soluzioni ottime dei sottoproblemi.

### Dimostrazione
Per costruire un albero ottimale:
1. Supponiamo che `T` sia l'albero ottimale per i simboli di `S`.
2. Se rimuoviamo i due simboli meno frequenti, diciamo `si` e `sj`, il sottoalbero che li rappresenta è anch'esso ottimale.
3. Se un sottoalbero non fosse ottimale, potremmo sostituirlo con uno migliore, contraddicendo l'assunzione che `T` è ottimale.

---

## Lemma della Greedy Choice

Il metodo di Huffman utilizza una scelta greedy per combinare i due simboli meno frequenti in ogni iterazione.

### Dimostrazione
1. Sia `si` e `sj` i simboli con le frequenze minime.
2. La scelta di combinarli minimizza il costo complessivo, poiché contribuisce al costo totale della compressione in modo proporzionale alla somma delle loro frequenze.

---

## Algoritmo di Huffman

L'algoritmo utilizza una coda di priorità per combinare i simboli meno frequenti iterativamente.

### Passi:
1. Inserisci tutti i simboli con le loro frequenze in una coda di priorità (min-heap).
2. Fino a quando rimane più di un elemento nella coda:
   - Estrai i due elementi con le frequenze minime.
   - Combina i due elementi in un nuovo nodo, con frequenza uguale alla somma delle due.
   - Inserisci il nuovo nodo nella coda.
3. L'ultimo elemento nella coda rappresenta l'albero di Huffman.

### Implementazione in C++:
```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

struct Node {
    char symbol;
    int freq;
    Node* left;
    Node* right;

    Node(char s, int f) : symbol(s), freq(f), left(nullptr), right(nullptr) {}
};

// Comparator per la coda di priorità
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

// Funzione per costruire l'albero di Huffman
Node* buildHuffmanTree(const vector<char>& symbols, const vector<int>& freqs) {
    priority_queue<Node*, vector<Node*>, Compare> minHeap;

    for (size_t i = 0; i < symbols.size(); ++i) {
        minHeap.push(new Node(symbols[i], freqs[i]));
    }

    while (minHeap.size() > 1) {
        Node* left = minHeap.top(); minHeap.pop();
        Node* right = minHeap.top(); minHeap.pop();

        Node* combined = new Node('\0', left->freq + right->freq);
        combined->left = left;
        combined->right = right;

        minHeap.push(combined);
    }

    return minHeap.top();
}

// Funzione per stampare i codici di Huffman
void printHuffmanCodes(Node* root, const string& code) {
    if (!root) return;

    if (root->symbol != '\0') {
        cout << root->symbol << ": " << code << endl;
    }

    printHuffmanCodes(root->left, code + "0");
    printHuffmanCodes(root->right, code + "1");
}

int main() {
    vector<char> symbols = {'A', 'B', 'C', 'D', 'E'};
    vector<int> freqs = {5, 9, 12, 13, 16};

    Node* root = buildHuffmanTree(symbols, freqs);

    cout << "Codici di Huffman:" << endl;
    printHuffmanCodes(root, "");

    return 0;
}

```
---

### Complessità
- **Tempo**: \( O(n log n) \), dove `n` il numero di simboli.
- **Spazio**: \( O(n) \), poiché la memoria utilizzata dipende dai simboli.

---

### Esempio

#### Input:
```
Simboli: {'A', 'B', 'C', 'D', 'E'}

Frequenze: {5, 9, 12, 13, 16}
```

#### Output:
```
Codici di Huffman:

A: 1100

B: 1101

C: 10

D: 111

E: 0
```

---
