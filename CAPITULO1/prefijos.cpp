#include<iostream>
#include<string>
#include<vector>
using namespace std;
#define fast ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
int main(){
    fast;
    string cad;
    cin>>cad;
    vector<string> arr;
    for(size_t i=cad.size();i>0;i--){
        arr.push_back(cad.substr(0,i));
    }
    for(string& c : arr){
        cout<<c<<endl;
    }
}