#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

enum class Color {
    white = 0,
    grey = 1,
    black = 2
};

template <class T, class U>
class Node {
private:
    T key;
    U value;
    Color color;
    Node<T, U>* parent;

public:
    Node(T key, U value) : key(key), value(value), color(Color::white), parent(nullptr) {}

    T get_key() { return this->key;}
    U get_value() { return this->value;}
    Color get_color() { return this->color;}
    Node<T, U>* get_parent() { return this->parent;}

    void set_key(T key) { this->key = key;}
    void set_value(U value) { this->value = value;}
    void set_color(Color color) { this->color = color;}
    void set_parent(Node<T, U>* parent) { this->parent = parent;}
};

template <class T, class U>
class DirectedGraph {
private:
    int time;
    unordered_map<T, Node<T, U>*> vertices;
    unordered_map<T, unordered_map<T, int>> edges;
    unordered_map<T, int> start_time_table;
    unordered_map<T, int> end_time_table;

    void dfs_visit(Node<T, U>* node) {
        node->set_color(Color::grey);
        start_time_table[node->get_key()] = time++;

        for (auto& pair : edges[node->get_key()]) {
            Node<T, U>* adj_node = vertices[pair.first];
            if (adj_node->get_color() == Color::white) {
                adj_node->set_parent(node);
                dfs_visit(adj_node);
            }
        }

        node->set_color(Color::black);
        end_time_table[node->get_key()] = time++;
    }

    unordered_map<T, unordered_map<T, int>> get_transposed_edges() {
        unordered_map<T, unordered_map<T, int>> transposed_edges;

        for (auto& pair : edges) {
            T from_node = pair.first;

            unordered_map<T, int> adj = pair.second;
            for (auto& inner_pair : adj) {
                T to_node = inner_pair.first;
                int weight = inner_pair.second;
                transposed_edges[to_node][from_node] = weight;
            }
        }
        return transposed_edges;
    }

    void dfs_visit_collect(Node<T, U>* node, vector<T>& component) {
        node->set_color(Color::grey);
        component.push_back(node->get_key());

        for (auto& pair : edges[node->get_key()]) {
            Node<T, U>* adj_node = vertices[pair.first];
            if (adj_node->get_color() == Color::white) {
                adj_node->set_parent(node);
                dfs_visit_collect(adj_node, component);
            }
        }

        node->set_color(Color::black);
    }

    vector<Node<T, U>*> get_nodes_sorted_by_finish_time_desc() {
        vector<pair<int, T>> finish_times;

        for (auto& pair : end_time_table) {
            T key = pair.first;
            int end_time = pair.second;
            finish_times.push_back({end_time, key});
        }

        sort(finish_times.rbegin(), finish_times.rend());

        vector<Node<T, U>*> sorted_nodes;
        for (auto& pair : finish_times) {
            sorted_nodes.push_back(vertices[pair.second]);
        }

        return sorted_nodes;
    }

    vector<vector<T>> find_strongly_connected_components() {
        // Step 1: Run initial DFS to compute finishing times
        dfs();

        // Step 2: Get sorted nodes by decreasing finish time
        vector<Node<T, U>*> sorted_nodes = get_nodes_sorted_by_finish_time_desc();

        // Step 3: Get transposed edge list and build transposed graph
        auto transposed_edges = get_transposed_edges();

        // Step 4: Prepare new graph using transposed edges
        DirectedGraph<T, U> transposed_graph;

        // Re-add nodes to transposed graph
        for (auto& pair : vertices) {
            Node<T, U>* orig_node = pair.second;
            Node<T, U>* new_node = new Node<T, U>(orig_node->get_key(), orig_node->get_value());
            transposed_graph.add_node(new_node);
        }

        // Re-add reversed edges
        for (auto& from : transposed_edges) {
            for (auto& to : from.second) {
                transposed_graph.add_edge(
                    transposed_graph.vertices[from.first],
                    transposed_graph.vertices[to.first],
                    to.second
                );
            }
        }

        // Step 5: Do DFS again on transposed graph and collect SCCs
        vector<vector<T>> components;
        for (auto& pair : transposed_graph.vertices) {
            pair.second->set_color(Color::white);
            pair.second->set_parent(nullptr);
        }

        for (Node<T, U>* node : sorted_nodes) {
            Node<T, U>* transposed_node = transposed_graph.vertices[node->get_key()];
            if (transposed_node->get_color() == Color::white) {
                vector<T> component;
                transposed_graph.dfs_visit_collect(transposed_node, component);
                components.push_back(component);
            }
        }

        return components;
    }

public:
    DirectedGraph() : time(0) {}

    void add_node(Node<T, U>* node) {
        vertices[node->get_key()] = node;
    }

    void add_edge(Node<T, U>* from_node, Node<T, U>* to_node, int weight) {
        edges[from_node->get_key()][to_node->get_key()] = weight;
    }

    void dfs() {
        time = 0;
        for (auto& pair : vertices) {
            Node<T, U>* node = pair.second;
            node->set_color(Color::white);
            node->set_parent(nullptr);
        }

        for (auto& pair : vertices) {
            Node<T, U>* node = pair.second;
            if (node->get_color() == Color::white) {
                dfs_visit(node);
            }
        }
    }

    void print_times() {
        for (auto& pair : start_time_table) {
            T key = pair.first;
            cout << "Node " << key << ": Start = " << pair.second
                 << ", End = " << end_time_table[key] << endl;
        }
    }
};