#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

enum Color { White, Grey, Black };

const int INF = 1e9;

template <typename T>
class Node {
public:
    T value;
    Color color = White;
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

    void bfs(T start, ofstream& out) {
        for (auto& [_, node] : nodes) {
            node->color = White;
            node->distance = INF;
            node->parent = nullptr;
        }

        if (!nodes.count(start)) return;

        Node<T>* src = nodes[start];
        src->color = Grey;
        src->distance = 0;

        queue<Node<T>*> q;
        q.push(src);

        while (!q.empty()) {
            Node<T>* u = q.front();
            q.pop();
            out << u->value << " ";

            for (auto& [v, _] : adj[u->value]) {
                Node<T>* neighbor = nodes[v];
                if (neighbor->color == White) {
                    neighbor->color = Grey;
                    neighbor->distance = u->distance + 1;
                    neighbor->parent = u;
                    q.push(neighbor);
                }
            }
            u->color = Color::Black;
        }
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
    out << "\nVisita BFS dal nodo 0:\n";
    g.bfs(0, out);

    cout << "Grafo non orientato caricato, BFS eseguita. Output in output_undirected.txt\n";
    return 0;
}
