/**
 * @file CensusDataSorts.cpp   Sort functions for census population data.
 *         Includes insertion, merge and quick sort.
 *
 * @brief
 *    Implements several different types of sorts. Data can be sorted
 * by population or by name of town. This file contains all of the sorting
 * functions and their helpers.
 *
 * @author Priyanka Chordia
 * @date 2/28/15
 */

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>
#include <random>
#include "CensusData.h"

//std::default_random_engine generator;

/*
 void CensusData::insertionSort(int type)
 
 Desc:  Function to perform the insertion
        sort by its types.
 
 Parameter: type: states the type as sort by
            population or sort by name.
 
 Input:  key: holds the data which is currently
              being compared.
 
 Output: N/A
 
 */
void CensusData::insertionSort(int type) {
    for(int j = 1; j < getSize(); j++)
    {
        Record *key = data[j];
        int i = j-1;
        while(i>=0 && isSmaller(type,key,data[i]))
        {
            data[i+1] = data[i];
            i = i-1;
        }
        data[i+1] = key;
    }
}

/*
 void CensusData::mergeSort(int type)
 
 Desc:  Function to perform the merge
        sort by its types.
 
 Parameter: type: states the type as sort by
            population or sort by name.
 
 Input:  N/A
 
 Output: N/A
 
 */

void CensusData::mergeSort(int type) {
    mergeS(0, ((int)data.size()-1), type);
}

/*
 void CensusData::mergeS(int p, int r, int type)
 
 Desc: Recursive Function to perform a call to
       merge sort performed by its types.
 
 Parameters: p: Start index in vector
             r: end index in vector
             type: states the type as sort by
                   population or sort by name.
 
 Input:  q: to store the mid of the vector.
 
 Output: N/A
 
 */

void CensusData::mergeS(int p, int r, int type)
{
    if(p<r)
    {
        int q = floor(p+r)/2;
        mergeS(p, q, type);
        mergeS(q+1, r, type);
        merge(type, p, q, r);
    }
}

/*
 void CensusData::merge(int type, int p, int q, int r)
 
 Desc: A Function to merge the two sorted subsequences.
 
 Parameters: p: Start index in vector
             r: end index in vector
             q: mid element which divides array into subarrays.
             type: states the type as sort by
                    population or sort by name.
 
 Input: n1: to store the left subsequence of the vector.
        n2: to store the right subsequence of vector.
        L : Left subsequence of vector.
        R : Right subsequence of vector.
 
 Output: N/A
 
 */

void CensusData::merge(int type, int p, int q, int r)
{
    int n1 = q-p+1;
    int n2 = r-q;
    vector<Record*> L( (data.begin() + p ), (data.begin() + p +n1) );
    vector<Record*> R( (data.begin() + q + 1), (data.begin() + q + 1 + n2));
    
    int i=0;
    int j=0;
    int k = p;
    while(i < (int)L.size() && j < (int)R.size())
    {
        if(isSmaller(type, L[i], R[j]))
        {
            data[k++] = L[i++];
        }
        else
        {
            data[k++] = R[j++];
        }
    }
    while( i < (int)L.size() )
    {
        data[k++] = L[i++];
    }
    while( j < (int)R.size() )
    {
        data[k++] = R[j++];
    }
}

/*
 void CensusData::quickSort(int type)
 
 Desc: A Function to perform quicksort by its type.
 
 Parameters: type: states the type as sort by
             population or sort by name.
 
 Input: seed_called: to maintain the track whether or
        not the seed function is called.
 
 Output: N/A
 
 */

void CensusData::quickSort(int type) {
   /* static bool seed_called = false;
    if(seed_called == false)
    {
        generator.seed(0);
        seed_called = true;
    }*/
    quickS(0, ((int)data.size()-1), type);
}

/*
 void CensusData::quickS(int p, int r, int type)
 
 Desc: A Recursive Function to perform quicksort(randomized)
       using Randomized partition.
 
 Parameters: p: Start index in vector
             r: end index in vector
             type: states the type as sort by population or sort by name.
 
 Input: q: contains the pivot element obtained from the
        randomized_partition.
 
 Output: N/A
 
 */

void CensusData::quickS(int p, int r, int type)
{
    if(p<r)
    {
        int q= randomized_partition(type, p, r);
        quickS(p, q-1, type);
        quickS(q+1, r, type);
    }
}

/*
 int CensusData::partition(int type, int p, int r)
 
 Desc: A Function to partition the vector contents into
       elements of [p..q-1], [q+1..r] elements.
 
 Parameters: p: Start index in vector
             r: end index in vector
             type: states the type as sort by population or sort by name.
 
 Input: r: contains the pivot element with which the elements
           in the vector is compared.
 
 Output: returns the value at which the partition is to be
         obtained.
 
 */

int CensusData::partition(int type, int p, int r)
{
    Record *x = data[r];
    int i = p-1;
    for(int j = p; j < r ; j++)
    {
        if(isSmaller(type, data[j], x))
        {
            std::swap(data[++i], data[j]);
        }
    }
    std::swap(data[i+1], data[r]);
    return i+1;
 
}

/*
int CensusData::random(int p, int r)
 
 Desc: A Function to generate a random number to pass as
       the pivot element.
 
 Parameters: p: Start index in vector
             r: end index in vector
 
 Input: r: contains the pivot element with which the elements
            in the vector is compared.

 Output: returns the value at which the partition is to be
         obtained.
 
 */

int CensusData::random(int p, int r)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
     
     std::default_random_engine generator(seed);
     std::uniform_real_distribution<int> distribution(p, r);
     std::random_device rd;
     std::default_random_engine generator( rd() );
    /*
     Code used from the following site for generating the random
     number using std::default_random_engine
     
     http://stackoverflow.com/questions/15461140/stddefault-random
     -engine-generato-values-betwen-0-0-and-1-0
     
    
    std::uniform_int_distribution<int> distribution(p, r);
    int rand = distribution(generator);
    return rand;*/
}

/*
 int CensusData::randomized_partition(int type, int p, int r)
 
 Desc: A Function that receives the random value from random()
       function coded above to partition the vector.
 
 Parameters: p: Start index in vector
             r: end index in vector
             type: states the type as sort by population or sort by name.
 
 Input: i: stores the random value obtained from the random() function.
 
 Output: returns the value of the partition.
 */


int CensusData::randomized_partition(int type, int p, int r)
{
    int i = random(p, r);
    std::swap(data[r], data[i]);
    return partition(type, p, r);
}

/*
bool CensusData::isSmaller(int type, CensusData::
 Record* first, CensusData::Record* second)
 
 Desc: A Function to comapre the values to sort the vector
       for population and city name.
 
 Parameters: type: states the type as sort by population or sort by name.
             first: the first data to be compared.
             second:the second data to be compared.
 
 Input: N/A
 
 Output: N/A
 
 */


bool CensusData::isSmaller(int type, CensusData::Record* first,
                           CensusData::Record* second)
{
    if(type == POPULATION)
    {
        return first->population <= second->population;
    }
    else if(type == NAME)
    {
        string first_city = *first->city;
        string second_city = *second->city;
        return (first_city.compare(second_city) < 0 ? true : false);
    }
    return false;
}
