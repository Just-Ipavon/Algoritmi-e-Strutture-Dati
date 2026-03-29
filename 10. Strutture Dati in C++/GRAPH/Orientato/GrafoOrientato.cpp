#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

enum Color { White, Grey, Black };

class Graph {
public:
    int n;
    vector<vector<pair<int, int>>> adj;

    Graph(int n) : n(n), adj(n) {}

    void add_edge(int u, int v, int weight) {
        adj[u].push_back({v, weight}); // Orientato: solo da u a v
    }

    void dfs_visit(int u, vector<Color>& color, ostream& out) {
        color[u] = Grey;
        out << u << " "; // Pre-order visiting
        
        for (auto edge : adj[u]) {
            int v = edge.first;
            if (color[v] == White) {
                dfs_visit(v, color, out);
            }
        }
        color[u] = Black; // Post-order (completamento)
    }

    void dfs(int start, ostream& out) {
        vector<Color> color(n, White);
        
        // Se vogliamo la DFS completa di tutti i nodi disconnessi:
        // for(int i=0; i<n; i++) if (color[i] == White) dfs_visit(i, color, out);
        
        // Se vogliamo partire solo da 'start' come faceva l'originale:
        if (start < n) dfs_visit(start, color, out);
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
    out << "Lista di adiacenza (Orientata):\n";
    g.print(out);

    out << "\nDFS ricorsiva dal nodo 0:\n";
    g.dfs(0, out);

    cout << "Grafo orientato: DFS completata.\n";
    return 0;
}
