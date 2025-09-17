#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

enum Color { White, Grey, Black };

template <typename T>
class Node {
public:
    T value;
    Color color = White;
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
class GraphDirected {
private:
    map<T, Node<T>*> nodes;
    map<T, vector<pair<T, int>>> adj;

    void dfs_visit(Node<T>* node, ostream& out) {
        node->color = Grey;
        out << node->value << " ";
        for (const auto& neighbor : adj[node->value]) {
            Node<T>* next = nodes[neighbor.first];
            if (next->color == White) {
                next->parent = node;
                dfs_visit(next, out);
            }
        }
        node->color = Black;
    }

public:
    vector<Edge<T>*> edges;

    void add_node(T val) {
        if (nodes.count(val) == 0)
            nodes[val] = new Node<T>(val);
    }

    void add_edge(T u, T v, int weight) {
        add_node(u);
        add_node(v);
        Node<T>* nu = nodes[u];
        Node<T>* nv = nodes[v];
        edges.push_back(new Edge<T>(weight, nu, nv));
        adj[u].emplace_back(v, weight); // orientato
    }

    void print_adjacency_list(ostream& out) {
        for (const auto& entry : adj) {
            out << entry.first << " -> ";
            for (const auto& edge : entry.second) {
                out << "(" << edge.first << ", peso: " << edge.second << ") ";
            }
            out << "\n";
        }
    }

    void dfs(T start, ostream& out) {
        for (auto& n : nodes) {
            n.second->color = White;
            n.second->parent = nullptr;
        }

        if (nodes.count(start) == 0) return;

        dfs_visit(nodes[start], out);
    }
};

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");


    int n, m;
    in >> n >> m;

    GraphDirected<int> g;

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        in >> u >> v >> w;
        g.add_edge(u, v, w);
    }

    out << "Lista di adiacenza:\n";
    g.print_adjacency_list(out);

    out << "\nDFS dal nodo 0:\n";
    g.dfs(0, out);

    cout << "Grafo orientato caricato, DFS eseguita. Vedi output_orientato_dfs.txt\n";
    return 0;
}
