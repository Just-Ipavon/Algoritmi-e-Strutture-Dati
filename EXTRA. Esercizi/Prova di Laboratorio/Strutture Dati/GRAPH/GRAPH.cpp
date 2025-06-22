#include <iostream>
#include <unordered_map>
#include <vector>
#include <utility>
#include <limits>
#include <stdexcept>

using namespace std;

template <typename T, typename W = int>
class Graph {
private:
    bool directed;
    unordered_map<T, vector<pair<T, W>>> adj;

public:
    // Costruttore
    Graph(bool is_directed = true) : directed(is_directed) {}

    // Aggiunge un arco (e implicitamente i nodi)
    void add_edge(const T& from, const T& to, const W& weight = 1) {
        adj[from].emplace_back(to, weight);
        if (!directed) {
            adj[to].emplace_back(from, weight);
        }
    }

    // Stampa la rappresentazione del grafo
    void print() const {
        for (const auto& [node, neighbors] : adj) {
            cout << node << " -> ";
            for (const auto& [dest, weight] : neighbors) {
                cout << "(" << dest << ", " << weight << ") ";
            }
            cout << "\n";
        }
    }

    // Restituisce i vicini di un nodo
    const vector<pair<T, W>>& neighbors(const T& node) const {
        static const vector<pair<T, W>> empty;
        auto it = adj.find(node);
        if (it != adj.end()) return it->second;
        return empty;
    }

    // Verifica se un nodo esiste
    bool has_node(const T& node) const {
        return adj.find(node) != adj.end();
    }

    // Verifica se un arco esiste
    bool has_edge(const T& from, const T& to) const {
        auto it = adj.find(from);
        if (it == adj.end()) return false;
        for (const auto& [dest, _] : it->second) {
            if (dest == to) return true;
        }
        return false;
    }
};

// Esempio di utilizzo
int main() {
    Graph<string, int> g(false);  // non orientato

    g.add_edge("A", "B", 5);
    g.add_edge("A", "C", 3);
    g.add_edge("B", "D", 2);

    g.print();

    return 0;
}
