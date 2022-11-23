/// Act 3.4 - Comprehensive BST activity (competence evidence)
/// Author: Juan Jose Salazar Cortes
/// Author: Mariana Esquivel Hernandez
/// date: 11/02/2022

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


using namespace std;

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
    for(int i = 0; i < 10; i++){
        priorityQueue->top(i);
    }//Complexity O(nlogn)

    return 0;
}