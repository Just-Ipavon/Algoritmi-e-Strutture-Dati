#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

// Manteniamo i colori come richiesto
enum Color { White, Grey, Black };

// Classe Node template, più intuitiva
template <class T>
class Node {
public:
    T val;
    vector<Node<T>*> adj;
    Color color;
    int dist; // per la BFS

    Node(T val) : val(val), color(White), dist(-1) {}

    // Grafo non orientato, colleghiamo in entrambe le direzioni
    void add_edge(Node<T>* v) {
        adj.push_back(v);
        v->adj.push_back(this); 
    }
};

template <class T>
class Graph {
public:
    vector<Node<T>*> nodes;

    void add_node(T val) {
        nodes.push_back(new Node<T>(val));
    }

    void add_edge(T u, T v) {
        Node<T>* node_u = nullptr;
        Node<T>* node_v = nullptr;

        for (auto node : nodes) {
            if (node->val == u) node_u = node;
            if (node->val == v) node_v = node;
        }

        if (node_u && node_v) {
            node_u->add_edge(node_v); 
        }
    }

    void reset() {
        for (auto node : nodes) {
            node->color = White;
            node->dist = -1;
        }
    }

    // BFS classica iterativa
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

            for (Node<T>* v : u->adj) {
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
            for (auto neighbor : node->adj) {
                out << neighbor->val << " ";
            }
            out << "\n";
        }
    }
};

int main() {
    ifstream in("input.txt");
    int n, m;
    
    // Fallback su dimensioni fisse per test se il file manca o non è formattato
    if (!(in >> n >> m)) {
        n = 5; m = 4;
    }

    Graph<int> g;
    for (int i = 0; i < n; ++i) {
        g.add_node(i);
    }

    for (int i = 0; i < m; ++i) {
        int u, v;
        if(in >> u >> v) g.add_edge(u, v);
        // Test di fallback
        else if (i==0) { 
            g.add_edge(0,1); g.add_edge(1,2); g.add_edge(2,3); g.add_edge(3,4); 
            break;
        }
    }

    ofstream out("output.txt");
    out << "Lista di adiacenza:\n";
    g.print(out);

    out << "\nBFS dal nodo 0:\n";
    g.bfs(0, out);

    cout << "Grafo non pesato: BFS completata con classe Node.\n";
    return 0;
}
