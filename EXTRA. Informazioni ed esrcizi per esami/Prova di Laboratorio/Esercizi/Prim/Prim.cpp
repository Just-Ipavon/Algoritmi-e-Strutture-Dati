#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <functional>

using namespace std;

enum class Color { White, Grey, Black };

const int INF = 1e9;

template <typename T>
class Node {
public:
    T value;
    Color color = Color::White;
    int distance = INF;
    Node<T>* parent = nullptr;

    Node(T val) : value(val) {}
};

template <typename T>
class Edge {
public:
    int weight;
    Node<T>* from;
    Node<T>* to;

    Edge(int w, Node<T>* f, Node<T>* t)
        : weight(w), from(f), to(t) {}
};

template <typename T>
class GraphUndirected {
private:
    unordered_map<T, Node<T>*> nodes;
    unordered_map<T, vector<pair<T, int>>> adj;

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

    void prim(T start, ofstream& out) {
        // Inizializza i nodi
        for (auto& [_, node] : nodes) {
            node->distance = INF;
            node->parent = nullptr;
            node->color = Color::White;
        }

        if (!nodes.count(start)) {
            out << "Nodo iniziale non trovato\n";
            return;
        }

        auto cmp = [](Node<T>* a, Node<T>* b) { return a->distance > b->distance; };
        priority_queue<Node<T>*, vector<Node<T>*>, decltype(cmp)> pq(cmp);

        Node<T>* src = nodes[start];
        src->distance = 0;
        pq.push(src);

        int total_weight = 0;

        while (!pq.empty()) {
            Node<T>* u = pq.top();
            pq.pop();

            if (u->color == Color::Black) continue; // già visitato

            u->color = Color::Black;
            total_weight += u->distance;

            if (u->parent != nullptr) {
                out << "Arco: (" << u->parent->value << " - " << u->value << ") peso: " << u->distance << "\n";
            } else {
                out << "Nodo iniziale: " << u->value << "\n";
            }

            for (auto& [v, w] : adj[u->value]) {
                Node<T>* neighbor = nodes[v];
                if (neighbor->color != Color::Black && w < neighbor->distance) {
                    neighbor->distance = w;
                    neighbor->parent = u;
                    pq.push(neighbor);
                }
            }
        }
        out << "\nPeso totale MST: " << total_weight << "\n";
    }

    ~GraphUndirected() {
        for (auto& [_, n] : nodes) delete n;
        for (auto& e : edges) delete e;
    }
};

int main() {
    ifstream in("input.txt");
    ofstream out("output_prim.txt");

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
    out << "\nAlbero di copertura minimo (Prim) a partire dal nodo 0:\n";
    g.prim(0, out);

    cout << "Grafo non orientato caricato, MST Prim calcolata. Output in output_prim.txt\n";
    return 0;
}
