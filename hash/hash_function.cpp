/* This assignment originated at UC Riverside.*/


/**
 * @file hash_function.cpp   Implementation of functions for hashing.
 *
 * @brief
 *    Implementation of hash function for hash table.
 *    Consist of an efficient hash function.
 *
 * @author Priyanka Chordia
 * @date   3/18/15
 */

#include <string>
#include "hash.h"

using std::string;

/*
   int Hash::hf(string key)

   Reference used: http://www.eternallyconfuzzled.com/tuts/algorithms/
   jsw_tut_hashing.aspx
   Function Description: XOR hash function used. The XOR hash is an algorithm 
   which is commonly suggested in the textbooks. Instead
   of adding together the bytes of an object as the 
   additive hash does, the XOR hash repeatedly folds the
   bytes together to produce a seemingly random hash value.

Input: key- The size of the hash table.
Output: Returns the location of the key to be inserted.
 */

int Hash::hf(string key)
{
   int hashVal = 0;
   for (unsigned int x = 0; x < key.length(); ++x)
   {
      hashVal ^= (hashVal << 5) + (hashVal >> 2) + key[x];
   }
   return hashVal % HASH_TABLE_SIZE;
}
