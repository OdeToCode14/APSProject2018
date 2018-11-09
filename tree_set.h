#ifndef TREE_SET_H
#define TREE_SET_H

#include<iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

 template <class T> struct Node{

    T data;
    int height;
    int rank;
    Node *left;
    Node *right;

};

template <class T> class tree_set{
    public:
    Node<T> *root;
    tree_set(){
        root=NULL;
    }

    Node<T> *add_to_tree(Node<T> *root, T data);
    int balanceFactor(Node<T> *root);
    int height(Node<T> *root);
    Node<T> *performLL(Node<T> *root);
    Node<T> *performLR(Node<T> *root);
    Node<T> *performRL(Node<T> *root);
    Node<T> *performRR(Node<T> *root);
    int getRank(Node<T> *root);
    void inorder(Node<T> *root);
    Node<T> *delete_node(Node<T> *root, T data);
    int test(Node<T> *root);
    int count_left_nodes(Node<T> *root);
    Node<T>* getInorderSuccessor(Node<T> *root);
    bool search(Node<T>* root, T data);
    void find_delete_Kth_smallest(Node<T>*root, int k);
    T find_and_delete_first_min(Node<T> *root1);
    T findMin(Node<T>* root);
    void deleteMin(Node<T>* root);

    //wrappers
    void insert(T key);

    bool find(T key);
    void erase(T key);
    T find_smallest();
    void remove_smallest();
    bool empty();

    //set operations
    void inorder_add_to_vector(Node<T> *root,std::vector<T> &arr);
    void inorder_union(Node<T> *root,tree_set<T> &new_set);
    void inorder_intersection(Node<T> *root,tree_set<T> other,tree_set<T> &new_set);
    void inorder_difference(Node<T> *root,tree_set<T> other,tree_set<T> &new_set);

    tree_set<T> find_union(tree_set<T> other);
    tree_set<T> find_intersection(tree_set<T> other);
    tree_set<T> find_difference(tree_set<T> other);

    //for debugging
    void print();
};



int compare(int a,int b);

int compare(std::string a,std::string b);

int compare(std::pair<int,int> a,std::pair<int,int> b); // first compare based on second and then on basis of first

void printThisNodesValue(int data);

void printThisNodesValue(std::string data);

void printThisNodesValue(std::pair<int,int> data);
#endif