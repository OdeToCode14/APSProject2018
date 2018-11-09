#include "hash_set.h"
#include <bits/stdc++.h>
using namespace std;
int main(){
    /*
    hash_table<int,node> hr;
    node d;
    d.data=5;
    hr.insert(4,d);
    node* x=hr.find(4);
    cout<<x->data<<"\n";
    hr.erase(4);
    x=hr.find(4);
    if(x == NULL)
        cout<<"not found"<<"\n";
*/
    hash_set<int> st1;
    for(int i=1;i<=25;i++){
        st1.insert(i);
    }
    //cout<<st1.collision<<"\n";
    
    hash_set<int> st2;
    for(int i=10;i<=50;i++){
        st2.insert(i);
    }
    hash_set<int> st3=st1.find_intersection(st2);
    st3.print();
    hash_set<int> st4=st1.find_union(st2);
    st4.print();
    hash_set<int> st5=st1.find_difference(st2);
    cout<<"diff\n";
    st5.print();
    






    //string str="abc";
    /*
    hr.insert(4,12);
    int val=hr.find(4);
    cout<<val<<"\n";

    hr.erase(4);
    val=hr.find(4);
    if(val == NULL){
        cout<<"not found\n";
    }
    cout<<val<<"\n";
    */

    /*
    for(int i=0;i<10000;i++){
        hr.insert(i,i*2);
    }
    */

    /*
    for(int i=0;i<30;i++){
        hr.find(i);
    }
    */

    //cout<<hr.find(856)<<"\n";
    //string x=hr.test("abc",2);
    //cout<<x<<"\n";
   //test<string,int>("abc",2);
return 0;
}