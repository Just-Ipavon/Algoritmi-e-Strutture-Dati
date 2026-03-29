#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

enum Color { White, Grey, Black };

class Graph {
public:
    int n;
    // <Nodo di destinazione, Peso>
    vector<vector<pair<int, int>>> adj;

    Graph(int n) : n(n), adj(n) {}

    void add_edge(int u, int v, int weight) {
        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight}); // Non orientato
    }

    void bfs(int start, ostream& out) {
        vector<Color> color(n, White);
        vector<int> dist(n, -1); // in BFS il peso non conta per le distanze minime reali, conta solo nei percorsi a passi
        
        queue<int> q;
        color[start] = Grey;
        dist[start] = 0;
        q.push(start);

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            out << u << " ";
            
            for (auto edge : adj[u]) {
                int v = edge.first;
                if (color[v] == White) {
                    color[v] = Grey;
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
            color[u] = Black;
        }
    }

    void print(ostream& out) {
        for (int i = 0; i < n; i++) {
            out << i << " -> ";
            for (auto edge : adj[i]) 
                out << "(" << edge.first << ", w:" << edge.second << ") ";
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

    Graph g(n);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        if(in >> u >> v >> w) g.add_edge(u, v, w);
        else if (i==0) { g.add_edge(0,1,10); g.add_edge(1,2,5); break; }
    }

    ofstream out("output.txt");
    out << "Lista di adiacenza:\n";
    g.print(out);

    out << "\nBFS dal nodo 0:\n";
    g.bfs(0, out);

    cout << "Grafo pesato: BFS completata.\n";
    return 0;
}
