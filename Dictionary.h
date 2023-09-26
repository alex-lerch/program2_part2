
/*---------------------------------------------------------------------------------------------------------*
 *                                                                                                         *
 *   File: Dictionary.h                                                                                    *
 *                                                                                                         *
 *   Description:                                                                                          *
 *      A dictionary created using a hash table                                                            *
 *                                                                                                         *
 *   Authors: Mary Elaine Califf and Alex Lerch                                                            *
 *                                                                                                         *
 *---------------------------------------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------------------------------------*
 *   Header Files                                                                                          *
 *---------------------------------------------------------------------------------------------------------*/
#include <string>

/*---------------------------------------------------------------------------------------------------------*
 *   File Definition                                                                                       *
 *---------------------------------------------------------------------------------------------------------*/
#ifndef DICTIONARY_H
#define DICTIONARY_H

/*---------------------------------------------------------------------------------------------------------*
 *   Type Definitions                                                                                      *
 *---------------------------------------------------------------------------------------------------------*/
typedef std::string* StringPtr;


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
 *                                                                                                         *
 *   Class Interface: Dictionary                                                                           *
 *                                                                                                         *
 *   Description:                                                                                          *
 *      An dictionary created using a hash table                                                           *
 *                                                                                                         *
 *---------------------------------------------------------------------------------------------------------*/
class Dictionary
{

/*---------------------------------------------------------------------------------------------------------*
 *   Private Member Variables and structs                                                                  *
 *---------------------------------------------------------------------------------------------------------*/
private:
    
    // the string data of the array cell
    StringPtr data;

    // the array that stores the data items
    StringPtr* theArray;

    // the current size of the array
    int arraySize;

    // the current capacity of the array
    int arrayCapacity;


/*---------------------------------------------------------------------------------------------------------*
 *   Public Member Functions                                                                               *
 *---------------------------------------------------------------------------------------------------------*/
public:
    
    // Constructor
    Dictionary();

    // Copy constructor
    Dictionary(const Dictionary& orig) { copy(orig); }

    // Destructor
    ~Dictionary() { clear(); }

    // Assignment operator
    Dictionary& operator=(const Dictionary& rhs);

    // Check to see if the Dictionary isEmpty
    bool isEmpty() const { return arraySize == 0; }

    // Add an entry
    // Precondition: the dictionary must not have the identical string already stored in the dictionary
    // Postcondition: the string has been added to the dictionary
    void addEntry(std::string* anEntry);

    // Determine whether the string is in the dictionary
    // Returns true if the string is stored in the dictionary and false otherwise
    bool findEntry(const std::string& key) const;

    // Print entries in order
    // Calls printEntry on each Entry in order
    void printDictionaryInOrder(std::ostream& outputStream) const;

    // Prints the dictionary keys only, demonstrating the dictionary structure
    // For the binary search tree, this is an easy to do tree format
    void printDictionaryKeys(std::ostream& outputStream) const;


/*---------------------------------------------------------------------------------------------------------*
 *   Private Member Functions                                                                              *
 *---------------------------------------------------------------------------------------------------------*/
private:
    // clear helper method for copy constructor and assignment operator
    void clear();

    // copy helper method for destructor and assignment operator
    void copy(const Dictionary& orig);

    // recursive helper for printDictionaryInOrder
    void printInOrder(std::ostream& outputStream, Node* curNode) const;

    // rehashes the array 

};

// closing file definition
#endif