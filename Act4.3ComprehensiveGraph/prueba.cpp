/// Act 4.3 - Comprehensive Graph Activity (Competence evidence)
/// Author: Juan Jose Salazar Cortes
/// Author: Mariana Esquivel Hernandez
/// date: 11/14/2022


// Abra el archivo de entrada llamado "bitacora.txt Download bitacora.txt Vista previa del documento" 
// lealo y almacene los datos en en una lista de adyacencia organizada por dirección de ip origen 
// (Formato del archivo bitacora.pdf Download Formato del archivo bitacora.pdfVista previa del documento). 
// Por ejemplo la lista 192.168.1.3 => {192: 168, 168:1, 1:3}

// Determine el degree y el outdegree de cada nodo

// ¿Qué nodos tienen el mayor degree y cuales el mayor outdegree?


//#include <bits/stdc++.h>

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
        // adjMatrix = new int*[V];
        // for(int i=0; i<V; i++)
        //     adjMatrix[i] = new int[V];
        // for(int i=0; i<V; i++)
        //     for(int j=0; j<V; j++)
        //         adjMatrix[i][j] = 0;
    }

    ~Graph()
    {
        delete[] adjList;
        delete[] visited;
    }


    void loadGraph(int a, int b);
    void DFS(int);
    void BFS(int);
    void resetVisited();
    // void printAdjMatrix();
};

void Graph::loadGraph(int a, int b){
    // adjMatrix[a][b] = 1;
    // adjMatrix[b][a] = 1;
    adjList[a].push_back(b);
} // Complexity O(1)

void Graph::resetVisited()
{
    for (int i = 0; i < this->numVertices; i++)
        this->visited[i] = false;
} // Complexity O(V)

// Deep For Search
void Graph::DFS(int vertex)
{
    this->visited[vertex] = true;
    list<int> adjVertex = this->adjList[vertex];

    cout << vertex << " ";

    for (auto i : adjVertex)
        if (!this->visited[i])
            DFS(i);
} // Complexity: O(V + E)

// Breadth First Search
void Graph::BFS(int startVertex)
{
    visited[startVertex] = true;

    list<int> queue;
    queue.push_back(startVertex);

    while (!queue.empty())
    {
        int currVertex = queue.front();

        cout << currVertex << " ";

        queue.pop_front();

        for (auto i : adjList[currVertex])
        {
            if (!visited[i])
            {
                visited[i] = true;
                queue.push_back(i);
            }
        }
    }
}// Complexity O(V + E) - Space Complexity O(V)


struct Node{
    string IP;
    int rep;
    Node(string value): IP(value), rep(1){};
};

class maxHeap{
    private:
        int size = 0;
        vector<Node> heapTree = {};    
        int parent(int index) {
            return (index - 1) >> 1;
            }; 
        int left(int index) {
            return (index << 1) + 1;
            };  
        int right(int index) {
            return (index << 1) + 2;
            };  
    public:
        bool isEmpty() const {
            return size == 0;
            };
        void insertion(string value); 
        void top(int index);
        void shiftUp(int index); 
        void shiftDown(int index);
};

//Check if IP already exists and add to the repetitions and shift Up to move the IP further up the heap
//If it's a new value on the heap, insert it at the end and sift up to move it further up the heap
//If the heap is empty, insert the first element

void maxHeap::insertion(string value){
    if(size == 0){
        heapTree.push_back(Node(value));
        size+=1;
        return;
    }
    for(int i = 0; i < size; i++){
        if(heapTree[i].IP == value){
            heapTree[i].rep++;
            shiftUp(i);
            return;
        }
    }
    heapTree.push_back(Node(value));
    size+=1;
    shiftUp(size-1);
    return;
}//Time complexity: O(n)

void maxHeap::top(int index){
    string maxIP = heapTree[0].IP;    
    int maxReps = heapTree[0].rep;
    cout << "IP-."<< index+1 << " "<< maxIP + " is being repeated: " << to_string(maxReps) << " times "<< endl;
    swap(heapTree[0], heapTree[size-1]);
    shiftDown(0);
    size -= 1;
}//Time complexity: O(log n)

void maxHeap::shiftUp(int index){
    if(index == 0) return; 
    int parentIndex = parent(index);
    if(heapTree[parentIndex].rep < heapTree[index].rep){
        swap(heapTree[parentIndex], heapTree[index]);
    } 
    else if( heapTree[parentIndex].rep == heapTree[index].rep && heapTree[parentIndex].IP != heapTree[index].IP){ 
        swap(heapTree[parentIndex], heapTree[index]);
    }
    shiftUp(parentIndex);
}//Time complexity: O(log n)

void maxHeap::shiftDown(int index){
    if(size <= index){
        return; 
    }
    int aux = index;
    if((left(index) < size) && (heapTree[index].rep < heapTree[left(index)].rep)){
        aux = left(index);
    }
    if((right(index) < size) && (heapTree[aux].rep < heapTree[right(index)].rep)){
        aux = right(index);      
    }
    if(aux != index){
        swap(heapTree[index], heapTree[aux]);
        shiftDown(aux);
    }   
    return;
}//Time Complexity O(log n)

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
    vector<string> info;
    vector<string> IP;
    string record;
    maxHeap* priorityQueue = new maxHeap();
    ifstream OurReadFile("bitacora.txt");
    vector<string> lines;
    string line;

    while(getline(OurReadFile,line)){
        priorityQueue->insertion(getIPAccess(getIP(line)));
    }//Time complexity: O(n log n)
    OurReadFile.close();
    cout << "----------------------------Number of accesses for IP address-----------------------------" << endl;
    for(int i = 0; i < 5; i++){
        priorityQueue->top(i);
    }//Complexity O(nlogn)

    return 0;
}