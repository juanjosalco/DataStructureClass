///Act 2.3 - long longegral activity linear data structure (Proficiency Evidence)
/// Author: Juan Jose Salazar Cortes
/// Author: Mariana Esquivel Hernandez
/// date: 10/11/2022

//#include <bits/stdc++.h>

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

string getIP(string record){
    long long contEsp = 0;
    long long indexBeg;
    long long indexEnd;
    bool aux = true;
    bool aux2 = true;
    for(long long i = 0; i < record.length(); i++){
        if(record[i] == ' ') contEsp ++;
        if(contEsp == 3 && aux) indexBeg = i + 1 , aux = false;
        if(contEsp == 4 && aux2) indexEnd = i - indexBeg , aux2 = false;
    }
    return record.substr(indexBeg, indexEnd); // "112.12.122.12.1111"
} // Time Complexity O(n)

//Modify the IP to have the same length
string configStr(string IP){ // 14
    long long consts = 0;
    long long constt = 0;
    long long constf = 0;
    long long dot = 0;

    
    for(long long i = IP.length()-6; i >= 0; i--){ 
        if (IP[i] == '.') dot++; 
        else if (dot == 0) consts++; 
        else if (dot == 1) constt++; 
        else if (dot == 2) constf++;
        if (consts < 2 && dot == 1){
            IP[i] = '0';
            consts++;
        }
        else if (constt < 3 && dot == 2){
            IP[i] = '0';
            constt++;
            if(constt < 3) IP.insert(i,"0");
        }
        else if (constf < 2 && dot == 3){
            IP[i] = '0';
            constf++;
        }
    }
    return IP;
} // Time Complexity O(n)

//Delete "." and ":" from the IP to sort it as an long longeger
long long getNumberIP(string IP){
    string newStr;
    for(long long i = 0; i < IP.length(); i++){
        if(IP[i] != ':' && IP[i] != '.'){
            newStr += IP[i];
        } else{
            continue;
        }
    }
    return stoll(newStr);
} // Time Complexity O(n)

// ----- Part of mergeSort Function --------
void merge(vector<string> &data, long long inicio, long long mid, long long final){
    long long numIzq = mid - inicio + 1;
    long long numDer = final - mid;

    vector<string> vecIzq;
    vector<string> vecDer;

    for(long long i = 0; i < numIzq; i++){
        vecIzq.push_back(data[inicio + i]);
    }
    for(long long i = 0; i < numDer; i++){
        vecDer.push_back(data[mid + 1 + i]);
    }

    long long i = 0;
    long long j = 0; 
    long long k = inicio;


    while(i < numIzq && j < numDer){
        
        if(getNumberIP(configStr(getIP(vecIzq[i]))) < getNumberIP(configStr(getIP(vecDer[j])))){
            data[k] = vecIzq[i];
            i++;
        }
        else{
            data[k] = vecDer[j];
            j++;
        }
        k++;
    }

    while(j < numDer){
        data[k] = vecDer[j];
        j++;
        k++;
    }
    while(i < numIzq){
        data[k] = vecIzq[i];
        i++;
        k++;
    }
} // Time Complexity O(n)

void mergeSort(vector<string> &data, long long inicio, long long final){
    if(inicio < final){
        long long mid = inicio + (final - inicio) / 2;
        mergeSort(data, inicio, mid);
        mergeSort(data, mid + 1, final);
        merge(data, inicio, mid, final);

    } // Final Time Complexity O(n log n)
}

// -------------- Sequential Search -----------------

long long sequentialSearch(vector<string> &info, string IP){
    for(long long i = 0; i < info.size(); i++){
        if(getNumberIP(configStr(getIP(info[i]))) >= getNumberIP(configStr(IP))){
            return i;
        }
    }
    return -1;
} // Time Complexity O(n)

long long inverseSequentialSearch(vector<string> &info, string IP){
    for(long long i = info.size()-1; i > 0; i--){
        if(getNumberIP(configStr(getIP(info[i]))) <= getNumberIP(configStr(IP))){
            return i+1;
        }
    }
    return -1;
} // Time Complexity O(n)

void showSelectedRange(vector<string> info, long long start, long long end){
    ofstream myfile;
    myfile.open ("newBitacora.txt"); 
    for(long long i = start; i < end; i++){
        myfile << info[i] << endl; 
    }
    myfile.close();
} // Time Complexity O(n)

int main(){
    fflush(stdin);
    vector<string> info;
    string record;
    string startIP, endIP;
    ifstream MyReadFile("bitacora.txt");
    while(getline(MyReadFile, record)){
        info.push_back(record);
    }
    MyReadFile.close();
    mergeSort(info, 0, info.size()-1);
     
    cout << "Ingresa la IP de Inicio de Búsqueda en el Siguiente Formato: " << endl;
    cout << "Example: xxx.xx.xxx.xx:xxxx ";
    getline(cin, startIP);
    cout << "Ingresa la IP de Final de Búsqueda en el Siguiente Formato: " << endl;
    cout << "Example: xxx.xx.xxx.xx:xxxx ";
    getline(cin, endIP);
    showSelectedRange(info, sequentialSearch(info, startIP), inverseSequentialSearch(info, endIP));
    cout << "Rango seleccionado enviado a la Base de Datos" << endl;
    return 0;
}