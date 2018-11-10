#include<bits/stdc++.h>
#include<chrono>
using namespace std::chrono;
using namespace std;
int t_size[]={7,17,37,79,163,6,673,1361,2729,5471,10949,21911,43853,87719,175447,350899,701819,1403641,2807303,5614657,11229331};
template <typename K>
class HashNode{

    private:
    // key - value pair to be stored in the map
    K key;
    //V value;
    //pointer to next node with the same key-hash
    HashNode *next;
    //hash of key
    int hash;

    public:
    HashNode (const K &key){
        this->key = key;
        //this->value = value;
        this->next = NULL;
    }

    K getKey() const{
        return key;
    }

    /*V getValue() const{
        return value;
    }*/

    /*void setValue(V value){
        this->value=value;
    }*/

    HashNode *getNext() const{
        return next;
    }

    void setNext(HashNode *next){
        this->next = next;
    }

    void setHash(int hash){
        this->hash = hash;
    }

    int getHash(){
        return hash;
    }


};

template <typename K>
class hash_set {

    private:

    int current_size;
    int table_size;
    double load_factor;
    HashNode<K> **bucket;
    int t_size_index=0;
    public:

    hash_set(int table_size=7){
        current_size = 0;
        this->load_factor=0;
        this->table_size = table_size;
        bucket = new HashNode<K> *[table_size];
        for(int i=0;i<table_size;i++){
            bucket[i]=NULL;
        }
    }

    int getCurrentSize(){
        return current_size;
    }

    void setCurrentSize(int c_size){
        current_size = c_size;
    }

    int getTableSize(){
        return table_size;
    }

    void setTableSize(int table_size){
        this->table_size = table_size;
    }

    double getLoadFactor(){
        return load_factor;
    }

    void setLoadFactor(double load_factor){
        this->load_factor = load_factor;
    }

    int calculate_hash(int key){

        int n = key;
        int exp=0;
        long long hash=0;
        while(n!=0){
            int digit = n%10;
            hash+= digit * pow(37,exp);
            n=n/10;
            exp++;
        }

        int final_hash = (int) hash;
        return final_hash;
    }


    int calculate_hash(string key){

        double sum=0.0;
        for(int i=0;i<key.size();i++){
            sum = sum + key[i]*pow(47,i);
        }

        int final_hash=sum;

        return final_hash;
    }

    int calculate_hash(float key){

        const char * p = reinterpret_cast<const char*>(&key);
        string str =p;
        return calculate_hash(p);
    }

    int calculate_hash(double key){

        const char * p = reinterpret_cast<const char*>(&key);
        string str =p;
        return calculate_hash(p);
    }

    int get_hash_set_index(int key_hash){
        int index = ((key_hash%this->table_size)+this->table_size)%this->table_size;
        return index;
    }

    void rehash(){
        //cout<<"called"<<"\n";
        //take hold of old bucket
        HashNode<K> **old_bucket = this->bucket;
        int old_table_size = this->getTableSize();

        this->t_size_index++;
        //set current size to zero
        //this->setCurrentSize(0);

        //find new table size
        int new_table_size = t_size[t_size_index];
        //initialize new hash table with increased size.
        HashNode<K> **new_bucket = new HashNode<K> *[new_table_size];
        this->setTableSize(new_table_size);


        //set the new bucket to the hash table
        this->bucket = new_bucket;
        this->setCurrentSize(0);
        for(int i=0;i<new_table_size;i++){
            new_bucket[i] = NULL;
        }
        //iterate through the old table
        for(int i=0;i<old_table_size;i++){
            HashNode<K> *entry = old_bucket[i];
            //if chain exists, then iterate over it and rehash into new table
            while(entry!=NULL){
                 insert(entry->getKey());
                 entry = entry->getNext();
            }

            delete old_bucket[i];
        }
        //this->print();
        delete [] old_bucket;
    }


    void insert(const K key) {
        int key_hash = calculate_hash(key);

        int index = get_hash_set_index(key_hash);

        HashNode<K> *entry = bucket[index];

        if(entry==NULL){

            entry = new HashNode<K>(key);
            entry->setHash(key_hash);
            bucket[index] = entry;
            //update the hash table size
            this->setCurrentSize(this->getCurrentSize()+1);
            //cout<<this->getCurrentSize()<<endl;
            double load_factor = (double)this->getCurrentSize()/this->getTableSize();
            this->setLoadFactor(load_factor);

        }else{

            //check if same key already exists
            HashNode<K> *prev = NULL;

            while (entry != NULL && entry->getKey() != key) {
                prev = entry;
                entry = entry->getNext();
        }
            if(entry==NULL){ //identical key was not found, but chain exits, so, add in front
                entry = new HashNode<K>(key);
                prev->setNext(entry);
                entry->setHash(key_hash);
                //entry = newEntry;

            }else{ // identical key was found, update it.
                //entry->setValue(value);
            }

            //update hash table size
            this->setCurrentSize(this->getCurrentSize()+1);
            double load_factor = (double)this->getCurrentSize()/this->getTableSize();
            this->setLoadFactor(load_factor);
        }
       //cout<<"BF: "<<this->getLoadFactor()<<endl;
        //if balance factor > 0.7, rehash

        if(this->getLoadFactor()>0.7){
            //rehash
            rehash();
        }


    }

    void erase(const K &key) {
        int hash = this->calculate_hash(key);
        int table_index = get_hash_set_index(hash);
        HashNode<K> *prev = NULL;
        HashNode<K> *entry = bucket[table_index];

        while (entry != NULL && entry->getKey()!= key) {
            prev = entry;
            entry = entry->getNext();
        }

        if (entry == NULL) {
            // key not found
            return;
        }
        else {
            if (prev == NULL) {
                // remove first bucket of the list
                bucket[table_index] = entry->getNext();
            } else {
                prev->setNext(entry->getNext());
            }
            delete entry;
            this->setCurrentSize(this->getCurrentSize()-1);
        }
    }


    bool find(const K key) {
        int key_hash = calculate_hash(key);
        int index = get_hash_set_index(key_hash);
        HashNode<K> *entry = bucket[index];
        while(entry!=NULL){
            if(entry->getKey()==key){
                return true;
            }
            entry = entry->getNext();
        }
        return false;
    }

    void print(){
        vector<K> arr;
        ///iterate over buckets
        for(int i=0;i<table_size;i++){
            ///print the list for each bucket
            HashNode<K>*entry = bucket[i];
            //cout<<"Bucket "<<i<<"->";
            while(entry!=NULL){
                arr.push_back(entry->getKey());
                //cout<<entry->getKey()<<" ";
                entry = entry->getNext();
            }
            //cout<<endl;
        }
        sort(arr.begin(),arr.end());
        for(int i=0;i<arr.size();i++){
            cout<<arr[i]<<" ";
        }
        cout<<"\n";
    }

    hash_set find_union(hash_set<K> other){
        hash_set<K> un;
        for(int i=0;i<this->table_size;i++){
            ///print the list for each bucket
            HashNode<K>*entry = this->bucket[i];
            while(entry!=NULL){
                //cout<<entry->getKey()<<":"<<entry->getValue()<<",";
                un.insert(entry->getKey());
                entry = entry->getNext();
            }
        }
        for(int i=0;i<other.table_size;i++){
            ///print the list for each bucket
            HashNode<K>*entry = other.bucket[i];
            while(entry!=NULL){
                //cout<<entry->getKey()<<":"<<entry->getValue()<<",";
                un.insert(entry->getKey());
                entry = entry->getNext();
            }
        }
        return un;
    }
    hash_set find_intersection(hash_set<K> other){
        hash_set<K> intr;
        for(int i=0;i<this->table_size;i++){
            ///print the list for each bucket
            HashNode<K>*entry = this->bucket[i];
            while(entry!=NULL){
                //cout<<entry->getKey()<<":"<<entry->getValue()<<",";
                if(other.find(entry->getKey())){
                    intr.insert(entry->getKey());
                }
                entry = entry->getNext();
            }
        }
        return intr;
    }
    
    hash_set find_difference(hash_set<K> other){
        hash_set<K> diff;
        for(int i=0;i<this->table_size;i++){
            ///print the list for each bucket
            HashNode<K>*entry = this->bucket[i];
            while(entry!=NULL){
                //cout<<entry->getKey()<<":"<<entry->getValue()<<",";
                if(!other.find(entry->getKey())){
                    diff.insert(entry->getKey());
                }
                entry = entry->getNext();
            }
        }
        return diff;
    }

    bool empty(){
        if(getCurrentSize() == 0){
            return true;
        }
        else{
            return false;
        }
    }
    


};



int main(){
    //int left=1,right=1000000;
  int left=1,right=100;
  int pos=0;
    vector<int> arr(right-left+1);
    for(int i=left;i<=right;i++){
        arr[pos++]=i;
    }
    random_shuffle(arr.begin(),arr.end());

    hash_set<int> st1;
    for(int i=0;i<arr.size();i++){
        st1.insert(arr[i]);
    }

  //file << "Please writr this text to a file.\n this text is written using C++\n";


  //left=500001,right=1500000;
  left=51,right=150;
  vector<int> arr2(right-left+1);
  pos=0;
  for(int i=left;i<=right;i++){
    arr2[pos++]=i;
  }
  random_shuffle(arr2.begin(),arr2.end());
  hash_set<int> st2;
    for(int i=0;i<arr2.size();i++){
        st2.insert(arr2[i]);
    }  

    auto start = high_resolution_clock::now();
    hash_set<int> st3=st1.find_union(st2);
    //st3.print();
    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by hash_set_chaining find_union: "<< duration.count() << " microseconds\n";


    start = high_resolution_clock::now();
    hash_set<int> st4=st1.find_intersection(st2);
    //st3.print();
    stop = high_resolution_clock::now(); 
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by hash_set_chaining find_intersection: "<< duration.count() << " microseconds\n";
    //st4.print();

    start = high_resolution_clock::now();
    hash_set<int> st5=st1.find_difference(st2);
    //st3.print();
    stop = high_resolution_clock::now(); 
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by hash_set_chaining find_intersection: "<< duration.count() << " microseconds\n";
    st5.print();
    /*
    hash_set<int> hmap;
//    int n;
//    cin>>n;
    auto start = high_resolution_clock::now();
    for(int i=0;i<1000000;i++){
        hmap.insert(i);
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop-start);
    cout<<duration.count()<<" microseconds\n";
    */

//    int q;
//    cin>>q;
//    while(q--){
//        int num;
//        cin>>num;
//
//         HashNode<int,string> *entry = hmap.get(num);
//         if(entry!=NULL)
//            cout<<entry->getValue()<<"\n";
//    }

//     for(int i=1;i<=100000;i++){
//     	hmap.insert(i, i);
//     }
//   // hmap.print();
//     for(int i=4;i<=100000;i=i+4){
//     	hmap.remove(i);
//     }
//     HashNode<int,int> *entry = hmap.get(99);
//       if(entry==NULL){
//       	cout<<"Not found\n";
//       }else{
//       	cout<<"Found\n";
//       }




























//    	hmap.remove(i);
//    }
//    HashNode<int,int> *entry = hmap.get(99);
//    if(entry==NULL){
//    	cout<<"Not found\n";
//    }else{
//    	cout<<"Found\n";
//    }

//    cout<<"map1 \n";
//    hmap2.insert(1,1);
//    hmap2.insert(2,2);
//    hmap2.insert(3,2);
//    hmap2.insert(4,2);
//    hmap2.insert(5,2);
//    hmap2.insert(6,2);
//
//    hash_set<int, int> hmap;
//    cout<<"map2 \n";
//    hmap.insert(1,1);
//    hmap.insert(2,2);
//    hmap.insert(3,2);
//    hmap.insert(4,2);
//    hmap.insert(5,2);
//    hmap.insert(6,2);
//    hmap.insert(7,2);
//    hmap.insert(8,2);
//    hmap.insert(9,2);
//    hmap.print();
//    hmap.remove(5);
//    hmap.print();
//    HashNode<int,int> *node = hmap.get(2);
//    cout<<"Value: "<<node->getValue();
    // int size_of_table = hmap2.getTableSize();
    //  HashNode<int,int> *entry2 = hmap2.get(1);
    //  cout<<entry2->getKey()<<" "<<entry2->getValue()<<" "<<endl;

    //  HashNode<int,int> *entry3 = hmap2.get(2);
    //  cout<<entry3->getKey()<<" "<<entry3->getValue()<<" "<<endl;

    //  HashNode<int,int> *entry4 = hmap2.get(3);
    //  cout<<entry4->getKey()<<" "<<entry4->getValue()<<" "<<endl;

    //   entry2 = hmap2.get(4);
    //   cout<<entry2->getKey()<<" "<<entry2->getValue()<<" "<<endl;

     //entry2 = hmap2.get(5);
    // cout<<entry2->getKey()<<" "<<entry2->getValue()<<" "<<endl;

//      cout<<"Map3: \n";
//      hash_set<string, int> smap;
//      smap.insert("hi",1);
//      smap.insert("bye",2);
//      smap.insert("tie",3);
//      smap.insert("pie",223);
//      smap.insert("sigh",25);
//
//      cout<<"Map4: \n";
//      hash_set<string, int> smap1;
//      smap1.insert("thi",1);
//      smap1.insert("tbye",2);
//      smap1.insert("ttie",3);
//      smap1.insert("tpie",223);
//      smap1.insert("tsigh",256);
//      smap1.insert("igh",2569874);
//      smap1.insert("gh",2569874);
//      smap1.insert("h",2569874);
//
//      cout<<"Map5: \n";
//      hash_set<float, int> dmap;
//      dmap.insert(5.5f,2000);
//      dmap.print();


    return 0;

}

