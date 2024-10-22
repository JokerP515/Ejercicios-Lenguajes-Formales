#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<limits>
#include<map>
#include<algorithm>
#include<unordered_set>
#include<set>
using namespace std;
#define fast ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);

vector<string> splitString(string& str){
    vector<string> res;
    stringstream ss(str);
    string cad;
    while(getline(ss,cad,' ')){
        if(!cad.empty() && cad!="|") res.push_back(cad);
    }
    return res;
}

unordered_set<char> verifyTerminable(vector<pair<char,vector<string>>>& gram){
    unordered_set<char> terminable;
    // Primer barrido verificando solo minusculas
    for(auto& it : gram){ // pair< char, vector<string> >
        for(auto it2 : it.second){ // vector<string>
            bool flag = true;
            for(size_t i=0;i<it2.size();++i){ //string
                if(isupper(it2[i])){
                    flag = false;
                    break;
                }
            }
            if(flag) terminable.insert(it.first);
        }
    }
    size_t sizeAux=0;
    // Segundo y ultimo barrido verificando mayusculas
    while(sizeAux!=terminable.size()){
        sizeAux = terminable.size();
        for(auto& it : gram){ // pair< char, vector<string> >
            for(auto it2 : it.second){ // vector<string>
                bool flag = true;
                for(size_t i=0;i<it2.size();++i){ //string
                    if(isupper(it2[i]) && terminable.find(it2[i])==terminable.end()){
                        flag = false;
                        break;
                    }
                }
                if(flag) terminable.insert(it.first);
            }
        }
    }
    return terminable;
}

int main(){
    fast;
    int n=0;
    cin>>n;

    if(n<=0 || cin.fail()) return 0;

    vector<pair<char,vector<string>>> gramProductions; //Gramatica con producciones
    vector<char> gram; // Gramatica sin producciones
    cin.ignore(numeric_limits<streamsize>::max(),'\n');

    for(int i=0;i<n;i++){
        string cad = "";
        getline(cin,cad);
        auto it = cad.find("->");
        string left = cad.substr(0,it);
        string right = cad.substr(it+2);
        vector<string> arr = splitString(right);
        gramProductions.push_back({left[0],arr}); //Gramatica con producciones
        gram.push_back(left[0]);
    }

    
    vector<char> notTerminable;
    unordered_set<char> terminable = verifyTerminable(gramProductions);
    for(auto it : gram) if(terminable.find(it)==terminable.end()) notTerminable.push_back(it);


    cout<<"{";
    size_t i = 0;
    for(auto it = notTerminable.begin() ; it != notTerminable.end() ; ++it, ++i){
        cout << *it;
        if(i != notTerminable.size()-1){
            cout<<",";
        }
    }
    cout<<"}"<<endl;
    return 0;
}