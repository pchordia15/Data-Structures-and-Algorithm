//
//  graph.h
//
//  @file graph.h Initialization of graph to obtain
//                  SSP tree.
//
//  @brief Initialization details of a graph for Single
//         shortest path algorithm.
//
//  @author Priyanka Chordia
//  @date   5/1/15.

#ifndef __ssp__graph__
#define __ssp__graph__

#include <stdio.h>
#include <map>
#include <vector>
#include <stack>
#include "MinPriority.h"

using namespace std;

class Graph
{

  public:
    Graph();
    ~Graph();
    void addVertex(string name);
    void addEdge(string from, string to, int weight);
    string getShortestPath(string from, string to);
    void buildSSPTree(string source);
    void relax(string u, string v, int weight);
    void printGraph();

  private:
    class Vertex
    {
      public: 
        string pi;
        int key;
        Vertex(string nameP, int keyP);
    };

    class Neighbor
    {
      public: 
        string name;
        int weight;
        Neighbor(string nameP, int weightP);
        /*
        bool operator<(const Neighbor &*first) const
        {
          return (this->name < first->name);
        }
        */
    };

    class compare
    {
      public:
        bool operator()(Neighbor *first , Neighbor *second)
        {
          return (first->name < second->name);
        }
    }Predicate;

    string currentSource;
    map<string, Vertex* > vertices;
    map<string, vector<Neighbor* >> adjList;
    stack<string> path;
    MinPriorityQ *minQ;
    bool addVertexToMinQ;
    bool sortAdjList;
    void initSingleSource(string start);
    void getParent(string source);
};

#endif /* defined(__ssp__graph__) */
