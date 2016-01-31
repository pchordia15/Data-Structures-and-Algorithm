
/**
 * @file hash.cpp   Implementation of functions for hashing.
 *
 * @brief
 *    Implementation of hash table by chaining method.
 *    Consists all functions required to perform hashing.
 *
 * @author Priyanka Chordia
 * @date   3/18/15
 */

#include <stdio.h>
#include "hash.h"
#include <iostream>
#include <fstream>
#include <string>
#include <list>

using namespace std;

/*
   Hash::Hash()

Desc:  Default constructor of class Hash initialised
using initialization list which takes 3
arguments collisions, longestList and avgLength.
Input:  N/A
Output: N/A

 */

Hash::Hash() : collisions(0), longestList(0), avgLength(0.0)
{

}

/*
   void Hash::print()

Desc:  Prints the output of the hash table on the screen.
Input:  N/A
Output: N/A

 */

void Hash::print()
{
   int i=0;
   for(i = 0; i < HASH_TABLE_SIZE; i++)
   {
      cout << i << ":" << "\t";
      if(!hashTable[i].empty())
      {
         list<string>::iterator iter;
         for(iter = hashTable[i].begin(); iter != hashTable[i].end();
               iter++)
         {
            cout << *iter << ", ";
         }
         cout << endl;
      }
      else
      {
         cout << endl;
      }
   }
}

/*
   void Hash::processFile(string file)

Desc:  Reads from the file passes as parameter and performs
hashing by checking for the number of collisions and 
performing file operations.
Input: file: consists of the file name on which the hashing 
is to be performed.
Output: N/A

 */

void Hash::processFile(string file)
{
   string line;
   int index = 0;
   ifstream fileName;
   fileName.open(file);
   if(fileName.is_open())
   {
      while (getline(fileName, line))
      {
         index = hf(line);
         hashTable[index].push_back(line);

         unsigned int length = hashTable[index].size();

         if (length > 1)
         {
            collisions++;
         }

         if(longestList < length)
         {
            longestList = length;
         }

         average();
      }		
   }
   fileName.close();
}

/*
   void Hash::average()

Desc:  Calculates the average length of the list that is
being processed
Input: file: consists of the file name on which the hashing
is to be performed.
Output: N/A

 */


void Hash::average()
{
   double sum = 0;
   double avgListLen;
   int items = 0;

   std::list<string>::iterator itr;
   for(int i = 0; i < HASH_TABLE_SIZE; i++)
   {    
      sum = sum + hashTable[i].size();
      if(hashTable[i].size() > 0 )
         items++;
   }

   avgListLen  = sum/items;
   loadFactor = sum;
   avgLength = (avgListLen + avgLength)/2.0;
}

/*
   void Hash::remove(string key)

Desc:  Deletes the key from the hash table
Input: key: consists of the key which is to be
deleted from the hash table
Output: N/A

 */

void Hash::remove(string key)
{
   int index = hf(key);
   bool word = search(key);
   if(word)
   {
      hashTable[index].remove(key);
      average();
   }
}

/*
   bool Hash::search(string key)

Desc:  Searches for the key in the hash table
Input: key: consists of the key which is to be
searched in the hash table
Output: true - if key is found
false - if key is not found.

 */

bool Hash::search(string key)
{
   int i = hf(key);
   list<string>::iterator iter;
   if(!hashTable[i].empty())
   {
      for(iter = hashTable[i].begin(); iter != hashTable[i].end();
            iter++)
      {
         if(*iter == key)
         {
            return true;
         }
      }
   }
   return false;
}

/*
   void Hash::output(string file)

Desc:  Searches for the key in the hash table
Input: file: consists of the file name on which the
output operation is to be performed.
Output: N/A

 */

void Hash::output(string file)
{
   ofstream fileName;
   fileName.open(file);
   if (fileName.is_open())
   {
      for(int i = 0; i < HASH_TABLE_SIZE; i++)
      {
         fileName << i << ":\t";
         list<string>::iterator iter;
         for(iter = hashTable[i].begin(); iter != hashTable[i].end();
               iter++)
         {
            fileName << *iter << ", ";
         }
         fileName << "\n";
      }
      fileName.close();
   }
}

/*
   void Hash:: printStats()

Desc:  Prints the output of the functions performed for hash table
Input: file: consists of the file name on which the
output operation is to be performed.
Output: N/A

 */

void Hash:: printStats()
{
   loadFactor = loadFactor / HASH_TABLE_SIZE;
   cout << "Total Collisions = " << collisions << endl;
   cout << "Longest List Ever = " << longestList << endl;
   cout << "Average List Length Over Time = " << avgLength << endl;
   cout << "Load Factor = " <<loadFactor << endl;
}
