#include<iostream>
#include<regex>
#include<string>
using namespace std;
#define fast ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
int main(){
    fast;
    string cad;
    cin>>cad;
    
    const regex pattern("^[012](2)[012]*(1)[012]$|^12$");
    smatch arr;
    regex_search(cad,arr,pattern);
    if(!arr.empty()){
        cout<<"ACEPTA"<<endl;
    }else cout<<"RECHAZA"<<endl;
    return 0;
}