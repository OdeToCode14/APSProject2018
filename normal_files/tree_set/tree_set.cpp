#include<iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

//#include "tree_set.h"
//using namespace std;



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

int compare(int a,int b){
    return a-b;
}

int compare(std::string a,std::string b){
    return a.compare(b);
}

int compare(std::pair<int,int> a,std::pair<int,int> b){ // first compare based on second and then on basis of first
    //return a.second-b.second;
    if(a.second == b.second){
        return a.first-b.first;
    }
    else{
        return a.second-b.second;
    }
}

void printThisNodesValue(int data){
    std::cout<<data<<"\n";
}

void printThisNodesValue(std::string data){
    std::cout<<data<<"\n";
}

void printThisNodesValue(std::pair<int,int> data){
    std::cout<<data.second<<"\n";
}
template <class T>
void tree_set<T>::find_delete_Kth_smallest(Node<T> *root1, int k){

    Node<T> *temp = root1;
    bool flag = true;
    while(flag){
        if(k <= getRank(temp->left)){
            temp = temp->left;
        }else if( k > getRank(temp->left)+1){
            k = k-getRank(temp->left)-1;
            temp = temp->right ;
        }else{
           printThisNodesValue(temp->data);
           //std::cout<<(temp->data).second<<"\n";
           root = delete_node(root,temp->data);
           flag = false;
          //  std::cout<<"\n in kway: "<<root->data;
            //return;
        }
    }
}

template <class T>
T tree_set<T>::find_and_delete_first_min(Node<T> *root1){
    int k=1;
    T ans;
    Node<T> *temp = root1;
    bool flag = true;
    while(flag){
        if(k <= getRank(temp->left)){
            temp = temp->left;
        }else if( k > getRank(temp->left)+1){
            k = k-getRank(temp->left)-1;
            temp = temp->right ;
        }else{
           //printThisNodesValue(temp->data);
           //std::cout<<(temp->data).second<<"\n";
           ans=temp->data;
           root = delete_node(root,temp->data);
           flag = false;
          //  std::cout<<"\n in kway: "<<root->data;
            //return;
        }
    }
    return ans;
}

template <class T>
bool tree_set<T>::search(Node<T> *root, T data){
    bool found = false;

    while(root){
        if(compare(root->data,data) > 0){  // if(root->data > data)
            root = root->left;
        }else if(compare(root->data,data) < 0){ //root->data < data)
            root = root->right;
        }else{
            found = true;
            break;
        }
    }

    return found;
}

template <class T>
Node<T>* tree_set<T>::getInorderSuccessor(Node<T>* root){

    while(root->left){
        root = root->left;
    }
    return root;
}

template <class T>
Node<T>* tree_set<T>::delete_node(Node<T> *root, T data){

    if(!root)
        return root;

    if(compare(root->data,data) > 0) { //root->data > data
        root->left = delete_node(root->left,data);
    }else if(compare(root->data,data) < 0){ //root->data < data

        root->right = delete_node(root->right, data);
    }else{

         if(!root->left && !root->right){

              Node<T> *temp = root;
              root = NULL;
              free(temp);
         }else if(!(root->left) || !(root->right)){
            Node<T> *temp = (root->left)?root->left:root->right;
            *root = *temp;
            free(temp);
        }else{
            Node<T> *temp = getInorderSuccessor(root->right);
            root->data = temp->data;
            root->right = delete_node(root->right,temp->data);
        }
    }
    if(root){
            root->height = 1+std::max( height(root->left) , height(root->right) );

            root->rank = 1+getRank(root->left)+getRank(root->right);
            int bFactor = balanceFactor(root);
            if(bFactor>1){
                if(balanceFactor(root->left)>=0){
                    root = performLL(root);
                }else{
                    root = performLR(root);
                }
            }
            if(bFactor<-1){
                if(balanceFactor(root->right)<=0){
                    //std::cout<<root->data;
                   // display(root,1);
                    root = performRR(root);
                    //display(root,1);
                }else{
                    root = performRL(root);
                }
            }
           // std::cout<<"\n"<<root->data;
    }

    return root;
}

template <class T>
int tree_set<T>::count_left_nodes(Node<T> *root){
    int count =1;
    if(root->left){
        count+=count_left_nodes(root->left);
    }
    if(root->right){
        count+=count_left_nodes(root->right);
    }
    return count;
}

template <class T>
void tree_set<T>::inorder(Node<T> *root){

    if(root!=NULL){
        inorder(root->left);
        std::cout<<"\ndata: "<<root->data<<" height: "<<root->height<<" rank: "<<root->rank;
        inorder(root->right);
    }
}

template <class T>
int tree_set<T>::height(Node<T> *root){
    if(!root){
        return -1;
    }else if(!root->left && !root->right){
        return 0;
    }else
        return root->height;
}

template <class T>
int tree_set<T>::getRank(Node<T> *root){
    if(root == NULL)
        return 0;
    return root->rank;
}

template <class T>
int tree_set<T>::balanceFactor(Node<T> *root){
    if(!root || (!root->left && !root->right))
        return 0;
    return( height(root->left) - height(root->right)  );
}

template <class T>
Node<T> * tree_set<T>::performLL(Node<T> *root){
   // std::cout<<"perform LL";
    Node<T> * x = root->left;
    Node<T> *y = x->right;

    x->right = root;
    root->left = y;

    root->height = 1+std::max(height(root->left), height(root->right));
    root->rank = 1+getRank(root->left)+ getRank(root->right);
    x->height = 1+std::max(height(x->left), height(x->right));
    x->rank = 1+getRank(x->left)+ getRank(x->right);
    return x;
}

template <class T>
int tree_set<T>::test(Node<T> *root){
    std::cout<<"test: "<<root->data;
    std::cout<<"test: "<<root->left->data;
    std::cout<<"test "<<root->left->left->data;
    return 0;
}

template <class T>
Node<T> * tree_set<T>::performRR(Node<T> *root){
    //std::cout<<"Current root is: "<<root->data<<"root right is: "<<root->right->data;
    Node<T> * x = root->right;
    Node<T> *y = x->left;
   // display(root,1);
    x->left = root;
    //display(root,1);
    root->right = y;
  //  std::cout<<"x->data: "<<x->data;
  //  display(x,1);
    root->height = 1+std::max(height(root->left), height(root->right));
    root->rank = 1+getRank(root->left)+ getRank(root->right);
    x->height = 1+std::max(height(x->left), height(x->right));
    x->rank = 1+getRank(x->left)+ getRank(x->right);
    //std::cout<<"\n"<<x->data;

    return x;
}

template <class T>
Node<T>* tree_set<T>::performLR(Node<T> *root){
    root->left = performRR(root->left);
    return performLL(root);
}

template <class T>
Node<T>* tree_set<T>::performRL(Node<T> *root){
    root->right = performLL(root->right);
    return performRR(root);
}

template <class T>
Node<T>* tree_set<T>::add_to_tree(Node<T> *root, T data){

    if(root==NULL){
        //std::cout<<"here for inserting : "<<data;
        root = new Node<T>;
        root->data = data;
        root->left = NULL;
        root->right = NULL;
        root->height = 0;
        root->rank = 1;
        return root;
    }

    if(compare(root->data,data) > 0) { //root->data > data
        //std::cout<<"\n"<<root->data<<" > "<<data;
        root->left = add_to_tree(root->left, data);

        root->height = 1 + std::max( height(root->left) , height(root->right) );

        root->rank = 1+getRank(root->left)+ getRank(root->right);

        int bFactor = balanceFactor(root);
        //std::cout<<"\n bf: "<<bFactor;
        if(bFactor > 1){
          //std::cout<<"\nhere in balance...";
          //std::cout<<"data: "<<data <<"root->left->data "<<root->left->data<<" root->data"<<root->data;
           if(compare(root->left->data,data) > 0) { //root->left->data > data
                root = performLL(root);
                // test(root);
           }else{
                 root = performLR(root);
             }
        }
    }else if(compare(root->data,data) < 0) { //root->data < data)
        //std::cout<<"here1..";
        root->right = add_to_tree(root->right, data);
        //std::cout<<"here2..";
        root->height = 1 + std::max( height(root->left) , height(root->right) );
        //std::cout<<"here3..";
        root->rank = 1+getRank(root->left)+ getRank(root->right);
        //std::cout<<"here4..";
        int bFactor = balanceFactor(root);
        //std::cout<<"bf: "<<bFactor;

        if(bFactor <-1){
            if(compare(root->right->data,data) < 0) { //root->right->data <data)
                root = performRR(root);
            }else{
                root = performRL(root);
            }
        }
    }else{
        return root;
    }

    return root;
}
/*
template <class T>
T tree_set<T>::findMin(Node<T>* root){
    while(root->left){
        root = root->left;
    }
    return root->data;
}

template <class T>
void tree_set<T>::deleteMin(Node<T>* root){
    T to_delete=findMin(root);
    delete_node(root,to_delete);
}
*/

//wrappers
template <class T>
bool tree_set<T>::find(T key){
    return search(this->root,key);
}

template <class T>
void tree_set<T>::insert(T key){
    this->root=add_to_tree(this->root,key);
}

template <class T>
void tree_set<T>::erase(T key){
    this->root=delete_node(this->root,key);
}

template <class T>
T tree_set<T>::find_smallest(){
    int k=1;
    T ans;
    Node<T> *temp = this->root;
    bool flag = true;
    while(flag){
        if(k <= getRank(temp->left)){
            temp = temp->left;
        }else if( k > getRank(temp->left)+1){
            k = k-getRank(temp->left)-1;
            temp = temp->right ;
        }else{
           //printThisNodesValue(temp->data);
           //std::cout<<(temp->data).second<<"\n";
           ans=temp->data;
           //root = delete_node(root,temp->data);
           flag = false;
          //  std::cout<<"\n in kway: "<<root->data;
            //return;
        }
    }
    return ans;
}

template <class T>
void tree_set<T>::remove_smallest(){
    int k=1;
    T ans;
    Node<T> *temp = this->root;
    bool flag = true;
    while(flag){
        if(k <= getRank(temp->left)){
            temp = temp->left;
        }else if( k > getRank(temp->left)+1){
            k = k-getRank(temp->left)-1;
            temp = temp->right ;
        }else{
           //printThisNodesValue(temp->data);
           //std::cout<<(temp->data).second<<"\n";
           ans=temp->data;
           root = delete_node(root,temp->data);
           flag = false;
          //  std::cout<<"\n in kway: "<<root->data;
            //return;
        }
    }
}

template <class T>
bool tree_set<T>::empty(){
    if(this->root == NULL){
        return true;
    }
    else{
        return false;
    }
}


//operations on set
template <class T>
void tree_set<T>::inorder_add_to_vector(Node<T> *root,std::vector<T> &arr){
    if(root!=NULL){
        inorder_add_to_vector(root->left,arr);
        //std::cout<<"\ndata: "<<root->data<<" height: "<<root->height<<" rank: "<<root->rank;
        arr.push_back(root->data);
        inorder_add_to_vector(root->right,arr);
    }
}

template <class T>
void tree_set<T>::inorder_union(Node<T> *root,tree_set<T> &new_set){
    if(root!=NULL){
        inorder_union(root->left,new_set);
        //std::cout<<"\ndata: "<<root->data<<" height: "<<root->height<<" rank: "<<root->rank;
        new_set.insert(root->data);
        inorder_union(root->right,new_set);
    }
}

template <class T>
void tree_set<T>::inorder_intersection(Node<T> *root,tree_set<T> other,tree_set<T> &new_set){
    if(root!=NULL){
        inorder_intersection(root->left,other,new_set);
        //std::cout<<"\ndata: "<<root->data<<" height: "<<root->height<<" rank: "<<root->rank;
        if(other.find(root->data)){
            new_set.insert(root->data);
        }
        inorder_intersection(root->right,other,new_set);
    }
}

template <class T>
void tree_set<T>::inorder_difference(Node<T> *root,tree_set<T> other,tree_set<T> &new_set){
    if(root!=NULL){
        inorder_difference(root->left,other,new_set);
        //std::cout<<"\ndata: "<<root->data<<" height: "<<root->height<<" rank: "<<root->rank;
        if( !other.find(root->data) ){
            new_set.insert(root->data);
        }
        inorder_difference(root->right,other,new_set);
    }
}

template <class T>
tree_set<T> tree_set<T>::find_union(tree_set<T> other){
        tree_set<T> new_set;
        inorder_union(this->root,new_set);
        inorder_union(other.root,new_set);
        
        return new_set;
    }

template <class T>
tree_set<T> tree_set<T>::find_intersection(tree_set<T> other){
    tree_set<T> new_set;
    inorder_intersection(this->root,other,new_set);
    return new_set;
}

template <class T>
tree_set<T> tree_set<T>::find_difference(tree_set<T> other){
    tree_set<T> new_set;
    inorder_difference(this->root,other,new_set);
    return new_set;
}

// for debugging
template <class T>
void tree_set<T>::print(){
    std::vector<T> ans;
    inorder_add_to_vector(this->root,ans);
    sort(ans.begin(),ans.end());
    for(auto it: ans){
        std::cout<<it<<" ";
        //printThisNodesValue(it->data);
    }
    std::cout<<"\n";
}


int main(){
    tree_set<int> st1;
    for(int i=1;i<=25;i++){
        st1.insert(i);
    }

    tree_set<int> st2;
    for(int i=10;i<=50;i++){
        st2.insert(i);
    }
    tree_set<int> st3=st1.find_intersection(st2);
    st3.print();
    tree_set<int> st4=st1.find_union(st2);
    st4.print();
    tree_set<int> st5=st1.find_difference(st2);
    std::cout<<"diff\n";
    st5.print();

   return 0;
}





