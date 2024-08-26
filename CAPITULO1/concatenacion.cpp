#include<iostream>
#include<string>
#include<vector>
#include<sstream>
using namespace std;
#define fast ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
vector<string> split(string& str){
    vector<string> res;
    stringstream ss(str);
    string cad;
    while(getline(ss,cad,' ')){
        if(!cad.empty()) res.push_back(cad);
    }
    return res;
}
int main(){
    fast;
    string A,B;
    vector<string> LA,LB,LAB;
    getline(cin,A);
    getline(cin,B);

    LA = split(A);
    LB = split(B);

    for(string& a : LA){
        for(string& b : LB){
            LAB.push_back(a+b);
        }
    }
    for(size_t i=0;i<LAB.size();i++){
        cout<<LAB[i];
        if(i!=LAB.size()-1) cout<<" ";
    }
    return 0;
}
