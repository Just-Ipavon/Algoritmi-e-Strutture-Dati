#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();
enum color { white, gray, black };

template <typename T>
class Node {
public:
    T value;
    color col = white;
    int distance = INF;
    int discovery = 0;
    int finish = 0;
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
    int time = 0;

public:
    unordered_map<T, Node<T>*> nodes;
    unordered_map<T, vector<pair<T, int>>> adj;
    vector<Edge<T>*> edges;

    ~Graph() {
        for (auto& p : nodes) delete p.second;
        for (Edge<T>* e : edges) delete e;
    }

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

    void print_adjacency_list(ofstream& out) {
        for (typename unordered_map<T, vector<pair<T, int>>>::iterator it = adj.begin(); it != adj.end(); ++it) {
            out << it->first << ": ";
            for (size_t i = 0; i < it->second.size(); ++i) {
                out << "(" << it->second[i].first << ", peso " << it->second[i].second << ") ";
            }
            out << "\n";
        }
    }

    void DFS() {
        for (typename unordered_map<T, Node<T>*>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
            it->second->col = white;
            it->second->parent = nullptr;
        }
        time = 0;
        for (typename unordered_map<T, Node<T>*>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
            if (it->second->col == white) {
                DFS_VISIT(it->second);
            }
        }
    }

    void DFS_VISIT(Node<T>* u) {
        u->col = gray;
        u->discovery = ++time;

        for (size_t i = 0; i < adj[u->value].size(); ++i) {
            T v_val = adj[u->value][i].first;
            Node<T>* v = nodes[v_val];
            if (v->col == white) {
                v->parent = u;
                DFS_VISIT(v);
            }
        }

        u->col = black;
        u->finish = ++time;
    }

    void BFS(T start) {
    for (auto& [_, node] : nodes) {
        node->col = white;
        node->distance = INF;
        node->parent = nullptr;
    }

    Node<T>* source = nodes[start];
    source->col = gray;
    source->distance = 0;
    source->parent = nullptr;

    queue<Node<T>*> q;
    q.push(source);

    while (!q.empty()) {
        Node<T>* u = q.front();
        q.pop();

        for (auto& [v_val, _] : adj[u->value]) {
            Node<T>* v = nodes[v_val];
            if (v->col == white) {
                v->col = gray;
                v->distance = u->distance + 1;
                v->parent = u;
                q.push(v);
            }
        }

        u->col = black;
    }
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

    g.DFS();

    out << "Lista di adiacenza:\n";
    g.print_adjacency_list(out);

    out << "\nTempi di scoperta/fine (DFS):\n";
    for (unordered_map<int, Node<int>*>::iterator it = g.nodes.begin(); it != g.nodes.end(); ++it) {
        out << "Nodo " << it->first << ": discovery=" << it->second->discovery
            << ", finish=" << it->second->finish << "\n";
    }

    out << "\nDistanze dal nodo " << g.nodes.begin()->first << " (BFS):\n";
    g.BFS(1); // oppure qualsiasi nodo di partenza
    out << "\nRisultati BFS:\n";
    for (auto& [key, node] : g.nodes) {
        out << "Nodo " << key << ", distanza: " << node->distance << "\n";
    }

    in.close();
    out.close();

    cout << "Grafo caricato e analizzato, risultati in output.txt\n";
    return 0;
}
