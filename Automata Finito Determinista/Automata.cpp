#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<limits>
#include<unordered_map>
#include<algorithm>
using namespace std;
#define fast ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);

vector<char> splitChar(string& str){
    vector<char> res;
    stringstream ss(str);
    string cad;
    while(getline(ss,cad,' ')){
        if(!cad.empty()) res.push_back(cad[0]);
    }
    return res;
}

vector<string> splitString(string& str){
    vector<string> res;
    stringstream ss(str);
    string cad;
    while(getline(ss,cad,' ')){
        if(!cad.empty()) res.push_back(cad);
    }
    return res;
}

string verify(unordered_map<string, unordered_map<char,string>>& listAdj,string& cad,string& initialS,vector<string>& finalS){
    string actualS = initialS;
    bool k = true;
    for(char& c : cad){
        if(listAdj[actualS].find(c) != listAdj[actualS].end()){
            actualS = listAdj[actualS][c];
        }else{
            k=false; //It will give problems if lambda = &
            break;
        }
    }
    auto it = find(finalS.begin(),finalS.end(),actualS);
    if(it != finalS.end() && k){
        return "ACEPTADA";
    }else return "RECHAZADA";
}

int main(){
    fast;
    string lang,states,initialS,finalS,trans;
    int n=0;
    
    unordered_map<string, unordered_map<char,string>> listAdj;
    
    getline(cin,lang);
    vector<char> L = splitChar(lang);
    
    getline(cin,states);
    vector<string> st = splitString(states);


    cin>>initialS;
    cin.ignore(numeric_limits<streamsize>::max(),'\n'); //It will clean the buffer to keep using getline

    getline(cin,finalS);
    vector<string> fst = splitString(finalS);

    getline(cin,trans);
    vector<string> tr = splitString(trans);

    //This will separate all the transitions and it will put them inside listAdj
    for(string& s : tr){
        auto it = s.find(',');
        auto it2 = s.find("->");
        string state = s.substr(0,it);
        char letter = s[it+1];
        string next = s.substr(it2+2);
        listAdj[state][letter] = next;
    }

    cin>>n;
    if(n>0){
        vector<string> s(n);
        for(int i=0;i<n;i++){
            cin>>s[i];
        }

        for(string& aux : s){
            string ver = verify(listAdj,aux,initialS,fst);
            cout<<ver<<endl;
        }
    }
    return 0;
}