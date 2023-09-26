
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
 *                                                                                                         *
 *---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*
 *   Header Files                                                                                          *
 *---------------------------------------------------------------------------------------------------------*/
#include "Dictionary.h"
#include <iostream> 


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

}



/*---------------------------------------------------------------------------------------------------------*
 *                                                                                                         *
 *   Function Name: printDictionaryInOrder                                                                 *
 *                                                                                                         *
 *   Description:                                                                                          *
 *      print entries in order. calls printEntry on each entry in order                                    *
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
    outputStream << "whatever";
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
 *   Postcondition: none                                                                                   *
 *                                                                                                         *
 *---------------------------------------------------------------------------------------------------------*/
void Dictionary::clear() {
    for (int arrayIndex = 0; arrayIndex < arrayCapacity; arrayIndex++) {
        if (theArray[arrayIndex] != nullptr) {
            delete theArray[arrayIndex];
        }
    }
    delete[] theArray;
}



/*---------------------------------------------------------------------------------------------------------*
 *                                                                                                         *
 *   Function Name: copy                                                                                   *
 *                                                                                                         *
 *   Description:                                                                                          *
 *      copy helper method for destructor and assignment operator                                          *
 *                                                                                                         *
 *   Returns: n/a                                                                                          *
 *                                                                                                         *
 *   Precondition: none                                                                                    *
 *                                                                                                         *
 *   Postcondition: none                                                                                   *
 *                                                                                                         *
 *---------------------------------------------------------------------------------------------------------*/
void Dictionary::copy(const Dictionary& orig) {

    /* copy member variables */
    arraySize = orig.arraySize;
    arrayCapacity = orig.arrayCapacity;

    // copy the contents of the original array into this array
    theArray = new StringPtr[orig.arrayCapacity];
    for (int arrayIndex = 0; arrayIndex < arrayCapacity; arrayIndex++) {
        if (orig.theArray[arrayIndex] != nullptr) {
            theArray[arrayIndex] = new std::string(*(orig.theArray[arrayIndex]));
        }
    }
}