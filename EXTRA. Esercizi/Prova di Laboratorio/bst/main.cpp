#include <iostream>
#include <string>

using namespace std;


template <class K, class V>
class Node {
private:
    K key;
    V value;
    Node<K, V>* left;
    Node<K, V>* right;
    Node<K, V>* parent;
public:
    K get_key() { return key; }
    V get_value() { return value; }
    Node<K, V>* get_left() { return this->left; }
    Node<K, V>* get_right() { return this->right; }
    Node<K, V>* get_parent() { return this->parent; }

    void set_key(K key) { this->key = key; }
    void set_value(V value) { this->value = value; }
    void set_left(Node<K, V>* left) {
        this->left = left;
        if (left) left->parent = this;
    }
    void set_right(Node<K, V>* right) {
        this->right = right;
        if (right) right->parent = this;
    }
    void set_parent(Node<K, V>* parent) {this->parent = parent;}

    bool operator==(Node<K, V>* other) {return key == other->key;}

    Node(K key, V value) : key(key), value(value), left(nullptr), right(nullptr), parent(nullptr) {}
};

template <class K, class V>
ostream& operator<<(ostream& os, Node<K, V>* node) {
    os << "(" << node->get_key() << ")";
    return os;
}


template <class K, class V>
class BST {
private:
    Node<K, V>* root;

    Node<K, V>* find(Node<K, V>* current, K key) {
        if (!current) return nullptr;

        if (key < current->get_key()) {
            return find(current->get_left(), key);
        } else if (key > current->get_key()) {
            return find(current->get_right(), key);
        } else {
            return current;
        }
    }

    Node<K, V>* find_min(Node<K, V>* start) {
        Node<K, V>* min_node = start;
        while (min_node->get_left()) {
            min_node = min_node->get_left();
        }
        return min_node;
    }

    Node<K, V>* insert(Node<K, V>* current, Node<K, V>* new_node) {
        if (!current) return new_node;

        if (new_node->get_key() < current->get_key()) {
            current->set_left(insert(current->get_left(), new_node));
        } else {
            current->set_right(insert(current->get_right(), new_node));
        }
        return current;
    }

    void transplant(Node<K, V>* node_to_remove, Node<K, V>* new_subtree) {
        Node<K, V>* parent = node_to_remove->get_parent();
        if (!parent) {
            root = new_subtree;
            if (new_subtree) new_subtree->set_parent(nullptr);
        } else if (node_to_remove == parent->get_left()) {
            parent->set_left(new_subtree);
        } else {
            parent->set_right(new_subtree);
        }
    }

    void remove(Node<K, V>* node_to_remove, K key) {
        if (!node_to_remove->get_left()) {
            transplant(node_to_remove, node_to_remove->get_right());
        } else if (!node_to_remove->get_right()) {
            transplant(node_to_remove, node_to_remove->get_left());
        } else {
            Node<K, V>* successor = find_min(node_to_remove->get_right());
            transplant(successor, successor->get_right());
            successor->set_left(node_to_remove->get_left());
            successor->set_right(node_to_remove->get_right());
            transplant(node_to_remove, successor);
        }
        delete node_to_remove;
    }

    void inorder(Node<K, V>* current) {
        if (!current) return;

        inorder(current->get_left());
        cout << current << " ";
        inorder(current->get_right());
    }

    void destroy_subtree(Node<K, V>* node) {
        if (!node) return;

        destroy_subtree(node->get_left());
        destroy_subtree(node->get_right());
        delete node;
    }

    void left_rotate(Node<K, V>* x) {
        Node<K, V>* y = x->get_right();
        if (!y) return;
        Node<K, V>* y_subtree = y->get_left();


        x->set_right(y_subtree);
        transplant(x, y);
        y->set_left(x);
    }
public:
    void insert(K key, V value) {root = insert(root, new Node<K, V>(key, value));}
    bool search(K key) {return find(root, key) != nullptr;}
    void remove(K key) {
        Node<K, V>* node_to_remove = find(root, key);
        if (node_to_remove) remove(node_to_remove, key);
    }
    void inorder() {inorder(root); cout << endl;}

    void left_rotate(K key) {
        Node<K, V>* node = find(root, key);
        if (node) left_rotate(node);
    }

    BST() : root(nullptr) {}
    ~BST() {
        destroy_subtree(root);
    }
};


int main(int argc, char** argv) {
    BST<int, int> bst;

    bst.insert(10, 10);
    bst.insert(20, 20);
    bst.insert(15, 15);
    bst.inorder();
    bst.left_rotate(10);
    bst.inorder();

}