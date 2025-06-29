#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

template<typename T, typename S>
class Node {
public:
    T key;
    S val;
    Node<T, S>* parent;
    Node<T, S>* right;
    Node<T, S>* left;

    Node(T key, S val) : key(key), val(val) {
        parent = right = left = nullptr;
    }
};

template<typename T, typename S>
class ABR {
public:
    Node<T, S>* root;

    ABR() {
        root = nullptr;
    }

    void insert(T key, S val) {
        Node<T, S>* nodein = new Node<T, S>(key, val);
        Node<T, S>* parentnode = nullptr;
        Node<T, S>* currentnode = root;

        while (currentnode != nullptr) {
            parentnode = currentnode;
            if (nodein->val < currentnode->val) {
                currentnode = currentnode->left;
            } else {
                currentnode = currentnode->right;
            }
        }
        nodein->parent = parentnode;
        if (parentnode == nullptr) {
            root = nodein;
        } else if (nodein->val < parentnode->val) {
            parentnode->left = nodein;
        } else {
            parentnode->right = nodein;
        }
    }

    void pre(Node<T, S>* node, vector<pair<T, S>>& v) {
        if (node) {
            v.push_back({node->key, node->val});
            pre(node->left, v);
            pre(node->right, v);
        }
    }

    void post(Node<T, S>* node, vector<pair<T, S>>& v) {
        if (node) {
            post(node->left, v);
            post(node->right, v);
            v.push_back({node->key, node->val});
        }
    }

    void print(ofstream& out) {
        vector<pair<T, S>> preorder;
        pre(root, preorder);
        for (auto& p : preorder) {
            out << "chiave: " << p.first << ", valore: " << p.second << endl;
        }
    }

    void print_postorder(ofstream& out) {
        vector<pair<T, S>> postorder;
        post(root, postorder);
        for (auto& p : postorder) {
            out << "chiave: " << p.first << ", valore: " << p.second << endl;
        }
    }
};

int main() {
    ifstream in("input.txt");
    int key;
    char val;
    ABR<int, char>* albero = new ABR<int, char>();
    while (in >> key >> val) {
        albero->insert(key, val);
    }
    in.close();

    ofstream out("output999.txt");
    out << "Preorder:\n";
    albero->print(out);

    out << "\nPostorder:\n";
    albero->print_postorder(out);

    out.close();

    cout << "Il file è stato creato" << endl;
    return 0;
}
