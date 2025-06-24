#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

enum class Color { White, Grey, Black };

template <typename T>
class Node {
public:
    T value;
    Color color = Color::White;
    int distance = -1;
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
class GraphUndirected {
private:
    unordered_map<T, Node<T>*> nodes;
    unordered_map<T, vector<pair<T, int>>> adj;

    bool dfs_cycle(T u, T parent, unordered_set<T>& visited) {
        visited.insert(u);
        for (auto& [v, _] : adj[u]) {
            if (v == parent) continue;
            if (visited.count(v)) return true; // ciclo trovato
            if (dfs_cycle(v, u, visited)) return true;
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
        adj[from].emplace_back(to, weight);
        adj[to].emplace_back(from, weight); // non orientato
    }

    void print_adjacency_list(ostream& out) const {
        for (const auto& [node, neighbors] : adj) {
            out << node << " -> ";
            for (const auto& [dest, w] : neighbors) {
                out << "(" << dest << ", peso: " << w << ") ";
            }
            out << "\n";
        }
    }

    void bfs(T start, ofstream& out) {
        if (!nodes.count(start)) {
            out << "Nodo di partenza non presente nel grafo.\n";
            return;
        }

        for (auto& [_, node] : nodes) {
            node->color = Color::White;
            node->distance = -1;
            node->parent = nullptr;
        }

        Node<T>* src = nodes[start];
        src->color = Color::Grey;
        src->distance = 0;

        queue<Node<T>*> q;
        q.push(src);

        out << "Visita BFS dal nodo " << start << ":\n";

        while (!q.empty()) {
            Node<T>* u = q.front();
            q.pop();
            out << u->value << " ";

            for (auto& [v, _] : adj[u->value]) {
                Node<T>* neighbor = nodes[v];
                if (neighbor->color == Color::White) {
                    neighbor->color = Color::Grey;
                    neighbor->distance = u->distance + 1;
                    neighbor->parent = u;
                    q.push(neighbor);
                }
            }
            u->color = Color::Black;
        }
        out << "\n";
    }

    bool is_tree() {
        if (edges.size() != nodes.size() - 1) return false;
        unordered_set<T> visited;
        if (nodes.empty()) return false;
        T start = nodes.begin()->first;
        if (dfs_cycle(start, start, visited)) return false;
        return visited.size() == nodes.size();
    }

    bool is_binary_tree() {
        if (!is_tree()) return false;
        for (auto& [node, neighbors] : adj) {
            if (neighbors.size() > 3) return false; // max 3 vicini in grafo non orientato (1 genitore + 2 figli)
        }
        return true;
    }

    ~GraphUndirected() {
        for (auto& [_, n] : nodes) delete n;
        for (auto& e : edges) delete e;
    }
};

int main() {
    ifstream in("inputNonOrientato.txt");
    ofstream out("output_undirected.txt");

    if (!in || !out) {
        cerr << "Errore apertura file.\n";
        return 1;
    }

    int n, m;
    in >> n >> m;

    GraphUndirected<int> g;

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        in >> u >> v >> w;
        g.add_edge(u, v, w);
    }

    out << "Lista di adiacenza (grafo non orientato):\n";
    g.print_adjacency_list(out);

    g.bfs(0, out);

    bool tree = g.is_tree();
    bool binary_tree = g.is_binary_tree();

    out << "\nIl grafo è un albero? " << (tree ? "Sì" : "No") << "\n";
    out << "L'albero è binario? " << (binary_tree ? "Sì" : "No") << "\n";

    cout << "Elaborazione completata. Risultati scritti in output_undirected.txt\n";

    return 0;
}
