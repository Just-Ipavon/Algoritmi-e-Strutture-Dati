#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

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
class Graph {
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

    void add_edge(T from, T to, int weight, bool undirected = false) {
        Node<T>* src = add_node(from);
        Node<T>* dest = add_node(to);
        edges.push_back(new Edge<T>(weight, src, dest));
        adj[from].emplace_back(to, weight);
        if (undirected) {
            adj[to].emplace_back(from, weight);
        }
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

    ~Graph() {
        for (auto& [_, n] : nodes) delete n;
        for (auto& e : edges) delete e;
    }
};

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

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
        g.add_edge(u, v, w); // orientato
    }

    out << "Lista di adiacenza:\n";
    g.print_adjacency_list(out);

    cout << "Grafo caricato e salvato in output.txt\n";
    return 0;
}
