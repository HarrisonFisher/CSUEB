#include <string>
#include <iostream>
#include "SetType.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *  Function:
 *      Default Constructor
 *
 * Precondition:
 *      none
 *
 * Post-condition:
 *      numBuckets is set to default number of buckets
 *
 */


// The default constructor should use the default number of buckets and set the number of elements to 0.
// This should also set the maxLoad to the default load factor.

template<class T>
SetType<T>::SetType() {
    // Create an array of forward_lists and initially set to an empty forward_list
    buckets = new forward_list<T>[DEFAULT_BUCKETS];

    // Your code here

    this->numBuckets = DEFAULT_BUCKETS;
    this->numElems = 0;
    this->maxLoad = DEFAULT_LOAD_FACTOR;
    ResetIterator();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class T>
SetType<T>::SetType(SetType &otherSet) {
    // This function is complete. No modification required.
    // This assumes the operator= is implemented.
    *this = otherSet;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class T>
SetType<T>::~SetType() {
    delete [] buckets;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Function:
 *      + operator for single elements
 *
 * Precondition:
 *      Element class should match
 *
 * Post-condition:
 *      Original is not changed.
 *      The return result will be a set that contains that element
 *
 */

// This is an alternative way to add an element to a set.
// However, this overload does not change the original calling set.

template<class T>
SetType<T> SetType<T>::operator+(T elem) {
    SetType<T> result;

    // Your code here

    result = (*this);
    result.Add(elem);

    return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Function:
 *      - operator for single elements
 *
 * Precondition:
 *      Element class should match
 *
 * Post-condition:
 *      The return result will be a set that does not contain the element
 *
 */

// This is an alternative way to remove an element to a set.
// However, this overload does not change the original calling set.

template<class T>
SetType<T> SetType<T>::operator-(T elem) {
    SetType<T> result;

    // Your code here

    result = (*this);
    result.Remove(elem);

    return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * Function:
 *      + operator for a set
 *
 * Precondition:
 *      The class of both sets match
 *
 * Post-condition:
 *      The return result will be a set with all elements of both sets
 *
 */


// This function returns the union of this and otherSet.
// This overload does not change the original instance or otherSet.

template<class T>
SetType<T> SetType<T>::operator+(SetType & otherSet) {
    SetType<T> result;

    // Your code here

    result = (*this);
    for (int i = 0; i < otherSet.numBuckets; i++){
        for (auto it = otherSet.buckets[i].begin(); it != otherSet.buckets[i].end(); ++it ){
            result.Add(*it);
        }
    }

    return result;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Function:
 *      * operator for a set
 *
 * Precondition:
 *      The class of both sets should match
 *
 * Post-condition:
 *      The return result will be a set with elements that are in both sets
 *
 */


// This function returns the intersection of this and otherSet.
// This overload does not change the original instance or otherSet.

template<class T>
SetType<T> SetType<T>::operator*(SetType & otherSet) {
    SetType<T> result;

    // Your code here

    for (int i = 0; i < numBuckets; i++){
        for (auto it = buckets[i].begin(); it != buckets[i].end(); ++it ){
            if (otherSet.Contains(*it)) { result.Add(*it); }
        }
    }

    return result;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Function:
 *      - operator for a set
 *
 * Precondition:
 *      The class of both sets must match
 *
 * Post-condition:
 *      The return result will be a set that does not contain any elements that are contained in the input set
 *
 */

// This function returns the difference of this and otherSet.
// This overload does not change the original instance or otherSet.

template<class T>
SetType<T> SetType<T>::operator-(SetType& otherSet) {
    SetType<T> result;

    // Your code here

    result = (*this);
    for (int i = 0; i < otherSet.numBuckets; i++){
        for (auto it = otherSet.buckets[i].begin(); it != otherSet.buckets[i].end(); ++it ){
            result.Remove(*it);
        }
    }

    return result;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Function:
 *      Get the next iterator item
 *
 * Precondition:
 *      The iterCount should be greater than the number of elements
 *
 * Post-condition:
 *      Return the element that the iterator currently point to.
 *      The iterator is incremented.
 *
 */

// This function should return the element that the bucketIter currently points to and then increment the bucketIter.
// If there are no more elements in the bucketIter (it is at the end),
// then the currBucket should be incremented and bucketIter should be set to the beginning of the next bucket.
// If GetNextItem() is called and there are no more elements to iterate over,
// then it should throw a IteratorOutOfBounds error.

template<class T>
T SetType<T>::GetNextItem() {
    // Returns the current item and then move to the next item
    T item;

    // Your code here

    iterCount++;
    if (iterCount > numElems) { throw IteratorOutOfBounds(); }

    if (bucketIter == buckets[currBucket].end()) {
        while(bucketIter == buckets[currBucket].end()) {
            currBucket++;
            bucketIter = buckets[currBucket].begin();
        }
    }

    item = *bucketIter;
    bucketIter++;

    return item;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class T>
int SetType<T>::GetHashIndex(const T& key) {
    // This is done... No touching!
    unordered_map<T,T> mapper;
    typename unordered_map<T,T>::hasher hashFunction = mapper.hash_function();
    return static_cast<int>(hashFunction(key) % numBuckets);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class T>
void SetType<T>::SetMaxLoad(double max) {
    // This function is done
    if (maxLoad < 0.1)
        maxLoad = 0.1;

    maxLoad = max;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Function:
 *      = Operator
 *
 * Precondition:
 *      none
 *
 * Post-condition:
 *      A deep copy is made
 *
 */

// This function does a deep copy into this.
// The function should copy the contents of each bucket from otherSet into the buckets of this.
// The function should also copy over the appropriate private variables from otherSet to this.

// HINT:
// Be sure that the number of buckets match.
// You will need to delete buckets and reallocate the correct number of buckets similar how you allocated the buckets for the constructor.
// Be also sure to make this empty before copying the elements from otherSet.

template<class T>
SetType<T>& SetType<T>::operator=(SetType const &other) {

    // Your code here

    MakeEmpty();

    if (numBuckets != other.numBuckets) {
        numBuckets = other.numBuckets;
        delete [] buckets;
        buckets = new forward_list<T>[other.numBuckets];
    }

    for (int i = 0; i < other.numBuckets; i++){
        for (auto it = other.buckets[i].begin(); it != other.buckets[i].end(); ++it ){
//            this->Add(*it);
            int bucket = GetHashIndex(*it);
            buckets[bucket].push_front(*it);
            numElems++;
        }
    }
    ResetIterator();

    return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Function:
 *      Rehash
 *
 * Precondition:
 *      number of buckets greater than 0
 *
 * Post-condition:
 *      The new number of buckets have been set.
 *      The elements were re-hashed to the appropriate buckets.
 */

// This function rehashes the elements stored in the set using the newNumBuckets.
// A simple strategy is to start with an empty set with the appropriate number of buckets (let's call this rehashSet).
// After that, you can use the iterator to add all the elements from this to the rehashSet.
// Once all the elements are copied into the rehashSet,
// you can use the assignment operator with *this and rehashSet.

template<class T>
void SetType<T>::Rehash(int newNumBuckets) {
    SetType<T> rehashedSet(newNumBuckets);

    // Your code here

    for (int i = 0; i < numBuckets; i++){
        for (auto it = buckets[i].begin(); it != buckets[i].end(); ++it ){
            int bucket = rehashedSet.GetHashIndex(*it);
            rehashedSet.buckets[bucket].push_front(*it);
            rehashedSet.numElems++;
        }
    }

    *this = rehashedSet;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Function:
 *      Constructor (int)
 *
 * Precondition:
 *      numBuckets > 0
 *
 * Post-condition:
 *      A new set was made with "numBucks" amount of buckets.
 *
 */

// This constructor should use the numBucks to create the buckets and set the number of elements to 0.
// This should also set the maxLoad to the default load factor.

template<class T>
SetType<T>::SetType(int numBucks) {

    buckets = new forward_list<T>[numBuckets];
    this->numBuckets = numBucks;
    this->numElems = 0;
    this->maxLoad = DEFAULT_LOAD_FACTOR;
    ResetIterator();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Function:
 *      Add element to set
 *
 * Precondition:
 *      Element class matches the set class
 *
 * Post-condition:
 *      Set contains the element
 *
 */

// This function should add elem to the set.
// If elem already exists in the list, then the set should not change.
// This function should use the GetHashIndex to figure out what bucket elem should be placed and the elem should be pushed to the front of the forward_list.

template<class T>
void SetType<T>::Add(T elem) {

    if (Contains(elem)) { return; }
    int bucket = GetHashIndex(elem);
    buckets[bucket].push_front(elem);
    numElems++;

    if (LoadFactor() > maxLoad) {
        Rehash(numBuckets * 2);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Function:
 *      Remove Element
 *
 * Precondition:
 *      Element class matches the set class.
 *
 * Post-condition:
 *      The set does not contain the element.
 *
 */

// This function should remove elem to the set. If elem does not exist in the list, then the set should not change.
// This function should use the GetHashIndex to figure out what bucket elem exists in and remove elem from the forward list.

template<class T>
void SetType<T>::Remove(T elem) {


    if (!Contains(elem)) { return; }
    int bucket = GetHashIndex(elem);
    buckets[bucket].remove(elem);
    numElems--;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Function:
 *      Set Contains Element
 *
 * Precondition:
 *      Element class matches the set class
 *
 * Post-condition:
 *      returns bool if the set Contains that element
 *
 */

// This function should return true if elem is in the set.
// You should find the bucket that elem is in and the search for that item within the bucket.


template<class T>
bool SetType<T>::Contains(T elem) {

    int bucket = GetHashIndex(elem);

    for (auto it = buckets[bucket].begin(); it != buckets[bucket].end(); ++it )
        if (*it == elem) { return true;}

    return false;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Function:
 *      Make Set Empty
 *
 * Precondition:
 *      none
 *
 * Post-condition:
 *      The set has no elements.
 *
 */
template<class T>
void SetType<T>::MakeEmpty() {
    for (int i = 0; i < numBuckets; i++){
        buckets[i].clear();
    }
    numElems = 0;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Function:
 *      Load factor of set
 *
 * Precondition:
 *      Number of buckets & elements > 0
 *
 * Post-condition:
 *      returns the load factor
 *
 */

// This function returns the load factor of the set.
// This is total number of elements in the set divided by the total number of buckets.

template<class T>
double SetType<T>::LoadFactor() const {
    //return numElems/numBuckets;
    return static_cast<double>(numElems)/numBuckets;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Function:
 *      ResetIterator
 *
 * Precondition:
 *      none
 *
 * Post-condition:
 *      bucketIter set to the beginning, and currBucket and iterCount set to 0.
 *
 */

// This function resets the iterator for the set. It behaves similarly to the other data structures covered previously.
// This function should set bucketIter to the beginning of the first bucket.
// It should also set currBucket and iterCount appropriately.

template<class T>
void SetType<T>::ResetIterator() {
    currBucket = 0;
    iterCount = 0;
    bucketIter = buckets[0].begin();
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
