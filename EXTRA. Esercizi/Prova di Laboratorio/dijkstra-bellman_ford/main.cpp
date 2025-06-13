#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>
#include <limits>
#include <queue>

using namespace std;

const int DIJKSTRA_NEGATIVE_EDGE_ERR_CODE = 1;
const int BELLMAN_FORD_NEGATIVE_CYCLE_ERR_CODE = 2;

enum class Color {
    white = 0,
    grey = 1,
    black = 2
};


template <class T>
class Node {
private:
    T key;
    Color color;
    Node<T>* parent;
    int distance;
public:
    T get_key() { return this->key; }
    Color get_color() { return this->color; }
    Node<T>* get_parent() { return this->parent; }
    int get_distance() { return this->distance; }

    void set_key(T key) { this->key = key; }
    void set_color(Color color) { this->color = color; }
    void set_parent(Node<T>* parent) { this->parent = parent; }
    void set_distance(int distance) { this->distance = distance; }

    Node(T key) : key(key), color(Color::white), parent(nullptr), distance(0) {}
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
        if (vertices.find(node->get_key()) == vertices.end()) {
            vertices[node->get_key()] = node;
        }
    }

    void add_edge(T from, T to, int w) {
        edges[from][to] = w;
    }

    void init_source(T source) {
        for (auto& pair : vertices) {
            pair.second->set_parent(nullptr);
            pair.second->set_distance(numeric_limits<int>::max());
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

    void dijkstra(T source) {
        init_source(source);

        priority_queue<Node<T>*, vector<Node<T>*>, DijkstraPriorityQueueComparator<T>> pq;
        pq.push(vertices[source]);

        while (!pq.empty()) {
            Node<T>* current = pq.top();
            pq.pop();

            for (auto& pair : edges[current->get_key()]) {
                Node<T>* adj_node = vertices[pair.first];
                int w = pair.second;
                if (relax(current, adj_node, w)) {
                    pq.push(adj_node);
                }
            }
        }
    }

    void bellman_ford(T source) {
        init_source(source);

        for (int i = 0; i < vertices.size() - 1; i++) {
            for (auto& edge : edges) {
                Node<T>* current = vertices[edge.first];
                for (auto& pair : edges[current->get_key()]) {
                    Node<T>* adj_node = vertices[pair.first];
                    int w = pair.second;
                    relax(current, adj_node, w);
                }
            }
        }

        for (auto& edge : edges) {
            Node<T>* current = vertices[edge.first];
            for (auto& pair : edges[current->get_key()]) {
                Node<T>* adj_node = vertices[pair.first];
                int w = pair.second;
                if (adj_node->get_distance() > current->get_distance() + w) {
                    throw runtime_error("Negative cycle detected in the graph!");
                }
            }
        }
    }
public:
    Graph(string init_file) {
        string from, to;
        int w;

        ifstream graph_data(init_file);
        while (graph_data >> from >> to >> w) {
            add_node(new Node<string>(from));
            add_node(new Node<string>(to));
            add_edge(from, to, w);
        }
        graph_data.close();
    }
    ~Graph() {}

    void dijkstra(T source, string outfile) {
        dijkstra(source);

        ofstream out(outfile);
        for (auto& pair : vertices) {
            out << "Node: " << pair.second->get_key() << "\t"
                << "Distance: " << pair.second->get_distance() << endl;
        }
        out.close();
    }

    void bellman_ford(T source, string outfile) {
        bellman_ford(source);

        ofstream out(outfile);
        for (auto& pair : vertices) {
            out << "Node: " << pair.second->get_key() << "\t"
                << "Distance: " << pair.second->get_distance() << endl;
        }
        out.close();
    }
};


int main(int argc, char** argv) {
    Graph<string> graph("bellman_ford-input.txt");


    graph.bellman_ford("A", "bellman_ford-output.txt");
}