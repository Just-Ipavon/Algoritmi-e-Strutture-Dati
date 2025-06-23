#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <queue>
#include <unordered_map>

using namespace std;

const int WHITE = 0;
const int GREY = 1;
const int BLACK = 2;
const int infinity = 99999;

template<typename T>
class Node{
    public: 
    T key, val;
    Node<T>* parent;
    T distance;
    int color = WHITE;

    Node(T val) : val(val){}
};

template<typename T>
class Edge{
    public:
    T weight;
    Node<T>* source;
    Node<T>* destination;
    Edge(T weight, Node<T>* source, Node<T>* destination) : weight(weight), source(source), destination(destination){}
};

template<typename T>
class Graph{
    public:
    vector<Node<T>*> nodes;
    vector<Edge<T>*> edges;
    unordered_map<T, vector<pair<T,T>>> adj;
    unordered_map<T, Node<T>*> node_map;

    Node<T>* get_node(T val) {
    return node_map[val];
    }

    Node<T>* get_or_create_node(T val) {
        if (node_map.find(val) == node_map.end()) {
            Node<T>* node = new Node<T>(val);
            node_map[val] = node;
            nodes.push_back(node);
        }
        return node_map[val];
    }

    void add_edge_by_values(T weight, T source_val, T dest_val) {
        Node<T>* source = get_or_create_node(source_val);
        Node<T>* dest = get_or_create_node(dest_val);
        addEdge(weight, source, dest);
    }

    //Lo pseudocodice è molto simile, vi consiglio di leggere quello

    void BFS(Node<T>* snode){
        for(Node<T>* node: nodes){
            node->color = WHITE;
            node->parent = nullptr;
            node->distance = infinity;
        }
        snode->color = GREY;
        snode->parent = nullptr;
        snode->distance = 0;
        queue<Node<T>*> q;
        q.push(snode);
        while(!q.empty()){
            Node<T>* u = q.front();
            q.pop();
            for(auto v: adj[u->val]){
                Node<T>* node = nullptr;
                for(Node<T>* n: nodes){
                    if(n->val == v.first){
                        node = n;
                        break;
                    }
                }
                if(node == nullptr){
                    continue;
                }
                if(node->color == WHITE){
                    node->color = GREY;
                    node->parent = u;
                    node->distance = u->distance + v.first;
                    q.push(node);
                }
            }
            u->color = BLACK;
        }
    }


};

int main() {
    ifstream in("input.txt");
    int numnodes, numedges;
    in >> numnodes >> numedges;

    Graph<int> g;

    for (int i = 0; i < numedges; i++) {
        int weight, sourceval, destval;
        in >> weight >> sourceval >> destval;
        g.add_edge_by_values(weight, sourceval, destval);
    }
    in.close();

    Node<int>* snode = g.get_node(g.nodes[0]->val);

    g.BFS(snode);

    ofstream out("output.txt");
    out << "DISTANZE DAL NODO " << snode->val << ":\n\n";
    for (Node<int>* node : g.nodes) {
        out << "DISTANZA DAL NODO " << node->val << ": " << node->distance << endl;
    }
    out.close();

    cout << "File creato\n";
    return 0;
}
