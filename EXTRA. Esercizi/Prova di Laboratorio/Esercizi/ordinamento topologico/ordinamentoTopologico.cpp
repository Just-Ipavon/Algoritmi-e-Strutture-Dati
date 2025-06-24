#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <unordered_map>

using namespace std;

const int WHITE = 0;
const int GREY = 1;
const int BLACK = 2;

template<typename T>
class Node {
public:
    T val;
    int color = WHITE;
    int discovery = 0;
    int finish = 0;
    Node<T>* parent = nullptr;

    Node(T val) : val(val) {}
};

template<typename T>
class Graph {
private:
    int time = 0;
    unordered_map<T, Node<T>*> node_map;
    unordered_map<T, vector<T>> adj;

public:
    ~Graph() {
        for (auto& [_, node] : node_map) delete node;
    }

    void add_edge(T from, T to) {
        if (!node_map.count(from)) node_map[from] = new Node<T>(from);
        if (!node_map.count(to)) node_map[to] = new Node<T>(to);
        adj[from].push_back(to);
    }

    void topological_sort(ofstream& out) {
        stack<Node<T>*> st;
        for (auto& [_, node] : node_map) {
            node->color = WHITE;
            node->parent = nullptr;
        }
        time = 0;
        for (auto& [_, node] : node_map) {
            if (node->color == WHITE) dfs_visit(node, st);
        }

        while (!st.empty()) {
            out << "Nodo in ordine topologico: " << st.top()->val << "\n";
            st.pop();
        }
    }

private:
    void dfs_visit(Node<T>* u, stack<Node<T>*>& st) {
        u->color = GREY;
        u->discovery = ++time;

        for (T v_val : adj[u->val]) {
            Node<T>* v = node_map[v_val];
            if (v->color == WHITE) {
                v->parent = u;
                dfs_visit(v, st);
            }
        }

        u->color = BLACK;
        u->finish = ++time;
        st.push(u);
    }
};


int main() {
    ifstream in("input.txt");
    ofstream out("outputtop.txt");

    if (!in || !out) {
        cerr << "Errore apertura file." << endl;
        return 1;
    }

    int n, m;
    in >> n >> m;

    Graph<int> g;
    for (int i = 0; i < m; ++i) {
        int weight, from, to;
        in >> weight >> from >> to;
        g.add_edge(from, to); // peso ignorato per topologia
    }

    g.topological_sort(out);

    in.close();
    out.close();
    cout << "File creato\n";
    return 0;
}
