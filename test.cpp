#include "tree_set.h"
//using namespace std;

int main(){
    /*
    tree_set<pair<int,int>> tree;
    for(int i=20;i>=16;i--){
        tree.insert(make_pair(i,i));
    }
    std::cout<<tree.find_smallest().second<<"\n";
    */

    tree_set<int> st1;
    for(int i=1;i<=25;i++){
        st1.insert(i);
    }
    //std::cout<<st1.collision<<"\n";
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
    


    /*
    int n,m,q;
    string x;
    string data;
    tree_set<string> tree;

    cin>>n>>m;
    //std::cout<<n<<" "<<m<<"\n";
    for(int i=0;i<n;i++){
        cin>>data;
        tree.root = tree.insert(tree.root,data);
        //tree.inorder(tree.root);
    }
    std::cout<<"done\n";
    for(int i=0;i<m;i++){
        cin>>data;
        //std::cout<<"here\n";
        if(tree.search(tree.root,data)){
            std::cout<<"found\n";
        }
        else{
            std::cout<<"not found\n";
        }
        //std::cout<<"not here\n";
    }
    */
/*
    while(m-->0){
        cin>>q>>x;

        if(q==1){
            tree.root = tree.insert(tree.root,x);
        }else if(q==2){
            tree.search(tree.root,x);
        }else if(q==3){
            tree.find_delete_Kth_smallest(tree.root,x);
          //  tree.inorder(root);
        }
    }
    */

//     tree_set tree;
//       root = tree.insert(root,14);
//      root = tree.insert(root,10);
//      root = tree.insert(root,19);
//      root = tree.insert(root,8);
//      root = tree.insert(root,4);
//    root = tree.insert(root,7);
//    root = tree.insert(root,18);
//    root = tree.insert(root,13);
//    root = tree.insert(root,5);
//    root = tree.insert(root,1);
//    tree.search(root,4);
//    root = tree.insert(root,16);
//    tree.find_delete_Kth_smallest(root, 9);
    // root = tree.delete_node(root,4);
   //    root = tree.delete_node(root,6);
//    root = tree.insert(root,14);
//    root = tree.insert(root,17);
//    root = tree.insert(root,11);
//    root = tree.insert(root,7);
//    root = tree.insert(root,53);
//    root = tree.insert(root,4);
//    root = tree.insert(root,13);
//    root = tree.insert(root,12);
//    root = tree.insert(root,8);
   // root = tree.delete_node(root,3);
//    root = tree.delete_node(root,11);
  // tree.find_delete_Kth_smallest(root,3);
  // std::cout<<"\n"<<root->left->data;
  // root = tree.insert(root,1);
//    if(root->right == NULL){
//        std::cout<<"Yes";
//    }
   //std::cout<<root->right->data;
   //tree.inorder(root);
   //std::cout<<"Search result: ";tree.search(root,8);
   return 0;
}
