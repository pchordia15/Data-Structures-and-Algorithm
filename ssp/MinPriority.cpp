//
//  @file MinPriority.cpp Implementation of a MinPriority
//                    queue assignment.
//
//  @brief Implementation of a MinPriority queue for Single
//         shortest path algorithm.
//
//  @author Priyanka Chordia
//  @date   4/19/15.
//

#include "MinPriority.h"
#include <math.h>
#include <string.h>

using namespace std;

/*
   MinPriorityQ::MinPriorityQ(int sizeP) : size(0)

Desc:  Parameterized constructor of class
MinPriorityQ
Input:  sizeP : To initialize the size of minHeap
Output: N/A

 */

MinPriorityQ::MinPriorityQ(int sizeP) : size(0)
{
   minHeap = new Element[sizeP];
}

/*
   MinPriorityQ::~MinPriorityQ()

Desc:  Destructor of class MinPriorityQ
Input:  N/A
Output: N/A

 */

MinPriorityQ::~MinPriorityQ()
{
   delete []minHeap;
}

/*
   int MinPriorityQ::parent(int i)

Desc:  To identify and obtain a parent of an
element in MinPriorityQ
Input:  i : The node of which parent is to be 
obtained
Output: N/A

 */

int MinPriorityQ::parent(int i)
{
   return floor(i/2);
}

/*
   int MinPriorityQ::right(int i)

Desc:  To identify and obtain a right child of an
element in MinPriorityQ
Input:  i : The node of which right child is to be
obtained
Output: N/A

 */

int MinPriorityQ::right(int i)
{
   return (2*i)+1;
}

/*
   int MinPriorityQ::left(int i)

Desc:  To identify and obtain a left child of an
element in MinPriorityQ
Input:  i : The node of which left child is to be
obtained
Output: N/A

 */

int MinPriorityQ::left(int i)
{
   return (2*i);
}

/*
   void MinPriorityQ::insert(string id, int Key)

Desc:  To insert an element in MinPriorityQ
Input:  id : The node value to be inserted.
key: the priority of the node.
Output: N/A

 */

void MinPriorityQ::insert(string id, int Key)
{
   minHeap[size].id = id;
   minHeap[size].key = Key;
   size = size + 1;
   buildMinHeap();
}

/*
   void MinPriorityQ::minHeapify(int i)

Desc:  To obtain a min heap from the inserted
heap in MinPriorityQ
Input:  i : The node on which minheapify is
performed
Output: N/A

 */

void MinPriorityQ::minHeapify(int i)
{
   int l = left(i);
   int r = right(i);
   int smallest = 0;

   if((l <= size) && minHeap[l-1].key
         < minHeap[i-1].key)
   {
      smallest = l;
   }
   else
   {
      smallest = i;
   }

   if((r <= size) && minHeap[r-1].key <
         minHeap[smallest-1].key)
   {
      smallest = r;
   }

   if(smallest != i)
   {
      swap(minHeap[i-1],minHeap[smallest-1]);
      minHeapify(smallest);
   }
}

/*
   void MinPriorityQ::buildMinHeap()

Desc:  To build a min heap from the inserted
heap in MinPriorityQ
Input:  N/A
Output: N/A

 */

void MinPriorityQ::buildMinHeap()
{
   for(int i = floor(size/2); i > 0; i--)
   {
      minHeapify(i);
   }
}

/*
   void MinPriorityQ::decreaseKey(string id, int newKey)

Desc:  To decrease the priority of a min heap in
MinPriorityQ
Input:  id : The new node value to be compared.
key: the priority of the node.
Output: N/A

 */

void MinPriorityQ::decreaseKey(string id, int newKey)
{
   for(int i = 0; i < size; i++)
   {
      if(minHeap[i].id.compare(id) == 0)
      {
         if(newKey < minHeap[i].key)
         {
            minHeap[i].key = newKey;
            buildMinHeap();
         }
      }
   }
}

/*
   string MinPriorityQ::extractMin()

Desc:  To obtain a minimum elemet from the heap
in MinPriorityQ
Input:  N/A
Output: N/A

 */

string MinPriorityQ::extractMin()
{
   string min = " ";
   if(size > 0)
   {
      min = minHeap[0].id;
      swap(minHeap[0], minHeap[size-1]);
      size = size-1;
      minHeapify(1);
   }
   else
      cout<<"empty";
   return min;
}

/*
   bool MinPriorityQ::isMember(string id)

Desc: Returns true if the element is found in MinPriorityQ
Input:  id : The value of the element to be searched
Output: N/A

 */

bool MinPriorityQ::isMember(string id)
{
   for(int i = 0; i < size; i++)
   {
      if(minHeap[i].id == id)
         return true;
   }
   return false;
}
