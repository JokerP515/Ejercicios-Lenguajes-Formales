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
void verifyWithDFS(char node, map<char,unordered_set<char>>& adjList, unordered_set<char>& visited){
    visited.insert(node);
    for(char neighbor : adjList[node]){
        if(visited.find(neighbor)==visited.end()) verifyWithDFS(neighbor,adjList,visited);
    }
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

    map<char,unordered_set<char>> AdjList; // Lista de adyacencia
    for(auto it:gramProductions){
        for(auto it2 : it.second){
            for(char& c : it2) if(isupper(c)) AdjList[it.first].insert(c);
        }
    }

    char initialNode = 'S';
    unordered_set<char> visited;
    verifyWithDFS(initialNode,AdjList,visited);

    vector<char> notReachable;
    for(char node : gram){
        if(visited.find(node) == visited.end()) notReachable.push_back(node);
    }
    
    cout<<"{";
    size_t i = 0;
    for(auto it = notReachable.begin() ; it != notReachable.end() ; ++it, ++i){
        cout << *it;
        if(i != notReachable.size()-1){
            cout<<",";
        }
    }
    cout<<"}"<<endl;
    return 0;
}