/* This assignment originated at UC Riverside. The hash table size
   should be defined at compile time. Use -D HASH_TABLE_SIZE=X */


/**
 * @file hash.h   Header file for Implementation of hash function.
 *
 * @brief
 *    Definition of the functions for implementing hash function.
 *
 * @author Priyanka Chordia
 * @date   3/18/15
 */

#ifndef __HASH_H
#define __HASH_H

#include <string>
#include <list>

using std::string;
using std::list;

class Hash {

   public:
      Hash();                          // constructor
      void remove(string);             // remove key from hash table
      void print();                    // print the entire hash table
      void processFile(string);        // open file and add keys to hash table
      bool search(string);             // search for a key in the hash table
      void output(string);             // print entire hash table to a file
      void printStats();               // print statistics

   private:
      // HASH_TABLE_SIZE should be defined using the -D option for g++
      list<string> hashTable [HASH_TABLE_SIZE];
      int collisions;                  // total number of collisions
      unsigned int longestList;        // longest list ever generated
      double avgLength;                // running average of average list length

      int hf(string);                  // the hash function

      // put additional functions below as needed
      // do not change anything above!

      void average();                // to obtain the average of hash table
      double loadFactor;
};

#endif
