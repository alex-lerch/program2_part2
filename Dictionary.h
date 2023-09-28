
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

    // the array that stores the data items
    StringPtr* theArray;

    // the current size of the array
    int arraySize;

    // the current capacity of the array
    int arrayCapacity;

    // stores the correct index for the table sizes
    int tableSizesIndex;


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

    // grows the hash table and reassigns old hash table entries 
    void rehash();

    // hash routine for string objects
    unsigned int hash(const std::string& word, int arrayCapacity) const;

    // second hash function used to calculate an offset
    int calculateOffset(const std::string& word, int arrayCapacity) const;

    void addEntry(StringPtr anEntry, StringPtr* theArray);

};

// closing file definition
#endif