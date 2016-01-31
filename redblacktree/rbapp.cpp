//
//  @file rbapp.cpp To process the functionalities of Red Black tree
//                    assignment.
//
//  @brief Processing of the red black tree functionality.
//
//  @author Priyanka Chordia
//  @date   4/13/15.
//

#include <stdio.h>
#include <iostream>
#include <sstream>
#include "rbapp.h"

using namespace std;

/*
 int main()
 
 Desc:  The main function for execution of red black tree.
 Input:  N/A
 Output: N/A
 
 */

int main() {
  RBapp myRBTapp;
  myRBTapp.mainLoop();
  return 0;
}

/*
 void RBapp::mainLoop()
 
 Desc:  The mainloop to process the commands for red black tree.
 Input:  N/A
 Output: N/A
 
 */

void RBapp::mainLoop()  {
  while (!cin.eof() && !done)
    processCommand();
}

/*
 RBapp::RBapp() : done(false)
 
 Desc:  Default Constructor of RBapp class.
 Input:  N/A
 Output: N/A
 
 */

RBapp::RBapp() : done(false)
{

}

/*
 void RBapp::processCommand()
 
 Desc:  Processes the various commands to perform the
        functionality of red black tree.
 Input:  N/A
 Output: N/A
 
 */

void RBapp::processCommand()
{
  string command;
  string line;
  getline(cin,line);
  stringstream ss(line);
  getline(ss, command, ' ');
  if(command == "insert")
  {
    string value;
    getline(ss, value);
    processInsert(value);
  }
  else if(command == "print")
  {
    processPrint();
  }
  else if(command == "quit")
  {
    done = true;
  }
  else if(command == "find")
  {
    string key;
    ss >> key;
    processFind(key);
  }
  else if(command == "delete")
  {
    string value;
    getline(ss, value);
    processDelete(value);
  }
}

/*
 void RBapp :: processInsert(string &value)
 
 Desc:  Function that process the insert command to insert
        a new node in the tree.
 Input:  value: the value of the node to be inserted.
 Output: N/A
 
 */

void RBapp :: processInsert(string &value)
{
  stringstream ss(value);
  string key, data;
  getline(ss, key, ' ');
  getline(ss, data);
  myRBT.rbInsert(key, data);
}

/*
 void RBapp :: processPrint()

 Desc:  Function that process the print command to print
 the nodes in the tree.
 Input:  N/A
 Output: N/A
 
 */

void RBapp :: processPrint()
{
  myRBT.rbPrintTree();
}

/*
 void RBapp:: processFind(string &value)
 
 Desc:  Function that process the find command to search
 for a node in the tree.
 Input:  value: the value of the node to be searched.
 Output: N/A
 
 */

void RBapp:: processFind(string &value)
{
  vector<const string*> v = myRBT.rbFind(value);
  for(auto itr = v.begin(); itr!=v.end(); cout << **itr << endl, itr++)
  {
  }
}

/*
 void RBapp :: processDelete(string &value)
 
 Desc:  Function that process the delete command to delete
 a node from the tree.
 Input:  value: the value of the node to be deleted.
 Output: N/A
 
 */

void RBapp :: processDelete(string &value)
{
  stringstream ss(value);
  string key,data;
  getline(ss, key, ' ');
  getline(ss, data);
  myRBT.rbDelete(key, data);
}

