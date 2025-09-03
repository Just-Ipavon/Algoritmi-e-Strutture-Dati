#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

const int INF = 1e9;

enum Color { White, Grey, Black };

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

    Edge(int w, Node<T>* f, Node<T>* t) : weight(w), from(f), to(t) {}
};

template <typename T>
class GraphUndirected {
private:
    map<T, Node<T>*> nodes;
    map<T, vector<pair<T, int>>> adj;

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
        adj[u].emplace_back(v, weight);
        adj[v].emplace_back(u, weight); // non orientato
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

    void bfs(T start, ofstream& out) {
        for (auto& n : nodes) {
            n.second->color = White;
            n.second->distance = INF;
            n.second->parent = nullptr;
        }

        if (nodes.count(start) == 0) return;

        Node<T>* src = nodes[start];
        src->color = Grey;
        src->distance = 0;

        queue<Node<T>*> q;
        q.push(src);

        while (!q.empty()) {
            Node<T>* u = q.front();
            q.pop();
            out << u->value << " ";
            for (const auto& neighbor : adj[u->value]) {
                Node<T>* v = nodes[neighbor.first];
                if (v->color == White) {
                    v->color = Grey;
                    v->distance = u->distance + 1;
                    v->parent = u;
                    q.push(v);
                }
            }
            u->color = Black;
        }
    }

    ~GraphUndirected() {
        for (auto& e : edges) delete e;
        for (auto& p : nodes) delete p.second;
    }
};

int main() {
    ifstream in("input.txt");
    ofstream out("output_ibrido.txt");

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

    out << "Lista di adiacenza:\n";
    g.print_adjacency_list(out);

    out << "\nBFS dal nodo 0:\n";
    g.bfs(0, out);

    cout << "Grafo caricato, BFS eseguita. Vedi output_ibrido.txt\n";
    return 0;
}
