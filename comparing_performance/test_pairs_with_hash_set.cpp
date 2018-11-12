#include <bits/stdc++.h>
#include "hash_set.h"

#include <chrono>

using namespace std;
using namespace std::chrono; 

typedef long long ll;
vector<string> split_string(string);

// Complete the pairs function below.
int pairs(int k, vector<int> arr) {
    hash_set<int> st;
    int ans=0;
    for(int i=0;i<arr.size();i++){
        int req=arr[i]-k;
        //cout<<"first "<<i<<" "<<req<<"\n";
        if(st.find(req)){
            ans++;
        }
        req=k+arr[i];
        //cout<<i<<" "<<req<<"\n";
        if(st.find(req)){
            ans++;
        }
        //cout<<"second "<<i<<" "<<ans<<"\n";
        st.insert(arr[i]);
    }
    return ans;
}

int main()
{
    ofstream out;
    out.open("output_pairs_with_hash_set.txt");

    ifstream in ("pairs_test_file.txt");

    string nk_temp;
    getline(in, nk_temp);

    vector<string> nk = split_string(nk_temp);

    int n = stoi(nk[0]);

    int k = stoi(nk[1]);

    string arr_temp_temp;
    getline(in, arr_temp_temp);

    vector<string> arr_temp = split_string(arr_temp_temp);

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        int arr_item = stoi(arr_temp[i]);

        arr[i] = arr_item;
    }

    auto start = high_resolution_clock::now();

    int result = pairs(k, arr);

    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start);
    //cout<<"number of collisions "<<hs_st3.collision<<"\n";
    cout << "Time taken by  hash_set for pairs problem on this file: "<< duration.count() << " microseconds\n";
    out << result << "\n";
    in.close();
    out.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
