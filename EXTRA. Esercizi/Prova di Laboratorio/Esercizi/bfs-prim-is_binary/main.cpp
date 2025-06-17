#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>
#include <limits>
#include <queue>

using namespace std;

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
    int prim_key;

public:
    T get_key() { return this->key;}
    Color get_color() { return this->color;}
    Node<T>* get_parent() { return this->parent;}
    int get_distance() { return this->distance;}
    int get_prim_key() { return this->prim_key;}

    void set_key(T key) { this->key = key;}
    void set_color(Color color) { this->color = color;}
    void set_parent(Node<T>* parent) { this->parent = parent;}
    void set_distance(int distance) { this->distance = distance;}
    void set_prim_key(int prim_key) { this->prim_key = prim_key;}

    Node(T key) : key(key), color(Color::white), parent(nullptr), distance(0) {}
};


template <class T>
class PrimKeyComparator {
public:
    bool operator()(Node<T>* n1, Node<T>* n2) {
        return (n1->get_prim_key() > n2->get_prim_key());
    }
};


template <class T>
class Graph {
private:
    unordered_map<T, Node<T>*> vertices;
    unordered_map<T, unordered_map<T, int>> edges;

    void add_node(Node<T>* node) {
        vertices[node->get_key()] = node;
    }

    void add_edge(T from_node, T to_node, int w) {
        edges[from_node][to_node] = w;
        edges[to_node][from_node] = w;
    }

    void prim(T starting_node) {
        for (auto& pair : vertices) {
            Node<T>* node = pair.second;
            node->set_parent(nullptr);
            node->set_prim_key(numeric_limits<int>::max());
        }

        Node<T>* source = vertices[starting_node];
        source->set_prim_key(0);

        priority_queue<Node<T>*, vector<Node<T>*>, PrimKeyComparator<T>> q;
        unordered_set<T> q_tracker;
        for (auto& pair : vertices) {
            q.push(pair.second);
            q_tracker.insert(pair.first);
        }

        while(!q.empty()) {
            Node<T>* current = q.top();
            q.pop();

            for (auto& pair : edges[current->get_key()]) {
                Node<T>* adj_node = vertices[pair.first];
                int w = edges[current->get_key()][adj_node->get_key()];
                if (q_tracker.find(adj_node->get_key()) != q_tracker.end() && w < adj_node->get_prim_key()) {
                    adj_node->set_parent(current);
                    adj_node->set_prim_key(w);
                }
            }
        }
    }
public:
    Graph(string init_file_path) {
        ifstream data(init_file_path);

        T from_node, to_node;
        int w;
        while(data >> from_node >> to_node >> w) {
            add_node(new Node<T>(from_node));
            add_node(new Node<T>(to_node));
            add_edge(from_node, to_node, w);
        }

        data.close();
    }

    void dfs(T starting_node, string outfile) {
        for (auto& pair : vertices) {
            Node<T>* node = pair.second;
            node->set_parent(nullptr);
            node->set_distance(numeric_limits<int>::max());
            node->set_color(Color::white);
        }

        Node<T>* source = vertices[starting_node];
        source->set_distance(0);
        source->set_color(Color::grey);

        queue<Node<T>*> q;
        q.push(source);

        while (!q.empty()) {
            Node<T>* current = q.front();
            q.pop();

            for (auto& pair : edges[current->get_key()]) {
                Node<T>* adj_node = vertices[pair.first];
                if (adj_node->get_color() == Color::white) {
                    adj_node->set_parent(current);
                    adj_node->set_distance(current->get_distance() + 1);
                    adj_node->set_color(Color::grey);
                    q.push(adj_node);
                }
            }
            current->set_color(Color::black);
        }

        ofstream output(outfile);
        output << "Order is [NODE] -> [DISTANCE] -> [PARENT]" << endl;
        for (auto& pair : vertices) {
            Node<T>* current = pair.second;

            string parent = "NULL";
            if (current->get_parent()) {
                parent = current->get_parent()->get_key();
            }
            output << current->get_key() << "\t" << current->get_distance() << "\t" << parent << endl;
        }
        output.close();
    }

    void print_mst(T source) {
        prim(source);

        for (auto& pair : vertices) {
            Node<T>* current = pair.second;
            cout << "Node: " << current->get_key()
                 << "\tParent: " << (current->get_parent() ? current->get_parent()->get_key() : "NULL")
                 << endl;
        }
    }

    bool is_mst_binary() {
        unordered_map<T, int> childrens;
        for (auto& pair : vertices) {
            Node<T>* current = pair.second;
            if (current->get_parent() && ++childrens[current->get_parent()->get_key()] > 2) {
                return false;
            }
        }
        return true;
    }
};

int main() {
    // Initialize the graph using the file
    Graph<string> g("graph.txt");

    // Run DFS starting from node A and write results to output.txt
    g.dfs("A", "output.txt");
    cout << "DFS completed. Results written to output.txt\n";

    // Print the MST starting from node A
    cout << "\nMST (Prim's Algorithm) starting from node A:\n";
    g.print_mst("A");

    // Check if the resulting MST is a binary tree
    bool binary = g.is_mst_binary();
    cout << "\nIs the MST a binary tree? " << (binary ? "Yes" : "No") << endl;

    return 0;
}