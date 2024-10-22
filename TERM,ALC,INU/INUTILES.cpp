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
// Alcanzables
void verifyWithDFS(char node, map<char,unordered_set<char>>& adjList, unordered_set<char>& visited){
    visited.insert(node);
    for(char neighbor : adjList[node]){
        if(visited.find(neighbor)==visited.end()) verifyWithDFS(neighbor,adjList,visited);
    }
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

vector<pair<char,vector<string>>> deleteUseless(vector<char>& gram, vector<pair<char,vector<string>>>& gramProductions, unordered_set<char>& notTerminable, unordered_set<char>& notReachable){
    vector<pair<char,vector<string>>> newGramProductions; // Gramatica con producciones
    vector<char> newGram; // Gramatica sin producciones
    vector<char> newGram2; // Gramatica sin producciones

    // Primero la limpieza de los notTerminables
    for(char& c : gram){
        if(notTerminable.find(c)==notTerminable.end()){
            newGram.push_back(c);
        }
    }
    // Limpieza de los notReachables
    for(char& c : newGram){
        if(notReachable.find(c)==notReachable.end()){
            newGram2.push_back(c);
        }
    }
    // Reconstruccion de la gramatica con newGram2
    for(auto& it : gramProductions){ // pair<char,vector<string>>
        if(find(newGram2.begin(),newGram2.end(),it.first) != newGram2.end()){
            vector<string> temp;
            for(auto& it2 : it.second){ // vector<string>
                bool flag = true;
                for(size_t i=0;i<it2.size();++i){ //string
                    if(isupper(it2[i]) && find(newGram2.begin(),newGram2.end(),it2[i]) == newGram2.end()){
                        flag = false;
                        break;
                    }
                }
                if(flag) temp.push_back(it2);
            }
            newGramProductions.push_back({it.first,temp});
        }
    }

    return newGramProductions;
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


    //INICIO NO ALCANZABLES
    map<char,unordered_set<char>> AdjList; // Lista de adyacencia
    for(auto it:gramProductions){
        for(auto it2 : it.second){
            for(char& c : it2) if(isupper(c)) AdjList[it.first].insert(c);
        }
    }

    char initialNode = 'S';
    unordered_set<char> visited;
    verifyWithDFS(initialNode,AdjList,visited);

    unordered_set<char> notReachable;
    for(char node : gram) if(visited.find(node) == visited.end()) notReachable.insert(node);
    // FIN NO ALCANZABLES
    
    //INICIO NO TERMINABLE
    unordered_set<char> notTerminable;
    unordered_set<char> terminable = verifyTerminable(gramProductions);
    for(auto it : gram) if(terminable.find(it)==terminable.end()) notTerminable.insert(it);
    // FIN NO TERMINABLE

    vector<pair<char,vector<string>>> notUseless = deleteUseless(gram,gramProductions,notTerminable,notReachable);
    for(auto& it : notUseless){
        cout<<it.first<<" -> ";
        size_t i = 0;
        for(auto it2 = it.second.begin() ; it2 != it.second.end() ; ++it2, ++i){
            cout << *it2;
            if(i != it.second.size()-1){
                cout<<" | ";
            }
        }
        cout<<endl;
    }
    return 0;
}