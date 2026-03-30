#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

enum Color { White, Grey, Black };

// Classe Node template, includiamo i pesi
template <class T>
class Node {
public:
    T val;
    // pair <nodo di destinazione, peso>
    vector<pair<Node<T>*, int>> adj;
    Color color;
    int dist; // Passi nella BFS

    Node(T val) : val(val), color(White), dist(-1) {}

    // Grafo non orientato, colleghiamo in entrambe le direzioni
    void add_edge(Node<T>* v, int weight) {
        adj.push_back({v, weight});
        v->adj.push_back({this, weight}); 
    }
};

template <class T>
class Graph {
public:
    vector<Node<T>*> nodes;

    void add_node(T val) {
        nodes.push_back(new Node<T>(val));
    }

    void add_edge(T u, T v, int weight) {
        Node<T>* node_u = nullptr;
        Node<T>* node_v = nullptr;

        for (auto node : nodes) {
            if (node->val == u) node_u = node;
            if (node->val == v) node_v = node;
        }

        if (node_u && node_v) {
            node_u->add_edge(node_v, weight); 
        }
    }

    void reset() {
        for (auto node : nodes) {
            node->color = White;
            node->dist = -1;
        }
    }

    void bfs(T start_val, ostream& out) {
        Node<T>* start_node = nullptr;
        for (auto node : nodes) {
            if (node->val == start_val) {
                start_node = node;
                break;
            }
        }

        if (!start_node) return;

        reset();
        queue<Node<T>*> q;
        start_node->color = Grey;
        start_node->dist = 0;
        q.push(start_node);

        while (!q.empty()) {
            Node<T>* u = q.front();
            q.pop();
            out << u->val << " ";
            
            for (auto edge : u->adj) {
                Node<T>* v = edge.first;
                if (v->color == White) {
                    v->color = Grey;
                    v->dist = u->dist + 1;
                    q.push(v);
                }
            }
            u->color = Black;
        }
    }

    void print(ostream& out) {
        for (auto node : nodes) {
            out << node->val << " -> ";
            for (auto edge : node->adj) {
                out << "(" << edge.first->val << ", w:" << edge.second << ") ";
            }
            out << "\n";
        }
    }
};

int main() {
    ifstream in("input.txt");
    int n, m;
    
    if (!(in >> n >> m)) {
        n = 5; m = 4;
    }

    Graph<int> g;
    for (int i = 0; i < n; ++i) {
        g.add_node(i);
    }

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        if(in >> u >> v >> w) g.add_edge(u, v, w);
        else if (i==0) { 
            g.add_edge(0,1,10); g.add_edge(1,2,5); 
            break; 
        }
    }

    ofstream out("output.txt");
    out << "Lista di adiacenza (Pesata):\n";
    g.print(out);

    out << "\nBFS dal nodo 0:\n";
    g.bfs(0, out);

    cout << "Grafo pesato: BFS completata con classe Node.\n";
    return 0;
}
