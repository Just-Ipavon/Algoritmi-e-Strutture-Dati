#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <stack>
#include <string>

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
    int start_time;
    int end_time;
public:
    T get_key() {return this->key;}
    Color get_color() {return this->color;}
    Node<T>* get_parent() {return this->parent;}

    void set_key(T key) {this->key = key;}
    void set_color(Color color) {this->color = color;}
    void set_parent(Node<T>* parent) {this->parent = parent;}
    void set_start_time(int start_time) {this->start_time = start_time;}
    void set_end_time(int end_time) {this->end_time = end_time;}

    bool operator==(Node<T>& other) {
        return key == other.get_key();
    }

    Node(T key) : key(key), color(Color::white), parent(nullptr), start_time(0), end_time(0) {}
};


template <class T>
class Graph {
private:
    unordered_map<T, Node<T>*> vertices;
    unordered_map<T, map<T, int>> edges;
    int dfs_time;

    void add_node(Node<T>* node) {
        vertices[node->get_key()] = node;
    }

    void add_edge(T from_node, T to_node, int w) {
        edges[from_node][to_node] = w;
    }

    void dfs_visit(Node<T>* current, stack<Node<T>*>& ts_stack, int& cycles) {
        cout << "Analyzing " << current->get_key() << endl;
        current->set_color(Color::grey);
        current->set_start_time(dfs_time++);

        for (auto& pair : edges[current->get_key()]) {
            Node<T>* adj_node = vertices[pair.first];
            if (adj_node->get_color() == Color::white) {
                adj_node->set_parent(current);
                dfs_visit(adj_node, ts_stack, cycles);
            } else if (adj_node->get_color() == Color::grey) {
                cycles++;
            }
        }

        current->set_color(Color::black);
        current->set_end_time(dfs_time++);
        ts_stack.push(current);
    }

    void dfs(stack<Node<T>*>& ts_stack, int& cycles) {
        dfs_time = 0;
        for(auto& pair : vertices) {
            Node<T>* node = pair.second;
            node->set_parent(nullptr);
            node->set_color(Color::white);
        }

        for(auto& pair : vertices) {
            Node<T>* node = pair.second;
            if (node->get_color() == Color::white) {
                dfs_visit(node, ts_stack, cycles);
            }
        }
    }

    bool dfs_visit_hamiltonian_cycle(Node<T>* start, Node<T>* current, unordered_set<T>& visited) {
        visited.insert(current->get_key());

        for(auto& pair: edges[current->get_key()]) {
            Node<T>* adj_node = vertices[pair.first];
            if (adj_node == start && visited.size() == vertices.size()) {
                return true;
            } else if (visited.find(adj_node->get_key()) == visited.end()) {
                if(dfs_visit_hamiltonian_cycle(start, adj_node, visited)) {
                    return true;
                }
            }
        }
        visited.erase(current->get_key());
        return false;
    }

    bool dfs_hamiltonian_cycle() {
        for(auto& pair : vertices) {
            Node<T>* node = pair.second;
            unordered_set<T> visited;
            if(dfs_visit_hamiltonian_cycle(node, node, visited)) {
                return true;
            }
        }
        return false;
    }
public:
    void run_dfs() {
        stack<Node<T>*> ts_stack;
        int cycles = 0;
        dfs(ts_stack, cycles);

        while(!ts_stack.empty()) {
            Node<T>* node = ts_stack.top();
            ts_stack.pop();
            cout << "(" << node->get_key() << ")" << " ";
        }
        cout << endl;
        cout << "number of cycles: " << cycles << endl;
    }

    bool has_hamiltonian_cycle() {
        if (dfs_hamiltonian_cycle()) {
            return true;
        }
        return false;
    }

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
};


int main(int argc, char** argv) {
    Graph<string> graph("graph.txt");

    graph.run_dfs();

    if (graph.has_hamiltonian_cycle()) {
        cout << "The graph has an hamiltonian cycle" << endl;
    } else {
        cout << "The graph has NOT an hamiltonian cycle" << endl;
    }
}