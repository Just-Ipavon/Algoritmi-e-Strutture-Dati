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
    T get_key() { return key; }
    U get_value() { return value; }
    Node<K, V>* get_left() { return left; }
    Node<K, V>* get_right() { return right; }
    Node<K, V>* get_parent() { return parent; }

    void set_key(T key) { this->key = key; }
    void set_value(U value) { this->value = value; }
    void set_left(Node<K, V>* left) { this->left = left; if (left) left->parent = this; }
    void set_right(Node<K, V>* right) { this->right = right; if (right) right->parent = this; }
    void set_parent(Node<K, V>* parent) { this->parent = parent; }

    bool operator>(const Node<K, V>& other) const { return key > other.key; }
    bool operator<(const Node<K, V>& other) const { return key < other.key; }
    bool operator==(const Node<K, V>& other) const { return key == other.key; }

    Node(T key, U value) : key(key), value(value), left(nullptr), right(nullptr), parent(nullptr) {}
};

template <class K, class V>
ostream& operator<<(ostream& os, Node<K, V>* node) {
    os << "(" << node->get_key() << ")";
    return os;
}

// To implement:
// [] insert
// [] remove
// [] search
// [] inorder
// [] postorder
// [] preorder
// [] transplant
// [] leftrotate
// [] rightrotate

template <class K, class V>
class BST {
private:
    Node<K, V>* root;

    Node<K, V>* insert(Node<K, V>* current, Node<K, V>* new_node) {
        if (!current) return new_node;

        if (new_node < current) {
            current->set_left(insert(current->get_left(), new_node));
        } else {
            current->set_right(insert(current->get_right(), new_node));
        }
        return current;
    }

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
public:
    void insert(K key, V value) {
        root = insert(root, new Node<K, V>(key, value));
    }

    bool search(K key) {
        return find(root, key) != nullptr;
    }

};