

/*
// Sample code to perform I/O:

cin >> name;                            // Reading input from STDIN
cout << "Hi, " << name << ".\n";        // Writing output to STDOUT

// Warning: Printing unwanted or ill-formatted data to output will cause the test cases to fail
*/

// Write your code here

#include<bits/stdc++.h>
#include <utility>
#include <cstdlib>

using namespace std;
typedef int ll;
typedef pair<int,int> pr;

ll inf = 1000000000;


template <class T> struct Node{

    T data;
    int height;
    int rank;
    Node *left;
    Node *right;

};

template <class T> class AvlTree{
    public:
    Node<T> *root;
    AvlTree(){
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
};

int compare(int a,int b){
    return a-b;
}

int compare(string a,string b){
    return a.compare(b);
}

int compare(pair<int,int> a,pair<int,int> b){ // first compare based on second and then on basis of first
    //return a.second-b.second;
    if(a.second == b.second){
        return a.first-b.first;
    }
    else{
        return a.second-b.second;
    }
}

void printThisNodesValue(int data){
    cout<<data<<"\n";
}

void printThisNodesValue(string data){
    cout<<data<<"\n";
}

void printThisNodesValue(pair<int,int> data){
    cout<<data.second<<"\n";
}
template <class T>
void AvlTree<T>::find_delete_Kth_smallest(Node<T> *root1, int k){

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
           //cout<<(temp->data).second<<"\n";
           root = delete_node(root,temp->data);
           flag = false;
          //  cout<<"\n in kway: "<<root->data;
            //return;
        }
    }
}

template <class T>
T AvlTree<T>::find_and_delete_first_min(Node<T> *root1){
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
           //cout<<(temp->data).second<<"\n";
           ans=temp->data;
           root = delete_node(root,temp->data);
           flag = false;
          //  cout<<"\n in kway: "<<root->data;
            //return;
        }
    }
    return ans;
}

template <class T>
bool AvlTree<T>::search(Node<T> *root, T data){
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
Node<T>* AvlTree<T>::getInorderSuccessor(Node<T>* root){

    while(root->left){
        root = root->left;
    }
    return root;
}

template <class T>
Node<T>* AvlTree<T>::delete_node(Node<T> *root, T data){

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
            root->height = 1+max( height(root->left) , height(root->right) );

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
                    //cout<<root->data;
                   // display(root,1);
                    root = performRR(root);
                    //display(root,1);
                }else{
                    root = performRL(root);
                }
            }
           // cout<<"\n"<<root->data;
    }

    return root;
}

template <class T>
int AvlTree<T>::count_left_nodes(Node<T> *root){
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
void AvlTree<T>::inorder(Node<T> *root){

    if(root!=NULL){
        inorder(root->left);
        cout<<"\ndata: "<<root->data<<" height: "<<root->height<<" rank: "<<root->rank;
        inorder(root->right);
    }
}

template <class T>
int AvlTree<T>::height(Node<T> *root){
    if(!root){
        return -1;
    }else if(!root->left && !root->right){
        return 0;
    }else
        return root->height;
}

template <class T>
int AvlTree<T>::getRank(Node<T> *root){
    if(root == NULL)
        return 0;
    return root->rank;
}

template <class T>
int AvlTree<T>::balanceFactor(Node<T> *root){
    if(!root || (!root->left && !root->right))
        return 0;
    return( height(root->left) - height(root->right)  );
}

template <class T>
Node<T> * AvlTree<T>::performLL(Node<T> *root){
   // cout<<"perform LL";
    Node<T> * x = root->left;
    Node<T> *y = x->right;

    x->right = root;
    root->left = y;

    root->height = 1+max(height(root->left), height(root->right));
    root->rank = 1+getRank(root->left)+ getRank(root->right);
    x->height = 1+max(height(x->left), height(x->right));
    x->rank = 1+getRank(x->left)+ getRank(x->right);
    return x;
}

template <class T>
int AvlTree<T>::test(Node<T> *root){
    cout<<"test: "<<root->data;
    cout<<"test: "<<root->left->data;
    cout<<"test "<<root->left->left->data;
    return 0;
}

template <class T>
Node<T> * AvlTree<T>::performRR(Node<T> *root){
    //cout<<"Current root is: "<<root->data<<"root right is: "<<root->right->data;
    Node<T> * x = root->right;
    Node<T> *y = x->left;
   // display(root,1);
    x->left = root;
    //display(root,1);
    root->right = y;
  //  cout<<"x->data: "<<x->data;
  //  display(x,1);
    root->height = 1+max(height(root->left), height(root->right));
    root->rank = 1+getRank(root->left)+ getRank(root->right);
    x->height = 1+max(height(x->left), height(x->right));
    x->rank = 1+getRank(x->left)+ getRank(x->right);
    //cout<<"\n"<<x->data;

    return x;
}

template <class T>
Node<T>* AvlTree<T>::performLR(Node<T> *root){
    root->left = performRR(root->left);
    return performLL(root);
}

template <class T>
Node<T>* AvlTree<T>::performRL(Node<T> *root){
    root->right = performLL(root->right);
    return performRR(root);
}

template <class T>
Node<T>* AvlTree<T>::add_to_tree(Node<T> *root, T data){

    if(root==NULL){
        //cout<<"here for inserting : "<<data;
        root = new Node<T>;
        root->data = data;
        root->left = NULL;
        root->right = NULL;
        root->height = 0;
        root->rank = 1;
        return root;
    }

    if(compare(root->data,data) > 0) { //root->data > data
        //cout<<"\n"<<root->data<<" > "<<data;
        root->left = add_to_tree(root->left, data);

        root->height = 1 + max( height(root->left) , height(root->right) );

        root->rank = 1+getRank(root->left)+ getRank(root->right);

        int bFactor = balanceFactor(root);
        //cout<<"\n bf: "<<bFactor;
        if(bFactor > 1){
          //cout<<"\nhere in balance...";
          //cout<<"data: "<<data <<"root->left->data "<<root->left->data<<" root->data"<<root->data;
           if(compare(root->left->data,data) > 0) { //root->left->data > data
                root = performLL(root);
                // test(root);
           }else{
                 root = performLR(root);
             }
        }
    }else if(compare(root->data,data) < 0) { //root->data < data)
        //cout<<"here1..";
        root->right = add_to_tree(root->right, data);
        //cout<<"here2..";
        root->height = 1 + max( height(root->left) , height(root->right) );
        //cout<<"here3..";
        root->rank = 1+getRank(root->left)+ getRank(root->right);
        //cout<<"here4..";
        int bFactor = balanceFactor(root);
        //cout<<"bf: "<<bFactor;

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

template <class T>
T AvlTree<T>::findMin(Node<T>* root){
    while(root->left){
        root = root->left;
    }
    return root->data;
}

template <class T>
void AvlTree<T>::deleteMin(Node<T>* root){
    T to_delete=findMin(root);
    delete_node(root,to_delete);
}


//wrappers
template <class T>
bool AvlTree<T>::find(T key){
    return search(this->root,key);
}

template <class T>
void AvlTree<T>::insert(T key){
    this->root=add_to_tree(this->root,key);
}

template <class T>
void AvlTree<T>::erase(T key){
    this->root=delete_node(this->root,key);
}

template <class T>
T AvlTree<T>::find_smallest(){
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
           //cout<<(temp->data).second<<"\n";
           ans=temp->data;
           //root = delete_node(root,temp->data);
           flag = false;
          //  cout<<"\n in kway: "<<root->data;
            //return;
        }
    }
    return ans;
}

template <class T>
void AvlTree<T>::remove_smallest(){
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
           //cout<<(temp->data).second<<"\n";
           ans=temp->data;
           root = delete_node(root,temp->data);
           flag = false;
          //  cout<<"\n in kway: "<<root->data;
            //return;
        }
    }
}

template <class T>
bool AvlTree<T>::empty(){
    if(this->root == NULL){
        return true;
    }
    else{
        return false;
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n,m;
    cin>>n;
    cin>>m;
    vector<vector<pair<int,ll>>> adj(n);
    vector<ll> dist(n,inf);
    vector<bool> done(n,false);
    for(int i=0;i<m;i++){
        int a,b;
        ll wt;
        cin>>a;
        cin>>b;
        cin>>wt;
        a--;
        b--;
        adj[a].push_back(make_pair(b,wt));
        //adj[b].push_back(make_pair(a,wt));
    }
     //priority_queue< pr, vector <pr> , greater<pr> > pq;
     AvlTree<pr> pq;
     dist[0]=0;

     //pq.push(make_pair(0,0));
     pq.insert(make_pair(0,0));
     while(!pq.empty()){
         pr th=pq.find_smallest();
         pq.remove_smallest();
         int nd=th.first;
         ll d=th.second;

         if(done[nd] == true){
             continue;
         }
         else{
             //dist[nd]=d;
             done[nd]=true;
         }
         for(int i=0;i<adj[nd].size();i++){
             int neigh=adj[nd][i].first;
             ll len=adj[nd][i].second;
             if(dist[nd]+len < dist[neigh]){
                dist[neigh] = dist[nd]+len;
                pq.insert(make_pair(neigh,dist[neigh]));
             }
             //dist[neigh]=min(dist[nd]+len , dist[neigh]);
         }
     }
     for(int i=1;i<n;i++){
         cout<<dist[i]<<" ";
     }
     //cout<<n<<" "<<m;
}

