//
//  @file sspapp.cpp Processing of graph to
//                  obtain SSP tree.
//
//  @brief Processing the graph for Single
//         shortest path algorithm.
//
//  @author Priyanka Chordia
//  @date   5/1/15.

#include "sspapp.h"
#include <iostream>
#include <sstream>

using namespace std;

/*
   void SSPapp :: readGraph()

Desc:  To obtain the details of the graph on which the
single source shortest path tree is to be obtained.

Input:  N/A
Output: N/A

 */

void SSPapp :: readGraph()
{
   int no_of_vertices;
   string line;
   getline(cin,line);
   no_of_vertices = atoi(line.c_str());
   string vertices;
   getline(cin,vertices);
   istringstream ss(vertices);
   string vertex;
   for(int i =0; i < no_of_vertices-1; i++)
   {
      getline(ss,vertex,' ');
      myGraph.addVertex(vertex);
   }
   getline(ss,vertex);
   myGraph.addVertex(vertex);

   int no_of_edges;
   getline(cin,line);
   no_of_edges = atoi(line.c_str());
   string from,to, weight;
   for(int i =0; i < no_of_edges - 1; i++)
   {
      getline(cin,line);
      istringstream ss(line);
      getline(ss,from,' ');
      getline(ss,to,' ');
      getline(ss,weight);
      myGraph.addEdge(from, to, atoi(weight.c_str()));
   }
   getline(cin,line);
   ss.str(line);
   getline(ss,from,' ');
   getline(ss,to,' ');
   getline(ss,weight);
   myGraph.addEdge(from, to, atoi(weight.c_str()));
}

/*
   void SSPapp :: processQueries()

Desc:  To process the details of the graph passed
to the SSP tree.

Input:  N/A
Output: N/A

 */

void SSPapp :: processQueries()
{
   string line;
   string first, second;
   string result;
   while(getline(cin,line))
   {
      istringstream ss(line);
      getline(ss,first,' ');
      getline(ss,second);
      result = myGraph.getShortestPath(first,second);
      cout << result << endl;
   }
}

/*
   int main()

Desc:  the entry point of the program

Input:  N/A
Output: N/A

 */

int main()
{
   SSPapp myapp;
   myapp.readGraph();
   myapp.processQueries();
}
