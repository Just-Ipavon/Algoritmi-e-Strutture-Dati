#include <iostream>
#include <fstream>
using namespace std;

template<typename T, typename S>
class Node {
public:
    T key;
    S val;
    Node* left;
    Node* right;
    Node* parent;

    Node(T k, S v) : key(k), val(v), left(nullptr), right(nullptr), parent(nullptr) {}
};

template<typename T, typename S>
class ABR {
public:
    Node<T,S>* root;

    ABR() : root(nullptr) {}

    void insert(T key, S val) {
        Node<T,S>* nodein = new Node<T,S>(key, val);
        Node<T,S>* parentnode = nullptr;
        Node<T,S>* currentnode = root;

        while (currentnode) {
            parentnode = currentnode;
            if (key < currentnode->key) {
                currentnode = currentnode->left;
            } else if (key > currentnode->key) {
                currentnode = currentnode->right;
            } else {
                currentnode->val = val;
                delete nodein;
                return;
            }
        }
        nodein->parent = parentnode;
        if (!parentnode) root = nodein;
        else if (key < parentnode->key) parentnode->left = nodein;
        else parentnode->right = nodein;
    }

    // Preorder
    void preorder(Node<T,S>* node, ofstream& out) {
        if (!node) return;
        out << "chiave: " << node->key << ", valore: " << node->val << "\n";
        preorder(node->left, out);
        preorder(node->right, out);
    }

    // Postorder
    void postorder(Node<T,S>* node, ofstream& out) {
        if (!node) return;
        postorder(node->left, out);
        postorder(node->right, out);
        out << "chiave: " << node->key << ", valore: " << node->val << "\n";
    }

    // Ricerca
    Node<T,S>* search(Node<T,S>* node, T key) {
        if (!node || node->key == key) return node;
        if (key < node->key) return search(node->left, key);
        else return search(node->right, key);
    }

    // Minimo
    Node<T,S>* minimum(Node<T,S>* node) {
        while (node && node->left) node = node->left;
        return node;
    }

    void transplant(Node<T,S>* u, Node<T,S>* v) {
        if (!u->parent) root = v;
        else if (u == u->parent->left) u->parent->left = v;
        else u->parent->right = v;
        if (v) v->parent = u->parent;
    }

    void remove(T key) {
        Node<T,S>* z = search(root, key);
        if (!z) return;

        if (!z->left) transplant(z, z->right);
        else if (!z->right) transplant(z, z->left);
        else {
            Node<T,S>* y = minimum(z->right);
            if (y->parent != z) {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
        }
        delete z;
    }

};

int main() {
    ifstream in("input.txt");
    int key; char val;
    ABR<int,char> tree;

    while (in >> key >> val) {
        tree.insert(key, val);
    }
    in.close();

    ofstream out("output.txt");
    out << "Preorder:\n";
    tree.preorder(tree.root, out);

    out << "\nPostorder:\n";
    tree.postorder(tree.root, out);

    cout << "Inserisci la chiave da ricercare: ";
    int chiaveDaCercare;
    cin >> chiaveDaCercare;

    Node<int,char>* valoreTrovato = tree.search(tree.root, chiaveDaCercare);
    if(!valoreTrovato)
        cout << "\nNessuna chiave trovata\n";
    else
        cout << "La chiave ha valore: " << valoreTrovato->val << endl;

    out.close();
    cout << "File creato correttamente\n";
}
