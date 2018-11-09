#include <bits/stdc++.h>
#define unalloted 0
#define filled 1
#define deleted 2
#define upper_bound 0.8
#define lower_bound 0.2

typedef long long ll;
using namespace std;

template <class T> class hash_set{
public:
    //long long collision;
    vector<int> size_list={79, 163, 331, 673, 1361, 2729, 5471, 10949, 21911, 43853, 87719, 175447, 350899, 701819, 1403641, 2807303, 5614657, 11229331};
    int size_list_ptr;
    int sz;
    int occupied;
    vector<pair<int,T>> table;
    int number_of_digits=12;
    vector<ll> power;
    void find_power(){
        ll prime=37;
        power[0]=1;
        for(int i=1;i<number_of_digits;i++){
            power[i]=power[i-1]*prime;
            //cout<<power[i]<<"\n";
        }
    }

    int next_prime(int num) {
        while(true){
            num++;
            // Corner cases
            bool flag=true;
            if(num<=2){
                return 3;
            }
            if (num%2 == 0 || num%3 == 0){
                continue;
            }

            for (int i=5; i*i<=num; i=i+6){
                if (num%i == 0 || num%(i+2) == 0){
                   flag=false;
                   break;
                }
            }
            if(flag){
                break;
            }
        }
        return num;
    }

    hash_set(){
        //collision = 0;
        size_list_ptr=0;
        occupied=0;
        sz=size_list[size_list_ptr];
        table.resize(sz); //first one is status of cell (either occupied, filled or deleted) second is key value pair
        power.resize(number_of_digits);
        find_power();
    }
    /*
    hash_set(int a){
        occupied=0;
        sz=a;
        sz=next_prime(sz);
        table.resize(sz);
        power.resize(number_of_digits);
        find_power();
    }
    */

    int get_hash(int key){

        ll prime=37;
        vector<int> digits;
        while(key>0){
            int d=key%10;
            key=key/10;
            digits.push_back(d);
        }
        ll sum=0;
        for(int i=digits.size()-1;i>=0;i--){
            int d=digits[i];
            sum=sum+d*power[digits.size()-i-1];
        }
        ll hash=sum%sz;
        return (int) hash;

        //return key%sz;
    }
    int get_hash(string key){
       /*
       int sum=0;
       for (int i=0; i < key.length(); i++){
         sum += key[i];
       }
       int hash=sum%sz;
       return hash;
       */
         int chunk_size=4;
         int number_of_chunks = key.length() / 4;
         ll sum = 0;
         for (int j = 0; j < number_of_chunks; j++) {
                int start=j*chunk_size;
                int last=start+3;
           ll mult = 1;
           for (int k = start; k <=last; k++) {
             sum += key[k] * mult;
             mult *= 256;
           }
         }
         if(key.length() %4 != 0){
                 int start=number_of_chunks*chunk_size;
                 int last=key.length()-1;
                 ll mult = 1;
                 for (int k = start; k <=last; k++) {
                   sum += key[k] * mult;
                   mult *= 256;
                 }
         }
         return(abs(sum) % sz);
    }

    int find_hash(T key){
        int hash;
        string test_str;
        int test_int;
        if(typeid(key) == typeid(test_str)){
                //cout<<"string\n";
            hash=get_hash(key);
            return hash;
        }
        else if (typeid(key) == typeid(test_int)){
            //cout<<"int\n";
            hash=get_hash(key);
            return hash;
        }
        else{
            return 0;
        }
        //cout<<"hash found is "<<hash<<"\n";
    }



    void increase_table_size(){
        //cout<<"here\n";
        if(size_list_ptr == size_list.size()-1){
            return;
        }
        size_list_ptr++;
        //int new_sz=sz*2;
        int new_sz=size_list[size_list_ptr];
        //new_sz=next_prime(new_sz);
        vector<pair<int,T>> new_table(new_sz);
        vector<pair<int,T>> dup_table=table;
        table=new_table;
        sz=new_sz;
        for(auto it : dup_table){
            if(it.first == filled){
                T key=it.second;
                //U value=it.second.second;
                insert(key);
            }
        }
    }

    void decrease_table_size(){
        //int new_sz=sz/2;
        if(size_list_ptr == 0){
            return;
        }
        size_list_ptr--;
        //new_sz=next_prime(new_sz);
        int new_sz=size_list[size_list_ptr];
        vector<pair<int,T>> new_table(new_sz);
        vector<pair<int,T>> dup_table=table;
        table=new_table;
        sz=new_sz;
        for(auto it : dup_table){
            if(it.first == filled){
                T key=it.second;
                //U value=it.second.second;
                insert(key);
            }
        }
    }

    void insert(T key){
        int bucket=find_hash(key);

        int i = bucket;
        int h = 1;

        /* probing through the array until an unalloted or deleted space is found */
        while (table[i].first == filled) {
                //collision++;

            if (table[i].second == key) {
                /* case when already present key matches the given key */
                //printf("\n This key is already present in hash table, hence updating it's value \n");
                table[i].second = key;
                //cout<<i<<" "<<table[i].second.second<<"\n";
                return;
            }
            i = (i + (h * h)) % sz;
            h++;
            if (i == bucket){
                increase_table_size();
                insert(key);
                //printf("\n Hash table is full, cannot add more elements \n");
                //return;
            }

        }
        table[i].first = filled;
        table[i].second = key;
        //table[i].second.second = value;
        //cout<<i<<" "<<table[i].second.second<<"\n";
        //printf("\n Key  has been inserted\n");
        occupied++;
        double balance_factor=(double) occupied / (double) sz;
        //cout<<"balance fact "<<balance_factor<<" "<<occupied<<" "<<sz<<"\n";
        if(balance_factor > upper_bound){
            increase_table_size();
            //cout<<"new size "<<sz<<"\n";
        }
    }

    bool find(T key){
        int bucket = find_hash(key);
        int i = bucket;
        int h = 1;

        /* probing through the hash table until we reach at location where there had not been an element even once */
        while (table[i].first != unalloted){
            if (table[i].first == filled  &&  table[i].second == key) {

                /* case where data exists at the location and its key matches to the given key */
                //U *ret=&(table[i].second.second);
                //cout<<ret<<"\n";
                //return ret;
                //return table[i].second.second;
                return true;
            }
            i = (i + (h * h)) % sz;
            h++;
            if (i == bucket) {
                break;
            }
        }
        //printf("\n Key does not exist \n");
        //return NULL;
        return false;
    }

    void erase(T key){
        int bucket = find_hash(key);
        int i = bucket;
        int h = 1;

        /* probing through the hash table until we reach at location where there had not been an element even once */
        while (table[i].first != unalloted){
            if (table[i].first == filled &&  table[i].second == key) {

                /* case where data exists at the location and its key matches to the given key */
                table[i].first = deleted;
                //table[i].second.second = NULL;
                occupied--;
                double balance_factor=(double) occupied / (double) sz;
                //cout<<"balance fact "<<balance_factor<<" "<<occupied<<" "<<sz<<"\n";
                if(balance_factor < lower_bound){
                    decrease_table_size();
                    //cout<<"new size "<<sz<<"\n";
                }
                //printf("\n Key has been removed \n");
                return;

            }
            i = (i + (h * h)) % sz;
            h++;
            if (i == bucket) {
                break;
            }
        }
        //printf("\n Key does not exist \n");
    }

    //returns true if set is empty
    bool empty(){
        if(occupied == 0){
            return true;
        }
        else{
            return false;
        }
    }
    

    hash_set find_union(hash_set<T> other){
        hash_set<T> un;
        for(int i=0;i<this->sz;i++){
            if(this->table[i].first == filled){
                un.insert(this->table[i].second);
            }
        }
        for(int i=0;i<other.sz;i++){
            if(other.table[i].first == filled){
                un.insert(other.table[i].second);
            }
        }
        return un;
    }
    hash_set find_intersection(hash_set<T> other){
        hash_set<T> intr;
        for(int i=0;i<this->sz;i++){
            if(this->table[i].first == filled){
                T key=table[i].second;
                if(other.find(key)){
                    intr.insert(key);
                }
            }
        }
        return intr;
    }

    hash_set find_difference(hash_set<T> other){
        hash_set<T> diff;
        for(int i=0;i<this->sz;i++){
            if(this->table[i].first == filled){
                T key=table[i].second;
                if(!other.find(key)){
                    diff.insert(key);
                }
            }
        }
        return diff;
    }

    //for debugging
    void print(){
        vector<int> ans;
        for(int i=0;i<sz;i++){
            if(table[i].first == filled){
                //cout<<table[i].second<<" ";
                ans.push_back(table[i].second);
            }
        }
        sort(ans.begin(),ans.end());
        for(auto it: ans){
            cout<<it<<" ";
        }
        cout<<"\n";
    }
};

template <class T,class U>
T test (T x,U y) {
    pair<T,U> pr;
    pr={x,y};
    T z=pr.first+"cool";
    cout<<z<<"\n";
    return z;
    //cout<<pr.first+" "+pr.second;
}
typedef struct node{
    int data;
} node;
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
    for(int i=1;i<=100000;i++){
        st1.insert(i);
    }
    //cout<<st1.collision<<"\n";
    /*
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
    */






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

