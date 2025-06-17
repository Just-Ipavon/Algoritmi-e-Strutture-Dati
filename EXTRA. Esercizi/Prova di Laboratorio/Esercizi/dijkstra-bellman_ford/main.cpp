#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>
#include <limits>
#include <queue>

using namespace std;

enum class Color { white, grey, black };

template <class T>
class Node {
private:
    T key;
    Color color;
    Node<T>* parent;
    int distance;
public:
    Node(T key) : key(key), color(Color::white), parent(nullptr), distance(numeric_limits<int>::max()) {}

    T get_key() const { return key; }
    Color get_color() const { return color; }
    Node<T>* get_parent() const { return parent; }
    int get_distance() const { return distance; }

    void set_key(T key) { this->key = key; }
    void set_color(Color color) { this->color = color; }
    void set_parent(Node<T>* parent) { this->parent = parent; }
    void set_distance(int distance) { this->distance = distance; }
};

template <class T>
ostream& operator<<(ostream& os, Node<T>* node) {
    os << "(" << node->get_key() << ")";
    return os;
}

template <class T>
class DijkstraPriorityQueueComparator {
public:
    bool operator()(Node<T>* n1, Node<T>* n2) {
        return n1->get_distance() > n2->get_distance();
    }
};

template <class T>
class Graph {
private:
    unordered_map<T, Node<T>*> vertices;
    unordered_map<T, unordered_map<T, int>> edges;

    void add_node(Node<T>* node) {
        vertices.try_emplace(node->get_key(), node);
    }

    void add_edge(T from, T to, int w) {
        edges[from][to] = w;
    }

    void init_source(T source) {
        for (auto& [k, node] : vertices) {
            node->set_distance(numeric_limits<int>::max());
            node->set_parent(nullptr);
        }
        vertices[source]->set_distance(0);
    }

    bool relax(Node<T>* from, Node<T>* to, int w) {
        if (from->get_distance() == numeric_limits<int>::max()) return false;

        if (to->get_distance() > from->get_distance() + w) {
            to->set_distance(from->get_distance() + w);
            to->set_parent(from);
            return true;
        }
        return false;
    }

    void _dijkstra(T source) {
        init_source(source);
        priority_queue<Node<T>*, vector<Node<T>*>, DijkstraPriorityQueueComparator<T>> pq;
        pq.push(vertices[source]);

        while (!pq.empty()) {
            Node<T>* current = pq.top(); pq.pop();
            for (auto& [adj_key, weight] : edges[current->get_key()]) {
                Node<T>* adj_node = vertices[adj_key];
                if (relax(current, adj_node, weight)) {
                    pq.push(adj_node);
                }
            }
        }
    }

    void _bellman_ford(T source) {
        init_source(source);
        int V = vertices.size();

        for (int i = 0; i < V - 1; i++) {
            for (auto& [u, neighbours] : edges) {
                Node<T>* from = vertices[u];
                for (auto& [v, w] : neighbours) {
                    Node<T>* to = vertices[v];
                    relax(from, to, w);
                }
            }
        }

        for (auto& [u, neighbours] : edges) {
            Node<T>* from = vertices[u];
            for (auto& [v, w] : neighbours) {
                Node<T>* to = vertices[v];
                if (to->get_distance() > from->get_distance() + w) {
                    throw runtime_error("Negative cycle detected in the graph!");
                }
            }
        }
    }

public:
    Graph(string init_file) {
        ifstream graph_data(init_file);
        string from, to;
        int w;
        while (graph_data >> from >> to >> w) {
            add_node(new Node<string>(from));
            add_node(new Node<string>(to));
            add_edge(from, to, w);
        }
    }

    ~Graph() {
        for (auto& [key, node] : vertices) {
            delete node;
        }
    }

    void dijkstra(T source, const string& outfile) {
        for (auto& [u, neighbors] : edges) {
            for (auto& [v, weight] : neighbors) {
                if (weight < 0) {
                    throw runtime_error("Dijkstra cannot handle negative weights.");
                }
            }
        }

        _dijkstra(source);

        ofstream out(outfile);
        for (auto& [key, node] : vertices) {
            out << "Node: " << key << "\tDistance: ";
            if (node->get_distance() == numeric_limits<int>::max())
                out << "INF";
            else
                out << node->get_distance();
            out << endl;
        }
    }

    void bellman_ford(T source, const string& outfile) {
        _bellman_ford(source);

        ofstream out(outfile);
        for (auto& [key, node] : vertices) {
            out << "Node: " << key << "\tDistance: ";
            if (node->get_distance() == numeric_limits<int>::max())
                out << "INF";
            else
                out << node->get_distance();
            out << endl;
        }
    }
};

int main() {
    try {
        Graph<string> graph("bellman_ford-input.txt");
        graph.bellman_ford("A", "bellman_ford-output.txt");
        // graph.dijkstra("A", "dijkstra-output.txt"); // opzionale
    } catch (const exception& ex) {
        cerr << "Errore: " << ex.what() << endl;
        return 1;
    }
    return 0;
}
