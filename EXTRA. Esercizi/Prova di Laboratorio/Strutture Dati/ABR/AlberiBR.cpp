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

    Node<T, S>* search(Node<T, S>* node, T key) {
    if (node == nullptr || node->key == key)
        return node;
    if (key < node->key)
        return search(node->left, key);
    else
        return search(node->right, key);
    }

    void transplant(Node<T, S>* u, Node<T, S>* v) {
    if (u->parent == nullptr)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    if (v != nullptr)
        v->parent = u->parent;
    }

    void remove(T key) {
    Node<T, S>* z = search(root, key);
    if (z == nullptr) return;

    if (z->left == nullptr) {
        transplant(z, z->right);
    } else if (z->right == nullptr) {
        transplant(z, z->left);
    } else {
        Node<T, S>* y = minimum(z->right);
        if (y->parent != z) {
            transplant(y, y->right);
            y->right = z->right;
            if (y->right != nullptr)
                y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        if (y->left != nullptr)
            y->left->parent = y;
    }

    delete z;
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
