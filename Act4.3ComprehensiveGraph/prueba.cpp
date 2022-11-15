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
    list<int> *adjList;
    bool *visited;
    // int **adjMatrix;

public:
    Graph(int V)
    {
        numVertices = V;
        adjList = new list<int>[V];
        visited = new bool[V];
    }

    ~Graph()
    {
        delete[] adjList;
        delete[] visited;
    }
    void loadGraph(int a, int b);
    void resetVisited();
    void printGraph();
};

void Graph::loadGraph(int a, int b){
    adjList[a].push_back(b);
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
} // Time Complexity O(n)

// Take the IP without the port 
string getIPAccess(string IP){
    string access;
    for(int i = 0; i <= IP.length()-6; i++){
        access += IP[i];
    }
    return access;
} // Time Complexity O(n)

int main(){
    fflush(stdin);
    Graph g(1000);
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
    g.printGraph(); //Quitar si quieres dejar de ver el grafo en consola
    OurReadFile.close();
    return 0;
}