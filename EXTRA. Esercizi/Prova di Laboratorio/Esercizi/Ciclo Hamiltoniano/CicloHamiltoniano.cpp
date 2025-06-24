#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;

enum class Color { White, Grey, Black };

template <typename T>
class Node {
public:
    T value;
    Color color = Color::White;
    Node<T>* parent = nullptr;

    Node(T val) : value(val) {}
};

template <typename T>
class Edge {
public:
    int weight;
    Node<T>* from;
    Node<T>* to;

    Edge(int w, Node<T>* f, Node<T>* t) : weight(w), from(f), to(t) {}
};

template <typename T>
class Graph {
private:
    unordered_map<T, Node<T>*> nodes;
    unordered_map<T, vector<T>> adj;

    bool hamiltonian_cycle_util(T curr, vector<T>& path, unordered_map<T, bool>& visited) {
        if (path.size() == nodes.size()) {
            // Controlla se l'ultimo nodo è adiacente al primo per chiudere il ciclo
            for (T neighbor : adj[curr]) {
                if (neighbor == path[0]) {
                    path.push_back(path[0]);
                    return true;
                }
            }
            return false;
        }

        for (T neighbor : adj[curr]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                path.push_back(neighbor);

                if (hamiltonian_cycle_util(neighbor, path, visited))
                    return true;

                // backtrack
                visited[neighbor] = false;
                path.pop_back();
            }
        }

        return false;
    }

public:
    vector<Edge<T>*> edges;

    Node<T>* add_node(T val) {
        if (!nodes.count(val)) {
            nodes[val] = new Node<T>(val);
        }
        return nodes[val];
    }

    void add_edge(T from, T to, int weight) {
        Node<T>* src = add_node(from);
        Node<T>* dest = add_node(to);
        edges.push_back(new Edge<T>(weight, src, dest));
        adj[from].push_back(to);
    }

    void print_adjacency_list(ostream& out) const {
        for (const auto& [node, neighbors] : adj) {
            out << node << " -> ";
            for (const auto& dest : neighbors) {
                out << dest << " ";
            }
            out << "\n";
        }
    }

    void find_and_print_hamiltonian_cycle(T start, ofstream& out) {
        vector<T> path;
        unordered_map<T, bool> visited;

        for (auto& [key, _] : nodes) {
            visited[key] = false;
        }

        visited[start] = true;
        path.push_back(start);

        if (hamiltonian_cycle_util(start, path, visited)) {
            out << "Ciclo Hamiltoniano trovato:\n";
            for (auto& v : path) {
                out << v << " ";
            }
            out << "\n";
        } else {
            out << "Nessun ciclo Hamiltoniano trovato.\n";
        }
    }

    ~Graph() {
        for (auto& [_, n] : nodes) delete n;
        for (auto& e : edges) delete e;
    }
};

int main() {
    ifstream in("input.txt");
    ofstream out("output_directed.txt");

    if (!in || !out) {
        cerr << "Errore apertura file.\n";
        return 1;
    }

    int n, m;
    in >> n >> m;

    Graph<int> g;

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        in >> u >> v >> w;
        g.add_edge(u, v, w); // grafo orientato
    }

    out << "Lista di adiacenza (grafo orientato):\n";
    g.print_adjacency_list(out);

    out << "\nRicerca ciclo Hamiltoniano a partire da nodo 0:\n";
    g.find_and_print_hamiltonian_cycle(0, out);

    cout << "Grafo caricato, ciclo Hamiltoniano cercato. Output in output_directed.txt\n";
    return 0;
}
