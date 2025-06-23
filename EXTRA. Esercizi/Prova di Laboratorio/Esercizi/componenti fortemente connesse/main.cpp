#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

enum Color { WHITE, GREY, BLACK };

class Node {
public:
    int key;
    Color color;
    Node* parent;

    Node(int k) : key(k), color(WHITE), parent(nullptr) {}
};

class Graph {
private:
    unordered_map<int, Node*> nodes;
    unordered_map<int, vector<int>> adj;
    unordered_map<int, vector<int>> adj_transposed;
    unordered_map<int, int> finish_time;
    int time = 0;

    void dfs_visit(int u) {
        nodes[u]->color = GREY;
        for (int v : adj[u]) {
            if (nodes[v]->color == WHITE) {
                nodes[v]->parent = nodes[u];
                dfs_visit(v);
            }
        }
        nodes[u]->color = BLACK;
        finish_time[u] = ++time;
    }

    void dfs_visit_transposed(int u, vector<int>& component) {
        nodes[u]->color = GREY;
        component.push_back(u);
        for (int v : adj_transposed[u]) {
            if (nodes[v]->color == WHITE) {
                dfs_visit_transposed(v, component);
            }
        }
        nodes[u]->color = BLACK;
    }

public:
    ~Graph() {
        for (auto& [_, node] : nodes) delete node;
    }

    void add_edge(int u, int v) {
        if (!nodes.count(u)) nodes[u] = new Node(u);
        if (!nodes.count(v)) nodes[v] = new Node(v);
        adj[u].push_back(v);
        adj_transposed[v].push_back(u);
    }

    vector<vector<int>> find_sccs() {
        // Step 1: DFS normale per orari di fine
        for (auto& [key, node] : nodes) {
            node->color = WHITE;
            node->parent = nullptr;
        }
        time = 0;
        for (auto& [key, node] : nodes) {
            if (node->color == WHITE) {
                dfs_visit(key);
            }
        }

        // Step 2: Ordina per tempo di fine decrescente
        vector<pair<int, int>> order;
        for (auto& [k, t] : finish_time) {
            order.emplace_back(t, k);
        }
        sort(order.rbegin(), order.rend());

        // Step 3: DFS sul grafo trasposto
        for (auto& [_, node] : nodes) {
            node->color = WHITE;
            node->parent = nullptr;
        }

        vector<vector<int>> components;
        for (auto& [_, k] : order) {
            if (nodes[k]->color == WHITE) {
                vector<int> component;
                dfs_visit_transposed(k, component);
                components.push_back(component);
            }
        }
        return components;
    }
};

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    Graph g;
    int u, v;
    while (in >> u >> v) {
        g.add_edge(u, v);
    }

    vector<vector<int>> sccs = g.find_sccs();

    out << "Componenti fortemente connesse:\n";
    for (const auto& comp : sccs) {
        for (int node : comp) {
            out << node << " ";
        }
        out << "\n";
    }

    in.close();
    out.close();
    cout << "Componenti fortemente connesse scritte in output.txt\n";
    return 0;
}
