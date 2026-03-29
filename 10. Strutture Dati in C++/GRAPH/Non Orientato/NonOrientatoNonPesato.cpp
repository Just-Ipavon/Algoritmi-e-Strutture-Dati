#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

// Manteniamo i colori come richiesto
enum Color { White, Grey, Black };

class Graph {
public:
    int n;
    vector<vector<int>> adj;

    Graph(int n) : n(n), adj(n) {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // Non orientato
    }

    // BFS classica e facilmente memorizzabile (usa array anziché nodi allocati)
    void bfs(int start, ostream& out) {
        vector<Color> color(n, White);
        vector<int> dist(n, -1);
        
        queue<int> q;
        color[start] = Grey;
        dist[start] = 0;
        q.push(start);

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            out << u << " ";
            
            for (int v : adj[u]) {
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
            for (int v : adj[i]) out << v << " ";
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

    Graph g(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        if(in >> u >> v) g.add_edge(u, v);
        // Test di fallback
        else if (i==0) { g.add_edge(0,1); g.add_edge(1,2); g.add_edge(2,3); g.add_edge(3,4); break;}
    }

    ofstream out("output.txt");
    out << "Lista di adiacenza:\n";
    g.print(out);

    out << "\nBFS dal nodo 0:\n";
    g.bfs(0, out);

    cout << "Grafo non pesato: BFS completata.\n";
    return 0;
}
