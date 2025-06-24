#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>
#include <limits>
#include <queue>

using namespace std;

const int INF = numeric_limits<int>::max();

template <class T>
class Node {
public:
    T key;
    int distance;
    Node* parent;

    Node(T k) : key(k), distance(INF), parent(nullptr) {}
};

template <class T>
class Graph {
private:
    unordered_map<T, Node<T>*> nodes;
    unordered_map<T, vector<pair<T, int>>> adj;

public:
    Graph(const string& filename) {
        ifstream in(filename);
        T from, to;
        int weight;
        while (in >> from >> to >> weight) {
            if (!nodes.count(from)) nodes[from] = new Node<T>(from);
            if (!nodes.count(to)) nodes[to] = new Node<T>(to);
            adj[from].emplace_back(to, weight);
        }
        in.close();
    }

    ~Graph() {
        for (auto& [_, node] : nodes) delete node;
    }

    void reset() {
        for (auto& [_, node] : nodes) {
            node->distance = INF;
            node->parent = nullptr;
        }
    }

    void dijkstra(const T& source, const string& outfile) {
        for (auto& [_, edges] : adj)
            for (auto& [_, w] : edges)
                if (w < 0) throw runtime_error("Dijkstra non supporta pesi negativi.");

        reset();
        nodes[source]->distance = 0;

        using P = pair<int, T>; // distance, node key
        priority_queue<P, vector<P>, greater<>> pq;
        pq.push({0, source});

        while (!pq.empty()) {
            auto [dist, u] = pq.top(); pq.pop();
            if (dist > nodes[u]->distance) continue;
            for (auto& [v, weight] : adj[u]) {
                if (nodes[v]->distance > nodes[u]->distance + weight) {
                    nodes[v]->distance = nodes[u]->distance + weight;
                    nodes[v]->parent = nodes[u];
                    pq.push({nodes[v]->distance, v});
                }
            }
        }

        write_distances(outfile);
    }

    void bellman_ford(const T& source, const string& outfile) {
        reset();
        nodes[source]->distance = 0;

        int V = nodes.size();
        for (int i = 0; i < V - 1; ++i) {
            for (auto& [u, edges] : adj) {
                for (auto& [v, w] : edges) {
                    if (nodes[u]->distance != INF && nodes[v]->distance > nodes[u]->distance + w) {
                        nodes[v]->distance = nodes[u]->distance + w;
                        nodes[v]->parent = nodes[u];
                    }
                }
            }
        }

        // check ciclo negativo
        for (auto& [u, edges] : adj) {
            for (auto& [v, w] : edges) {
                if (nodes[u]->distance != INF && nodes[v]->distance > nodes[u]->distance + w) {
                    throw runtime_error("Ciclo negativo rilevato.");
                }
            }
        }

        write_distances(outfile);
    }

    void write_distances(const string& filename) {
        ofstream out(filename);
        for (auto& [key, node] : nodes) {
            out << "Nodo: " << key << "\tDistanza: ";
            if (node->distance == INF)
                out << "INF";
            else
                out << node->distance;
            out << endl;
        }
        out.close();
    }
};

int main() {
    try {
        // Test Bellman-Ford
        Graph<string> g_bf("bellman_ford-input.txt");
        g_bf.bellman_ford("A", "bellman_ford-output.txt");

        // Test Dijkstra
        Graph<string> g_dj("dijkstra-input.txt");
        g_dj.dijkstra("A", "dijkstra-output.txt");

        cout << "Algoritmi eseguiti. Controlla i file di output.\n";
    } catch (const exception& e) {
        cerr << "Errore: " << e.what() << endl;
        return 1;
    }

    return 0;
}
