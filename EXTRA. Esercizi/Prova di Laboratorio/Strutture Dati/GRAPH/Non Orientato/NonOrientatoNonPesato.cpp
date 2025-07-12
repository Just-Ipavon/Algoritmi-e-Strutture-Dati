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
    Node<T>* from;
    Node<T>* to;

    Edge(Node<T>* f, Node<T>* t) : from(f), to(t) {}
};

template <typename T>
class GraphUndirected {
private:
    map<T, Node<T>*> nodes;
    map<T, vector<T>> adj;   // lista di adiacenza senza peso

public:
    vector<Edge<T>*> edges;

    void add_node(T val) {
        if (nodes.count(val) == 0)
            nodes[val] = new Node<T>(val);
    }

    void add_edge(T from, T to) {
        add_node(from);
        add_node(to);
        Node<T>* FromNode = nodes[from];
        Node<T>* ToNode = nodes[to];
        edges.push_back(new Edge<T>(FromNode, ToNode));
        adj[from].push_back(to);
        adj[to].push_back(from);   // non orientato
    }

    void print_adjacency_list(ostream& out) {
        for (const auto& entry : adj) {
            out << entry.first << " -> ";
            for (const auto& neighbor : entry.second) {
                out << neighbor << " ";
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
            for (const auto& neighbor_val : adj[u->value]) {
                Node<T>* v = nodes[neighbor_val];
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
    ofstream out("output_ibrido_non_pesato.txt");

    if (!in || !out) {
        cerr << "Errore apertura file.\n";
        return 1;
    }

    int n, m;
    in >> n >> m;

    GraphUndirected<int> g;

    for (int i = 0; i < m; ++i) {
        int u, v;
        in >> u >> v;       // solo due valori: senza peso
        g.add_edge(u, v);
    }

    out << "Lista di adiacenza (non pesata):\n";
    g.print_adjacency_list(out);

    out << "\nBFS dal nodo 0:\n";
    g.bfs(0, out);

    cout << "Grafo non pesato caricato, BFS eseguita. Vedi output_ibrido_non_pesato.txt\n";
    return 0;
}
