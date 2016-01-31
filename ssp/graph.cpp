//
//  @file graph.cpp Implementation of graph to
//                  obtain SSP tree.
//
//  @brief Implementation of a graph for Single
//         shortest path algorithm.
//
//  @author Priyanka Chordia
//  @date   5/1/15.


#include "graph.h"
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

/*
 Graph :: Vertex :: Vertex(string nameP, int keyP) :
 pi(nameP), key(keyP)
 
 Desc:  Parameterized constructor for Vertex class

 Input:  N/A
 Output: N/A
 
 */

Graph :: Vertex :: Vertex(string nameP, int keyP) :
  pi(nameP), key(keyP)
{
}

/*
 Graph :: Neighbor :: Neighbor(string nameP, int weightP) :
 name(nameP), weight(weightP)
 
 Desc:  Parameterized constructor for Neighbor class
 
 Input:  N/A
 Output: N/A
 
 */

Graph :: Neighbor :: Neighbor(string nameP, int weightP) :
  name(nameP), weight(weightP)
{
}

/*
 Graph :: Graph() : currentSource(""), minQ(NULL),
 addVertexToMinQ(false), sortAdjList(false)
 
 Desc:  Parameterized constructor for Graph class
 
 Input:  N/A
 Output: N/A
 
 */

Graph :: Graph() : currentSource(""), minQ(NULL),
addVertexToMinQ(false), sortAdjList(false)
{
}

/*
 Graph :: ~Graph()
 
 Desc:  Destructor for Graph class
 
 Input:  N/A
 Output: N/A
 
 */

Graph :: ~Graph()
{
  for(auto it = vertices.begin(); it != vertices.end(); it++)
  {
    Vertex *v = it->second;
    delete v;
  }
  for(auto it = adjList.begin(); it != adjList.end(); it++)
  {
    vector<Neighbor *> vect = it->second;
    for(auto itr = vect.begin(); itr != vect.end(); itr++)
    {
      Neighbor *n = *itr;
      delete n;
    }
  }
  delete minQ;
}

/*
 void Graph::addVertex(string name)
 
 Desc:  To add vertex in the graph for single shortest
        path
 
 Input:  name : name of the vertex to be added
 Output: N/A
 
 */

void Graph::addVertex(string name)
{
  auto it = vertices.find(name);
  if(it == vertices.end())
  {
    Vertex *v = new Vertex("",100);
    vertices.insert(make_pair(name,v));
  }
}

/*
 void Graph::addEdge(string from, string to, int weight)
 
 Desc:  To add edge in the graph for single shortest
 path
 
 Input:  from : to add edge from the vertex
          to  : to add edge to the vertex
         weight: weight of the edge
 Output: N/A
 
 */

void Graph::addEdge(string from, string to, int weight)
{
  if(addVertexToMinQ == false)
  {
    addVertexToMinQ = true;
    minQ = new MinPriorityQ(vertices.size());
  }
  //check if both the vertices are present in the graph
  if(vertices.find(from) != vertices.end() && 
      vertices.find(to) != vertices.end() )
  {
    Neighbor *n = new Neighbor(to,weight);
    vector<Neighbor *> vect;

    auto it = adjList.find(from);
    if(it == adjList.end())
    {
      //add edge to adjList
      vect.push_back(n);
      adjList.insert(make_pair(from,vect));
    }
    else
    {
      //add edge to existing one
      vect = it->second;
      //TODO error checking for duplicate edge
      vect.push_back(n);
      adjList[from] = vect;
    }
  }
}

/*
 string Graph :: getShortestPath(string from, string to)
 
 Desc:  To obtain the shortest path between vertices
         in the graph
 
 Input:  from : to add edge from the vertex
          to  : to add edge to the vertex
 Output: N/A
 
 */

string Graph :: getShortestPath(string from, string to)
{
  if(sortAdjList == false)
  {
    sortAdjList = true;

    for(auto it = adjList.begin(); it != adjList.end(); it++)
    {
      vector<Neighbor *> temp = it->second;
      sort(temp.begin(), temp.end(),Predicate);
      adjList[it->first] = temp;
    }
  }

  string ret = "";
  if(currentSource != from)
  {
    currentSource = from;
    buildSSPTree(from);
  }

  stack<string> empty;
  swap(path,empty);
  path.push(to);

  getParent(to);

  unsigned int size = path.size();
  for(unsigned int i =0; i < size; i++)
  {
    string source = path.top();
    path.pop();
    ret += source;
    if(i != size-1)
      ret +="->";
  }
  ret += " with length ";
  stringstream ss;
  Vertex *v = vertices[to];
  ss << v->key;
  ret += ss.str();

  return ret;
}

/*
 void Graph :: getParent(string source)
 
 Desc:  To obtain the parent of the vertex
 Input:  source : the vertex whose parent need to be found
 Output: N/A
 
 */

void Graph :: getParent(string source)
{
  Vertex *v = vertices[source];
  if(v->pi == "")
    return;
  else
  {
    path.push(v->pi);
    getParent(v->pi);
  }
}

/*
 void Graph :: initSingleSource(string source)
 
 Desc:  To initialise the graph
 Input:  source : the vertex which is passed as the first
                   vertex
 Output: N/A
 
 */

void Graph :: initSingleSource(string source)
{
  for(auto it = vertices.begin(); it != vertices.end(); it++)
  {
    Vertex *v = it->second;
    v->pi = "";
    if(it->first == source)
    {
      v->key = 0;
    }
    else
    {
      v->key = 100;
    }
    minQ->insert(it->first,v->key);
    vertices[it->first] = v;
  }
}

/*
 void Graph :: buildSSPTree(string source)
 
 Desc:  To build the single source shortest path tree.
 Input:  source : the vertex which is passed as the first
                  vertex
 Output: N/A
 
 */

void Graph :: buildSSPTree(string source)
{
  initSingleSource(source);
  for(unsigned int i =0; i < vertices.size(); i++)
  {
    string u = minQ->extractMin();
    auto it = adjList.find(u);
    if(it != adjList.end())
    {
      vector<Neighbor *>vect = it->second;
      for(unsigned int i =0; i < vect.size(); i++)
      {
        relax(u,vect[i]->name,vect[i]->weight);
      }
    }
  }
}

/*
 void Graph :: relax(string u, string v, int w)
 
 Desc:  To obtain the minimum weight to a particular
         vertex
 Input:  u: the source vertex
         v: the destination vertex
         w: the weight of their edge
 Output: N/A
 
 */

void Graph :: relax(string u, string v, int w)
{
  int ud = 0;
  auto it = vertices.find(u);
  Vertex *temp = it->second;
  ud = temp->key;

  int vd = 0;
  it = vertices.find(v);
  temp = it->second;
  vd = temp->key;

  if(vd > (ud + w))
  {
    vd = ud + w;
    temp->key = vd;
    temp->pi = u;
    vertices[v] = temp;
    minQ->decreaseKey(v, vd);
  }
}

/*
 void Graph :: printGraph()
 
 Desc:  To print the detail of the graph
 Input:  N/A
 Output: N/A
 
 */

void Graph :: printGraph()
{
  for(auto it = adjList.begin(); it != adjList.end(); it++)
  {
    cout << it->first << " --> ";
    vector<Neighbor *> vect = it->second;
    for(unsigned int i=0; i < vect.size();i++)
    {
      cout << vect[i]->name << "|" << vect[i]->weight << " , ";
    }
    cout << endl;
  }
}
