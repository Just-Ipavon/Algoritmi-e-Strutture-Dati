#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <map>
#include <utility>

using namespace std;

const int WHITE = 0;
const int GREY = 1;
const int BLACK = 2;

template<typename T>
class Node {
public:
    T val;
    int discovery = 0;
    int finish = 0;
    int color = WHITE;
    Node<T>* parent = nullptr;

    Node(T val) : val(val) {}
};

template<typename T>
class Edge {
public:
    T weight;
    Node<T>* source;
    Node<T>* destination;

    Edge(T weight, Node<T>* source, Node<T>* destination)
        : weight(weight), source(source), destination(destination) {}
};

template<typename T>
class Graph {
public:
    int time = 0;
    vector<Node<T>*> nodes;
    vector<Edge<T>*> edges;
    unordered_map<T, Node<T>*> node_map; // 🔁 lookup rapido dei nodi
    map<T, vector<pair<T, T>>> adj;      // Lista di adiacenza con pesi

    Node<T>* get_or_create_node(T val) {
        if (node_map.find(val) == node_map.end()) {
            Node<T>* node = new Node<T>(val);
            node_map[val] = node;
            nodes.push_back(node);
        }
        return node_map[val];
    }

    void add_edge(T weight, T source_val, T dest_val) {
        Node<T>* source = get_or_create_node(source_val);
        Node<T>* dest = get_or_create_node(dest_val);

        Edge<T>* edge = new Edge<T>(weight, source, dest);
        edges.push_back(edge);

        adj[source_val].emplace_back(dest_val, weight);
        // Per grafo non orientato, aggiungi anche:
        // adj[dest_val].emplace_back(source_val, weight);
    }

    void dfs() {
        for (Node<T>* u : nodes) {
            u->color = WHITE;
            u->parent = nullptr;
        }
        for (Node<T>* u : nodes) {
            if (u->color == WHITE) {
                dfs_visit(u);
            }
        }
    }

    void dfs_visit(Node<T>* u) {
        u->color = GREY;
        u->discovery = ++time;

        for (auto& [v_val, _] : adj[u->val]) {
            Node<T>* v = node_map[v_val];
            if (v->color == WHITE) {
                v->parent = u;
                dfs_visit(v);
            }
        }

        u->color = BLACK;
        u->finish = ++time;
    }

    ~Graph() {
        for (auto node : nodes) delete node;
        for (auto edge : edges) delete edge;
    }
};



int main() {
    ifstream in("input.txt");
    int num_nodes, num_edges;
    in >> num_nodes >> num_edges;

    Graph<int> g;

    for (int i = 0; i < num_edges; i++) {
        int src, dst, weight;
        in >> src >> dst >> weight;
        g.add_edge(weight, src, dst);
    }
    in.close();

    g.dfs();

    ofstream out("output.txt");
    for (Node<int>* node : g.nodes) {
        out << "Nodo: " << node->val
            << ", tempo di scoperta: " << node->discovery
            << ", tempo di completamento: " << node->finish << endl;
    }
    out.close();

    return 0;
}
