#include<iostream>
#include<string>
#include<regex>
using namespace std;
#define fast ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
int main(){
    fast;
    string cad;
    cin>>cad;
    //const regex pattern2("^([bc]*a[bc]*a[bc]*)*$|^c*$ "); //Patron que acepta las A par
    const regex pattern3("^([bc]*a[bc]*a[bc]*)*$|^c*$|^[ac]*b([ac]*b[ac]*b[ac]*)*$"); //Patron que acepta las A par y B impar
    smatch arr;
    regex_search(cad,arr,pattern3);
    if(!arr.empty()){
        cout<<"ACEPTA"<<endl;
    }else cout<<"RECHAZA"<<endl;
    return 0;
}

