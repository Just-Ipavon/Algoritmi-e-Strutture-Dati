#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

template<typename T, typename S>
class Node{
public:
    T key;
    S val;
    Node<T,S>* parent;
    Node<T,S>* left;
    Node<T,S>* right;

    Node(T key,S val) : key(key), val(val){
        parent = left = right = nullptr;
    }
};

template<typename T, typename S>
class ABR{
public:
    NoNode<T,S>* root;

    ABR() {
    root = nullptr;
    }

    void insert(T key,S val){
        Node<T,S>* newnode = new Node<T,S>(key,val);
        Node<T,S>* currnode = root;
        Node<T,S>* parentnode = nullptr;
        while(currnode != nullptr){
            parentnode = currnode
            if(newnode->val < currnode->val)
                currnode = currnode->left;
            else
                currnode = currnode-> right;
        }

        newnode->parent = parentnode;
        if(parentnode == nullptr)
            root = newnode;
        else if(newnode->val < parentnode->val){
            parentnode->left = newnode
        }
        else{
            parentnode->right = newnode
        }
    }
    void pre(Node<T, S>* node, vector<pair<T, S>>& v){
        if(node){
            v.pushback(node->key,node->val);
            pre(node->left,v);
            pre(node->right,v);
        }
    }

}