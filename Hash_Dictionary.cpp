
/*---------------------------------------------------------------------------------------------------------*
 *                                                                                                         *
 *   File: Dictionary.cpp                                                                                  *
 *                                                                                                         *
 *   Description:                                                                                          *
 *      Implementation file for the Dictionary class. Stores data in a hash table                          *
 *                                                                                                         *
 *   Authors: Mary Elaine Califf and Alex Lerch                                                            *
 *                                                                                                         *
 *   Member Functions:                                                                                     *
 *      Dictionary                    default contructor                                                   *
 *      operator=                     assignment operator overload                                         *
 *      addEntry                      add an entry                                                         *
 *      findEntry                     determine if entry is in the dictionary                              *
 *      printDictionaryInOrder        print entries in order                                               *
 *      printDictionaryKeys           print the structure of the dictionary                                *
 *      clear                         helper method for assignment operator and destructor                 *
 *      copy                          helper method for copy constructor and assignment operator           *
 *      rehash                        grows hash table and reassigns entries                               *
 *      hash                          hash routine for strings                                             *
 *      calculateOffset               calculates an offset for an entry that has a collision               *
 *      addEntry(3arg)                helper method for addEntry                                           *
 *                                                                                                         *
 *---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*
 *   Header Files                                                                                          *
 *---------------------------------------------------------------------------------------------------------*/
#include "Dictionary.h"
#include <iostream> 
#include <vector> 
#include <algorithm>



/*---------------------------------------------------------------------------------------------------------*
 *   Namespaces                                                                                            *
 *---------------------------------------------------------------------------------------------------------*/
using namespace std;


/*---------------------------------------------------------------------------------------------------------*
 *   Constants                                                                                             *
 *---------------------------------------------------------------------------------------------------------*/
// prime numbers used for expanding the size of the hash table
const int tableSizes[14] = {101, 211, 431, 863, 1733, 3469, 6947, 13901, 27803, 55609, 111227, 222461,
                                444929, 889871};

// prime numbers used with the second hash function
const int doubleHashNums[14] = {97, 199, 421, 859, 1723, 3467, 6917, 13883, 27799, 55603, 111217, 222437,
                                    444901, 889829};


/*---------------------------------------------------------------------------------------------------------*
 *   Member functions and operator function definitions                                                    *
 *---------------------------------------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------------------------------------*
 *                                                                                                         *
 *   Function Name: Dictionary                                                                             *
 *                                                                                                         *
 *   Description:                                                                                          *
 *      default constructor                                                                                *
 *                                                                                                         *
 *   Returns: n/a                                                                                          *
 *                                                                                                         *
 *---------------------------------------------------------------------------------------------------------*/
Dictionary::Dictionary() {
    // initialize the array of string pointers
    theArray = new StringPtr[tableSizes[0]] {nullptr};

    // set the initial size to 0
    arraySize = 0;

    // set the initial capacity
    arrayCapacity = tableSizes[0];

    // initiate tableSizeIndex
    tableSizesIndex = 0;
}



/*---------------------------------------------------------------------------------------------------------*
 *                                                                                                         *
 *   Function Name: operator=                                                                              *
 *                                                                                                         *
 *   Description:                                                                                          *
 *      assignment operator overload to help with dynamic memory management                                *
 *                                                                                                         *
 *   Returns: reference to the dictionary that was copied into                                             *
 *                                                                                                         *
 *---------------------------------------------------------------------------------------------------------*/
Dictionary& Dictionary::operator=(const Dictionary& rhs)
{
    // if the objects are not the same
    if (this != &rhs) {
        // delete the data first
        clear();
        
        // copy the data from rhs to this object
        copy(rhs);
    }
    // return this object
    return *this;
}



/*---------------------------------------------------------------------------------------------------------*
 *                                                                                                         *
 *   Function Name: addEntry                                                                               *
 *                                                                                                         *
 *   Description:                                                                                          *
 *      add an entry                                                                                       *
 *                                                                                                         *
 *   Returns: n/a                                                                                          *
 *                                                                                                         *
 *   Precondition: the dictionary must not have the identical string already stored in the dictionary      *
 *                                                                                                         *
 *   Postcondition: the string has been added to the dictionary                                            *
 *                                                                                                         *
 *---------------------------------------------------------------------------------------------------------*/
void Dictionary::addEntry(string* anEntry)
{
    // increase the size by 1 and rehash if theArray will be over 50 percent full
    if ((arrayCapacity/++arraySize) < 2) {rehash();}

    // add the new entry
    addEntry(anEntry, theArray, arrayCapacity);
}



/*---------------------------------------------------------------------------------------------------------*
 *                                                                                                         *
 *   Function Name: findEntry                                                                              *
 *                                                                                                         *
 *   Description:                                                                                          *
 *      Determine whether the string is in the dictionary                                                  *
 *                                                                                                         *
 *   Returns: true if the string is stored in the dictionary and false otherwise                           *
 *                                                                                                         *
 *   Precondition: none                                                                                    *
 *                                                                                                         *
 *   Postcondition: none                                                                                   *
 *                                                                                                         *
 *---------------------------------------------------------------------------------------------------------*/
bool Dictionary::findEntry(const string& key) const
{

    /* variables */
    int hashedIndex; // the initial index that the entry hashes to
    int offset; // the number of cells we move forward if there is a collision
    int currentArrayIndex; // the current index we are working with in theArray

    // find hashedIndex
    hashedIndex = hash(key, arrayCapacity);

    // if the cell of the array at the hashedIndex is empty
    if (theArray[hashedIndex] == nullptr) {
        return false;
    }
    else { // the cell of the array at the hashedIndex is not empty

        // if the word at the hashedIndex is the word we're looking for
        if (*(theArray[hashedIndex]) == key) {
            return true;
        }
        else { // the word at the hashedIndex of theArray is not the word we're looking for
            // find offset
            offset = calculateOffset(key, doubleHashNums[tableSizesIndex]);

            // set the currentArrayIndex to where our original hashedIndex is
            currentArrayIndex = hashedIndex;

            // search for an empty space or the key we're tasked with finding
            while ( ( theArray[currentArrayIndex] != nullptr ) && ( *(theArray[currentArrayIndex]) != key ) ) {
                currentArrayIndex = (currentArrayIndex + offset) % arrayCapacity;
            }
            if (theArray[currentArrayIndex] == nullptr) { // if the word is not in the dictionary
                return false;
            }
            else { // the word was found
                return true;
            }
        }
    }

}



/*---------------------------------------------------------------------------------------------------------*
 *                                                                                                         *
 *   Function Name: printDictionaryInOrder                                                                 *
 *                                                                                                         *
 *   Description:                                                                                          *
 *      print entries in order                                                                             *
 *                                                                                                         *
 *   Returns: n/a                                                                                          *
 *                                                                                                         *
 *   Precondition: none                                                                                    *
 *                                                                                                         *
 *   Postcondition: none                                                                                   *
 *                                                                                                         *
 *---------------------------------------------------------------------------------------------------------*/
void Dictionary::printDictionaryInOrder(ostream& outputStream) const
{
    /* convert dynamic array to a vector */
    // create and initialize vector
    vector<std::string> vectorArray;

    // copy items from theArray to vectorArray
    for (int currentIndex = 0; currentIndex < arrayCapacity; currentIndex++) {
        if (theArray[currentIndex] != nullptr) {
            vectorArray.push_back(*theArray[currentIndex]);
        }
    }

    // sort the vector
    std::sort(vectorArray.begin(), vectorArray.end());

    // print the vector
    for (std::string word : vectorArray) {
        outputStream << word << "\n";
    }
}



/*---------------------------------------------------------------------------------------------------------*
 *                                                                                                         *
 *   Function Name: printDictionaryKeys                                                                    *
 *                                                                                                         *
 *   Description:                                                                                          *
 *      Prints the dictionary keys only, demonstrating the dictionary structure                            *
 *                                                                                                         *
 *   Returns: n/a                                                                                          *
 *                                                                                                         *
 *   Precondition: none                                                                                    *
 *                                                                                                         *
 *   Postcondition: none                                                                                   *
 *                                                                                                         *
 *---------------------------------------------------------------------------------------------------------*/
void Dictionary::printDictionaryKeys(ostream& outputStream) const
{
    // loop through the array
    for (int arrayIndex = 0; arrayIndex < arrayCapacity; arrayIndex++) {
        // if the entry at arrayIndex is not null then send to outputStream
        if (theArray[arrayIndex] != nullptr) {
            outputStream << arrayIndex << ": " << *(theArray[arrayIndex]) << "\n";
        }
        else { // entry is null so only send the index, not the contents
            outputStream << arrayIndex << ": \n";
        }
    }

}



/*---------------------------------------------------------------------------------------------------------*
 *                                                                                                         *
 *   Function Name: clear                                                                                  *
 *                                                                                                         *
 *   Description:                                                                                          *
 *      clear helper method for copy constructor and assignment operator                                   *
 *                                                                                                         *
 *   Returns: n/a                                                                                          *
 *                                                                                                         *
 *   Precondition: none                                                                                    *
 *                                                                                                         *
 *   Postcondition: the data in theArray is gone                                                           *
 *                                                                                                         *
 *---------------------------------------------------------------------------------------------------------*/
void Dictionary::clear() {

    // loop through the array
    for (int arrayIndex = 0; arrayIndex < arrayCapacity; arrayIndex++) {

        // if the entry is not null then delete the string pointer
        if (theArray[arrayIndex] != nullptr) {
            delete theArray[arrayIndex];
        }
    }

    // delete the array
    delete[] theArray;
}



/*---------------------------------------------------------------------------------------------------------*
 *                                                                                                         *
 *   Function Name: copy                                                                                   *
 *                                                                                                         *
 *   Description:                                                                                          *
 *      copy helper method for copy constructor and assignment operator                                    *
 *                                                                                                         *
 *   Returns: n/a                                                                                          *
 *                                                                                                         *
 *   Precondition: none                                                                                    *
 *                                                                                                         *
 *   Postcondition: theArray has taken on the data that was in orig                                        *
 *                                                                                                         *
 *---------------------------------------------------------------------------------------------------------*/
void Dictionary::copy(const Dictionary& orig) {

    /* copy member variables */
    arraySize = orig.arraySize;
    arrayCapacity = orig.arrayCapacity;

    // copy the contents of the original array into this array
    theArray = new StringPtr[orig.arrayCapacity] {nullptr};
    for (int arrayIndex = 0; arrayIndex < arrayCapacity; arrayIndex++) {
        if (orig.theArray[arrayIndex] != nullptr) {
            theArray[arrayIndex] = new std::string(*(orig.theArray[arrayIndex]));
        }
    }
}



/*---------------------------------------------------------------------------------------------------------*
 *                                                                                                         *
 *   Function Name: rehash                                                                                 *
 *                                                                                                         *
 *   Description:                                                                                          *
 *      grows the hash table and reassigns old hash table entries                                          *
 *                                                                                                         *
 *   Returns: n/a                                                                                          *
 *                                                                                                         *
 *   Precondition: none                                                                                    *
 *                                                                                                         *
 *   Postcondition: theArray is now larger                                                                 *
 *                                                                                                         *
 *---------------------------------------------------------------------------------------------------------*/
void Dictionary::rehash() {

    int newCapacity; // the new theArray capacity


    // find new capacity for theArray
    newCapacity = tableSizes[++tableSizesIndex];

    // create temp array used to move over items from the old array 
    StringPtr* tempArray = new StringPtr[newCapacity] {nullptr}; 

    // copy over items from the old array to tempArray
    for (int arrayIndex = 0; arrayIndex < arrayCapacity; arrayIndex++) {
        if (theArray[arrayIndex] != nullptr) {
            addEntry(theArray[arrayIndex], tempArray, newCapacity);
        }
    }

    // delete the array
    delete[] theArray;

    // transfer which array theArray points to
    theArray = tempArray; 
    arrayCapacity = newCapacity;

}



/*---------------------------------------------------------------------------------------------------------*
 *                                                                                                         *
 *   Function Name: hash                                                                                   *
 *                                                                                                         *
 *   Description:                                                                                          *
 *      hash routine for string objects                                                                    *
 *                                                                                                         *
 *   Returns: the index that the input string hashes to                                                    *
 *                                                                                                         *
 *   Precondition: none                                                                                    *
 *                                                                                                         *
 *   Postcondition: none                                                                                   *
 *                                                                                                         *
 *---------------------------------------------------------------------------------------------------------*/
unsigned int Dictionary::hash(const std::string& word, int arrayCapacity) const {

    // declare and initialize the hash value for word
    unsigned int hashVal = 0;

    // for each character in the word add to overall hashVal
    for (char ch : word) {
        hashVal = 37 * hashVal + ch;
    }

    // return the final hashVal
    return hashVal % arrayCapacity;
}



/*---------------------------------------------------------------------------------------------------------*
 *                                                                                                         *
 *   Function Name: calculateOffset                                                                        *
 *                                                                                                         *
 *   Description:                                                                                          *
 *      second hash function used to calculate an offset                                                   *
 *                                                                                                         *
 *   Returns: the offset that the input string hashes to                                                   *
 *                                                                                                         *
 *   Precondition: none                                                                                    *
 *                                                                                                         *
 *   Postcondition: none                                                                                   *
 *                                                                                                         *
 *---------------------------------------------------------------------------------------------------------*/
int Dictionary::calculateOffset(const std::string& word, int arrayCapacity) const{

    // return the offset
    return ((hash(word, doubleHashNums[tableSizesIndex]) + 1));
}

/*---------------------------------------------------------------------------------------------------------*
 *                                                                                                         *
 *   Function Name: addEntry(anEntry, theArray)                                                            *
 *                                                                                                         *
 *   Description:                                                                                          *
 *      helper method for addEntry                                                                         *
 *                                                                                                         *
 *   Returns: n/a                                                                                          *
 *                                                                                                         *
 *   Precondition: none                                                                                    *
 *                                                                                                         *
 *   Postcondition: theArray now has the anEntry added to it                                               *
 *                                                                                                         *
 *---------------------------------------------------------------------------------------------------------*/
void Dictionary::addEntry(StringPtr anEntry, StringPtr* theArray, int capacityOfArrayAddedTo) {

    /* variables */
    int hashedIndex; // the initial index that the entry hashes to
    int offset; // the number of cells we move forward if there is a collision
    int currentArrayIndex; // the current index we are working with in theArray

    // find hashedIndex
    hashedIndex = hash(*anEntry, capacityOfArrayAddedTo);

    // if the cell of the array at the hashedIndex is empty
    if (theArray[hashedIndex] == nullptr) {

        theArray[hashedIndex] = anEntry;
    }
    else { // the cell of the array at the hashedIndex is not empty

        // find offset
        offset = calculateOffset(*anEntry, capacityOfArrayAddedTo);

        // set the currentArrayIndex to where our original hashedIndex is
        currentArrayIndex = hashedIndex;

        // search for an empty space to put the new entry
        while (theArray[currentArrayIndex] != nullptr) { // while the cell is not empty

            currentArrayIndex = (currentArrayIndex + offset) % capacityOfArrayAddedTo;
        }

        // add the new entry to the array
        theArray[currentArrayIndex] = anEntry;
    }
}