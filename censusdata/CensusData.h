/**
 * @file CensusData.h   Declaration of the CensusData class.
 * 
 * @brief
 *    Contains the declaration of class CensusData which contains the
 *    member variables and member function to perform the 3 sorting
 *    techniques viz. Insertion, Merge and Quick sort.
 *
 * @author Priyanka Chordia
 * @date 2/28/15
 */

#ifndef CSCI_311_CENSUSDATA_H
#define CSCI_311_CENSUSDATA_H

#include <vector>
using std::ifstream;
using std::string;
using std::vector;

class CensusData {
public:
   static const int POPULATION = 0;       // type of sort
   static const int NAME = 1;
   ~CensusData();
   void initialize(ifstream&);            // reads in data
   int getSize(){return data.size();}
   void print();                          // prints out data
   void insertionSort(int);               // sorts data using insertionSort
   void mergeSort(int);                   // sorts data using mergeSort
   void quickSort(int);                   // sorts data using quickSort
private:
   class Record {                         // declaration of a Record
   public:
      string* city;
      string* state;
      int population;
      Record(string&, string&, int);
      ~Record();
   };
   vector<Record*> data;                  // data storage
//
// You may add your private helper functions here!

    void merge(int, int, int, int); // to merge the sorted subarrays
    void mergeS(int, int, int); // to perform merge sort on vector
    void quickS(int, int, int); // to perform quick sort on vector
    int randomized_partition(int, int, int); // to perform random partition
    int random(int, int); // to generate a random pivot
    int partition(int, int, int); // to perform partition
   bool isSmaller(int, Record*, Record*); // to compare the data
};

#endif // CSCI_311_CENSUSDATA_H