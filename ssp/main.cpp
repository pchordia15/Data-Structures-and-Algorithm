//
//  @file main.cpp Test Driver for MinPriorityQ.
//
//  @brief Contains test driver for MinPriorityQ.
//
//  @author Priyanka Chordia
//  @date   4/19/15.
//

#include <iostream>
#include <sstream>
#include <stdlib.h>
#include "MinPriority.h"

using namespace std;

int main() {
    string id;
    string data;
    int key;
    MinPriorityQ MPQ(100);
    while (!cin.eof())
    {
    string command;
    string line;
    getline(cin,line);
    stringstream ss(line);
    getline(ss, command, ' ');
    if(command == "a")
    {
        string value;
        getline(ss, value);
        stringstream ss(value);
        getline(ss, id, ' ');
        getline(ss, data);
        key = atoi(data.c_str());
        MPQ.insert(id,key);
    }
    else if(command == "d")
    {
        string value;
        getline(ss, value);
        stringstream ss(value);
        getline(ss, id, ' ');
        getline(ss, data);
        key = atoi(data.c_str());
        MPQ.decreaseKey(id,key);
    }
    else if(command == "x")
    {
        cout << MPQ.extractMin() << endl;
    }
    else if(command == "q")
    {
        exit(0);
    }
    }
    /*
    MinPriorityQ q(10);
    q.insert("sam",3);
    q.insert("fred",2);
    q.insert("polly",18);
    q.insert("jen",24);
    q.decreaseKey("polly",1);
    cout << q.extractMin() << endl;
    cout << q.extractMin() << endl;
    q.decreaseKey("jen",5);
    cout << q.extractMin() << endl;
    cout << q.extractMin() << endl;
    cout << q.extractMin() << endl;
     */
    
    return 0;
}
