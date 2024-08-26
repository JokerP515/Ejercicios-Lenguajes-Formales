#include<iostream>
#include<string>
using namespace std;
#define fast ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
int main(){
    fast;
    string cad;
    bool res = false;
    cin>>cad;
    if(cad.size()>1){
        if(cad[1]=='2' && cad[cad.size()-2]=='1'){
            res = true;
        }
    }
    if(res){
        cout<<"ACEPTA"<<endl;
    }else cout<<"RECHAZA"<<endl;
    return 0;
}