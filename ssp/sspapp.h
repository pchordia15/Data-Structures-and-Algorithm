//
//  @file sspapp.h Processing the graph to
//                  obtain SSP tree.
//
//  @brief Processing the graph for Single
//         shortest path algorithm.
//
//  @author Priyanka Chordia
//  @date   5/1/15.

#ifndef __ssp__sspapp__
#define __ssp__sspapp__

#include <stdio.h>
#include "graph.h"

class SSPapp
{

   public:
      void readGraph();
      void processQueries();

   private:
      Graph myGraph;
};

#endif /* defined(__ssp__sspapp__) */
