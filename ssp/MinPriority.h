//
//  @file MinPriority.h Header file for Implementation of
//                      a MinPriority queue
//
//  @brief contains all the function declarations for
//         implementing MinPriorityQ.
//
//  @author Priyanka Chordia
//  @date   4/19/15.
//

#ifndef __ssp__MinPriority__
#define __ssp__MinPriority__

#include <stdio.h>
#include <iostream>

using namespace std;

class MinPriorityQ
{

   public:

      MinPriorityQ(int size);   
      ~MinPriorityQ();
      void insert(string id, int Key);
      void decreaseKey(string id, int newKey);
      string extractMin();
      bool isMember(string id);

   private:
      void buildMinHeap();
      void minHeapify(int i);
      int parent(int i);
      int left(int i);
      int right(int i);
      int size;

      class Element
      {
         public:

            string id;
            int key;
      };
      Element *minHeap;
};


#endif /* defined(__ssp__MinPriority__) */
