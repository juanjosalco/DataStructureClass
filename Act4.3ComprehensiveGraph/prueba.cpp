#include <bits/stdc++.h>

// No se cuales librerias si borrar. Por el momento NO BORRAR NINGUNA
// #include <iostream>
// #include <string>
// #include <vector>
// #include <fstream>
// #include <algorithm>
// #include <typeinfo>
// #include <queue>
// #include <map>
// #include <array>
// #include <list>
// #include <stdio.h>
// #include <string.h>
// #include <cstring>

using namespace std;

class Graph
{
private:
    int numNodes;
    vector<int> *adjList;
    bool *visited;
    int **degreeList;
    // int **adjMatrix;

public:
    Graph(int V)
    {
        numNodes = V;
        adjList = new vector<int>[numNodes];
        visited = new bool[V];
        degreeList = new int*[numNodes];
        for(int i = 0; i < numNodes; i++){
                degreeList[i] = new int[2];
                degreeList[i][0] = 0;
                degreeList[i][1] = 0;
            }
    }

    ~Graph()
    {
        delete[] adjList;
        delete[] visited;
    }
    void loadGraph(int a, int b);
    void resetVisited();
    void printGraph();
    void nodeDegree();
    void InOutDegree();
};

void Graph::loadGraph(int a, int b){
    for(int i = 0; i < adjList[a].size(); i++){
        if(adjList[a][i] == b){
            return;
        }
    }
    adjList[a].push_back(b);
    degreeList[a][0]++;
    degreeList[b][1]++;
} // Complexity O(1)

void Graph::resetVisited()
{
    for (int i = 0; i < this->numNodes; i++)
        this->visited[i] = false;
} // Complexity O(V)

void Graph::printGraph()
{
    for (int i = 1; i < this->numNodes; i++)
    {
        cout << "\nVertex " << i << ":";
        for (auto x : this->adjList[i])
            cout << " -> " << x;
        cout << endl;
    }
}// Complexity O(V + E)

void Graph::InOutDegree(){
    int maxIn = 0;
    int maxOut = 0; 
    int indexBeg = 0;
    int indexEnd = 0;
    for(int i = 0; i < numNodes; i++){
        if(degreeList[i][0] > maxIn){
            maxIn = degreeList[i][0];
            indexBeg = i;
        }
        if(degreeList[i][1] > maxOut){
            maxOut = degreeList[i][1];
            indexEnd = i;
        }
    }
    cout << "\tMax Outdegree -> : '" << maxIn << "'  from Node: '" << indexBeg << "'" << endl;
    cout << "\n\tMax Indegree  <- : '" << maxOut << "'  from Node: '" << indexEnd << "'\n" << endl;
};// Time Complexity O(V); O👎

void Graph::nodeDegree(){
    for(int i = 0; i < numNodes; i++){
        cout << "Element from the IP: '" << i << "'\t Outdegree -> : '" << degreeList[i][0] <<
         "'\t Indegree <- : '" << degreeList[i][1] << "'"<< endl;
    }// Time Complexity O(V); O👎
}

// Take the IP from the line 
string getIP(string record){
    long long contEsp = 0;
    long long indexBeg;
    long long indexEnd;
    bool aux = true;
    bool aux2 = true;
    for(long long i = 0; i < record.length(); i++){
        if(record[i] == ' ') contEsp ++;
        if(contEsp == 3 && aux){
            indexBeg = i + 1 , aux = false;
        }
        if(contEsp == 4 && aux2){
            indexEnd = i - indexBeg , aux2 = false;
        }
    }
    return record.substr(indexBeg, indexEnd); // "112.12.122.12.1111"
} // Time Complexity O👎

// Take the IP without the port 
string getIPAccess(string IP){
    string access;
    for(int i = 0; i <= IP.length()-6; i++){
        access += IP[i];
    }
    return access;
} // Time Complexity O👎


int main(){
    fflush(stdin);
    Graph g(999);
    vector<string> info;
    vector<string> IP;
    string record;
    ifstream OurReadFile("bitacora.txt");
    vector<string> lines;
    string line;
    string IPnumber;
    int num = 0;

    // Do not be afraid of what is happening here
    // You are safe now my child
    while(getline(OurReadFile,line)){
        IPnumber = getIPAccess(getIP(line));
        //Time complexity: O(n log n)
        string s = IPnumber;
        //a function to convert the string "1.2.3.4" to a char array
        char* charArray;
        string str_obj(s);
        charArray = &str_obj[0];
        //create a vector of char* to hold the tokens
        vector<char*> v;
        char * pch;
        pch = strtok (charArray,".");
        while (pch != NULL)
        {
        v.push_back(pch);
        pch = strtok (NULL, " ,.-");
        }
        for(int i=0; i<v.size(); i++)
        {
            int num = i;
            int vertex = atoi(v[num]);
            int value = 0;
            if(num + 1 < v.size())
            {
                int value = atoi(v[num+1]);
                g.loadGraph(vertex, value);
            }
            else
            {
                g.loadGraph(value, 0);  
            }
        }
    }
    //g.printGraph(); //Ver el grafo en consola
    OurReadFile.close();
    cout << "\n---------------------------------- Degree List --------------------------------\n" << endl;
    g.nodeDegree();
    cout << "\n---------------------------------- Max. In & Out Degrees --------------------------------\n" << endl;
    g.InOutDegree();
    return 0;
}