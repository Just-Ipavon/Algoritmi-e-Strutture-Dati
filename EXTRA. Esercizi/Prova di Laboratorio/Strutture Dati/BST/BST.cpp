#include <iostream>
#include <fstream>

using namespace std;

template <typename T>
class Node {
public:
    T key;
    Node* left;
    Node* right;

    Node(T val) : key(val), left(nullptr), right(nullptr) {}
};

template <typename T>
class BST {
private:
    Node<T>* root;

    Node<T>* insert(Node<T>* node, T key) {
        if (node == nullptr) {
            return new Node<T>(key);
        }
        if (key < node->key) {
            node->left = insert(node->left, key);
        } else if (key > node->key) {
            node->right = insert(node->right, key);
        }
        // Se la chiave è già presente non facciamo nulla (no duplicati)
        return node;
    }

    bool search(Node<T>* node, T key) {
        if (node == nullptr) return false;
        if (key == node->key) return true;
        if (key < node->key)
            return search(node->left, key);
        else
            return search(node->right, key);
    }

    void inorder(Node<T>* node) {
        if (node == nullptr) return;
        inorder(node->left);
        cout << node->key << " ";
        inorder(node->right);
    }

    void destroy(Node<T>* node) {
        if (node == nullptr) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {}

    ~BST() {
        destroy(root);
    }

    void insert(T key) {
        root = insert(root, key);
    }

    bool search(T key) {
        return search(root, key);
    }

    void inorder() {
        inorder(root);
        cout << endl;
    }
};


int main() {
    BST<int> tree;

    ifstream in("input.txt");
    if (!in) {
        cerr << "Errore apertura file input.txt\n";
        return 1;
    }

    int value;
    while (in >> value) {
        tree.insert(value);
    }
    in.close();

    cout << "Inorder traversal: ";
    tree.inorder();

    int key;
    cout << "Inserisci un valore da cercare: ";
    cin >> key;
    cout << "Search " << key << ": " << (tree.search(key) ? "Found" : "Not found") << endl;

    return 0;
}
