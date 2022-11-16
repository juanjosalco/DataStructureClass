/// Act 4.3 - Comprehensive Graph Activity (Competence evidence)
/// Author: Juan Jose Salazar Cortes
/// Author: Mariana Esquivel Hernandez
/// date: 11/15/2022

// Abra el archivo de entrada llamado "bitacora.txt Download bitacora.txt Vista previa del documento" 
// lealo y almacene los datos en en una lista de adyacencia organizada por dirección de ip origen 
// (Formato del archivo bitacora.pdf Download Formato del archivo bitacora.pdfVista previa del documento). 
// Por ejemplo la lista 192.168.1.3 => {192: 168, 168:1, 1:3}

// Determine el degree y el outdegree de cada nodo
// ¿Qué nodos tienen el mayor degree y cuales el mayor outdegree?


//#include <bits/stdc++.h>

// No se cuales librerias si borrar. Por el momento NO BORRAR NINGUNA
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <typeinfo>
#include <queue>
#include <map>
#include <array>
#include <list>
#include <stdio.h>
#include <string.h>
#include <cstring>

using namespace std;

class Graph
{
private:
    int numVertices;
    vector<int> *adjList;
    bool *visited;
    int **matrixDegreeList;
    // int **adjMatrix;

public:
    Graph(int V)
    {
        numVertices = V;
        adjList = new vector<int>[numVertices];
        visited = new bool[V];
        matrixDegreeList = new int*[numVertices];
        for(int i = 0; i < numVertices; i++){
            matrixDegreeList[i] = new int[2];
            matrixDegreeList[i][0] = 0;
            matrixDegreeList[i][1] = 0;
        }
    }

    ~Graph()
    {
        delete[] adjList;
        delete[] visited;
        delete[] matrixDegreeList;
    }
    void loadGraph(int a, int b);
    void resetVisited();
    void printGraph();
    void printDegreeNodes();
    void maxAndMinDegree();
};

void Graph::loadGraph(int a, int b){
    for(int i = 0; i < adjList[a].size(); i++){
        if(adjList[a][i] == b){
            return;
        }
    }
    adjList[a].push_back(b);
    matrixDegreeList[a][0]++;
    matrixDegreeList[b][1]++;
} // Complexity O(1)

void Graph::resetVisited()
{
    for (int i = 0; i < this->numVertices; i++)
        this->visited[i] = false;
} // Complexity O(V)

void Graph::printGraph()
{
    for (int i = 1; i < this->numVertices; i++)
    {
        cout << "\nVertex " << i << ":";
        for (auto x : this->adjList[i])
            cout << " -> " << x;
        cout << endl;
    }
} // Time Complexity O(n)

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
} // Time Complexity O(n)

// Take the IP without the port 
string getIPAccess(string IP){
    string access;
    for(int i = 0; i <= IP.length()-6; i++){
        access += IP[i];
    }
    return access;
} // Time Complexity O(n)

void Graph::maxAndMinDegree(){
    int maxInDegree = 0, maxOutDegree = 0, cont1 = 0, cont2 = 0;
    for(int i = 0; i < numVertices; i++){
        if(matrixDegreeList[i][0] > maxInDegree){
            maxInDegree = matrixDegreeList[i][0];
            cont1 = i;
        }
        if(matrixDegreeList[i][1] > maxOutDegree){
            maxOutDegree = matrixDegreeList[i][1];
            cont2 = i;
        }
    }
    cout << "The Node With More OutDegree is: " << cont1 << " with: " << maxInDegree << endl;
    cout << "The Node With More InDegree is: " << cont2 << " with "<< maxOutDegree << endl<<endl;
}; //Time Complexity: O(n) 

void Graph::printDegreeNodes(){
    cout << "------------------------------------------" << endl;
    cout << "Node\t\tOutDegree\tInDegree" << " | " << endl;
    cout << "------------------------------------------" << endl;
    for(int i = 0; i < numVertices; i++){
        cout << i << "\t\t"<< matrixDegreeList[i][0] << "\t\t" << matrixDegreeList[i][1] << "\t | " << endl;
    }
    cout << "------------------------------------------" << endl;
} // Time Complexity: O(n) 

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
    int val = 0;

    // Do not be afraid of what is happening here
    // You are safe now my child
    while(getline(OurReadFile,line)){
        IPnumber = getIPAccess(getIP(line));
        //Time complexity: O(n log n)
        string s = IPnumber;
        //a function to convert the string "1.2.3.4" to a char array
        char* char_arr;
        string str_obj(s);
        char_arr = &str_obj[0];
        //create a vector of char* to hold the tokens
        vector<char*> v;
        char * pch;
        pch = strtok (char_arr,".");
        while (pch != NULL)
        {
        v.push_back(pch);
        pch = strtok (NULL, " ,.-");
        }
        for(int i=0; i<v.size(); i++)
        {
            int val = i;
            int value1 = atoi(v[val]);
            int value2 = 0;
            if(val + 1 < v.size())
            {
                int value2 = atoi(v[val+1]);
                g.loadGraph(value1, value2);
            }
            else
            {
                g.loadGraph(value2, 0);  
            }
        }
    }
    OurReadFile.close();
    cout << "\n------ List With In and Out Degrees ------\n" << endl;
    g.printDegreeNodes();
    cout << "\n--- Nodes With More In And Out Degrees ---\n" << endl;
    g.maxAndMinDegree();
    return 0;
}