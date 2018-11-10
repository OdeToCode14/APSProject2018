#include<bits/stdc++.h>
#define upper_bound 0.7
#define lower_bound 0.2
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


    int calculate_hash(std::string key){

        double sum=0.0;
        for(int i=0;i<key.size();i++){
            sum = sum + key[i]*pow(47,i);
        }

        int final_hash=sum;

        return final_hash;
    }

    int calculate_hash(float key){

        const char * p = reinterpret_cast<const char*>(&key);
        std::string str =p;
        return calculate_hash(p);
    }

    int calculate_hash(double key){

        const char * p = reinterpret_cast<const char*>(&key);
        std::string str =p;
        return calculate_hash(p);
    }

    int get_hash_set_index(int key_hash){
        int index = ((key_hash%this->table_size)+this->table_size)%this->table_size;
        return index;
    }

    void rehash(){
        //std::cout<<"called"<<"\n";
        //take hold of old bucket
        int sz = sizeof(t_size)/sizeof(t_size[0]);

        if(this->t_size_index == sz-1){
            return;
        }
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

    void rehash_decrease(){
        //std::cout<<"called"<<"\n";
        //take hold of old bucket
        if(this->t_size_index == 0){
            return;
        }
        HashNode<K> **old_bucket = this->bucket;
        int old_table_size = this->getTableSize();

        this->t_size_index--;
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
            //std::cout<<this->getCurrentSize()<<endl;
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
                return;
            }

            //update hash table size
            
        }
       //std::cout<<"BF: "<<this->getLoadFactor()<<endl;
        //if balance factor > 0.7, rehash

        this->setCurrentSize(this->getCurrentSize()+1);
        double load_factor = (double)this->getCurrentSize()/this->getTableSize();
        this->setLoadFactor(load_factor);

        if(this->getLoadFactor()>upper_bound){
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
            double load_factor = (double)this->getCurrentSize()/this->getTableSize();
            this->setLoadFactor(load_factor);

        }

        if(this->getLoadFactor() < lower_bound){
            //rehash
            rehash_decrease();
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
        std::vector<K> arr;
        ///iterate over buckets
        for(int i=0;i<table_size;i++){
            ///print the list for each bucket
            HashNode<K>*entry = bucket[i];
            //std::cout<<"Bucket "<<i<<"->";
            while(entry!=NULL){
                arr.push_back(entry->getKey());
                //std::cout<<entry->getKey()<<" ";
                entry = entry->getNext();
            }
            //std::cout<<endl;
        }
        sort(arr.begin(),arr.end());
        for(int i=0;i<arr.size();i++){
            std::cout<<arr[i]<<" ";
        }
        std::cout<<"\n";
    }

    hash_set find_union(hash_set<K> other){
        hash_set<K> un;
        for(int i=0;i<this->table_size;i++){
            ///print the list for each bucket
            HashNode<K>*entry = this->bucket[i];
            while(entry!=NULL){
                //std::cout<<entry->getKey()<<":"<<entry->getValue()<<",";
                un.insert(entry->getKey());
                entry = entry->getNext();
            }
        }
        for(int i=0;i<other.table_size;i++){
            ///print the list for each bucket
            HashNode<K>*entry = other.bucket[i];
            while(entry!=NULL){
                //std::cout<<entry->getKey()<<":"<<entry->getValue()<<",";
                un.insert(entry->getKey());
                entry = entry->getNext();
            }
        }
        return un;
    }
    hash_set find_intersection(hash_set<K> other){
        hash_set<K> intr;
        hash_set<K> smaller;
        hash_set<K> bigger;
        if(this->getCurrentSize() <= other.getCurrentSize){
            smaller=this;
            bigger=other;
        }
        else{
            smaller=other;
            bigger=this;
        }
        for(int i=0;i<smaller.table_size;i++){
            ///print the list for each bucket
            HashNode<K>*entry = smaller.bucket[i];
            while(entry!=NULL){
                //std::cout<<entry->getKey()<<":"<<entry->getValue()<<",";
                if(bigger.find(entry->getKey())){
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
                //std::cout<<entry->getKey()<<":"<<entry->getValue()<<",";
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
    return 0;
}