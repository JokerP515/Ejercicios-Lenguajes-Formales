#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;
#define fast ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
void generateCombinations(const vector<char>& arr, int n, string prefix, vector<string>& combinations) {
    if (n == 0) {
        combinations.push_back(prefix);
        return;
    }
    for (char ch : arr) {
        generateCombinations(arr, n - 1, prefix + ch, combinations);
    }
}

vector<string> generateAllCombinations(const vector<char>& arr, int n) {
    vector<string> combinations;
    
    for (int length = 1; length <= n; ++length) {
        generateCombinations(arr, length, "", combinations);
    }
    return combinations;
}

vector<char> split(string& str){
    vector<char> res;
    stringstream ss(str);
    string cad;
    while(getline(ss,cad,' ')){
        if(!cad.empty()) res.push_back(cad[0]);
    }
    return res;
}

int main() {
    fast;
    vector<char> arr; 
    string A;
    
    getline(cin,A);
    arr = split(A);
    
    int n; 
    cin>>n;

    vector<string> combinations = generateAllCombinations(arr, n); 

    for(size_t i=0;i<combinations.size();i++){
        cout<<combinations[i];
        if(i!=combinations.size()-1) cout<<" ";
    }
    return 0;
}
