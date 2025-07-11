#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

const int INF = 1e9;

enum Color { White, Grey, Black };

class Node {
public:
    int value;
    Color color;
    int distance;
    Node* parent;

    Node(int val) {
        value = val;
        color = White;
        distance = INF;
        parent = nullptr;
    }
};

class GraphUndirected {
private:
    map<int, Node*> nodes;
    map<int, vector< pair<int, int> > > adj;

public:
    void add_edge(int from, int to, int weight) {
        if (nodes.count(from) == 0) nodes[from] = new Node(from);
        if (nodes.count(to) == 0) nodes[to] = new Node(to);
        adj[from].push_back(make_pair(to, weight));
        adj[to].push_back(make_pair(from, weight));
    }

    void print_adjacency_list(ofstream& out) {
        for (const auto& entry : adj) {
            int node = entry.first;
            const vector< pair<int, int> >& neighbors = entry.second;
            out << node << " -> ";
            for (const auto& neighbor : neighbors) {
                out << "(" << neighbor.first << ", peso: " << neighbor.second << ") ";
            }
            out << "\n";
        }
    }

    void bfs(int start, ofstream& out) {
        for (auto& entry : nodes) {
            Node* n = entry.second;
            n->color = White;
            n->distance = INF;
            n->parent = nullptr;
        }

        if (nodes.count(start) == 0) return;

        Node* src = nodes[start];
        src->color = Grey;
        src->distance = 0;

        queue<Node*> q;
        q.push(src);

        while (!q.empty()) {
            Node* u = q.front();
            q.pop();
            out << u->value << " ";

            for (const auto& neighbor_info : adj[u->value]) {
                int neighbor_id = neighbor_info.first;
                Node* neighbor = nodes[neighbor_id];
                if (neighbor->color == White) {
                    neighbor->color = Grey;
                    neighbor->distance = u->distance + 1;
                    neighbor->parent = u;
                    q.push(neighbor);
                }
            }

            u->color = Black;
        }
    }

    ~GraphUndirected() {
        for (auto& entry : nodes) {
            delete entry.second;
        }
    }
};

int main() {
    ifstream in("inputNonOrientato.txt");
    ofstream out("output_undirected.txt");

    if (!in || !out) {
        cerr << "Errore apertura file.\n";
        return 1;
    }

    int n, m;
    in >> n >> m;

    GraphUndirected g;

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        in >> u >> v >> w;
        g.add_edge(u, v, w);
    }

    out << "Lista di adiacenza (grafo non orientato):\n";
    g.print_adjacency_list(out);

    out << "\nVisita BFS dal nodo 0:\n";
    g.bfs(0, out);

    cout << "Grafo caricato ed esplorato in BFS. Controlla output_undirected.txt\n";
    return 0;
}
