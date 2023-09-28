
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

    //asl debug
    std::cout << "theArray before adding '" << *anEntry << "'" << std::endl;
    printDictionaryKeys(cout);
    std::cout << std::endl;

    // add the new entry
    addEntry(anEntry, theArray);

    //asl debug
    std::cout << "theArray after adding '" << *anEntry << "'" << std::endl;
    printDictionaryKeys(cout);
    std::cout << std::endl;
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

    //asl debug
    std::cout << "in printDictionaryKeys" << std::endl;

    for (int arrayIndex = 0; arrayIndex < arrayCapacity; arrayIndex++) {

        //asl debug
        std::cout << "looking at index " << arrayIndex << std::endl;


        if (theArray[arrayIndex] != nullptr) {
            outputStream << arrayIndex << ": " << *(theArray[arrayIndex]) << "\n";
        }
        else {
            outputStream << arrayIndex << ": \n";
        }
    }

    //asl debug
    std::cout << "finished printing the keys of the dictionary" << std::endl;

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
 *   Postcondition: none                                                                                   *
 *                                                                                                         *
 *---------------------------------------------------------------------------------------------------------*/
void Dictionary::rehash() {

    //asl debug
    std::cout << "\n\n\njust entered rehash function\n\n" << std::endl;

    int newCapacity; // the new theArray capacity


    // find new capacity for theArray
    newCapacity = tableSizes[++tableSizesIndex];

    // create temp array used to move over items from the old array 
    StringPtr* tempArray = new StringPtr[newCapacity];

    // copy over items from the old array to tempArray
    for (int arrayIndex = 0; arrayIndex < arrayCapacity; arrayIndex++) {
        if (theArray[arrayIndex] != nullptr) {
            addEntry(theArray[arrayIndex], tempArray);
        }
    }

    // clear the dynamic data from theArray
    for (int arrayIndex = 0; arrayIndex < arrayCapacity; arrayIndex++) {
        if (theArray[arrayIndex] != nullptr) {
            delete theArray[arrayIndex];
        }
    }

    // transfer which array theArray points to
    theArray = tempArray;

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
    unsigned int hashVal = 0;

    for (char ch : word) {
        hashVal = 37 * hashVal + ch;
    }

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
 *   Postcondition: none                                                                                   *
 *                                                                                                         *
 *---------------------------------------------------------------------------------------------------------*/
void Dictionary::addEntry(StringPtr anEntry, StringPtr* theArray) {

    //asl debug
    std::cout << "\nin addEntry helper method with '" << *anEntry << "'" << std::endl; 

    /* variables */
    int hashedIndex; // the initial index that the entry hashes to
    int offset; // the number of cells we move forward if there is a collision
    int currentArrayIndex; // the current index we are working with in theArray

    // find hashedIndex
    hashedIndex = hash(*anEntry, arrayCapacity);

    //asl debug
    std::cout << "hashedIndex for '" << *anEntry << "' is " << hashedIndex << std::endl;

    // if the cell of the array at the hashedIndex is empty
    if (theArray[hashedIndex] == nullptr) {

        // asl debug
        std::cout << "no collision for '" << *anEntry << "'" << std::endl;

        theArray[hashedIndex] = anEntry;

        //asl debug
        std::cout << *anEntry << "added " << *theArray[hashedIndex] << " to array at index " << hashedIndex << std::endl;
    }
    else { // the cell of the array at the hashedIndex is not empty

        //asl debug
        std::cout << "collision occured at index " << hashedIndex << " for '" << *anEntry << "'" << std::endl;

        // find offset
        offset = calculateOffset(*anEntry, arrayCapacity);

        //asl debug
        std::cout << "offset for '" << *anEntry << " just calculated and it is " << offset << std::endl;

        // set the currentArrayIndex to where our original hashedIndex is
        currentArrayIndex = hashedIndex;

        //asl debug
        std::cout << "currentArrayIndex is assigned from hashedIndex which is " << hashedIndex << std::endl;

        // search for an empty space to put the new entry
        while (theArray[currentArrayIndex] != nullptr) { // while the cell is not empty

            //asl debug
            std::cout << "just checked index " << currentArrayIndex << " and there was something there so we move to the next location" << std::endl;

            currentArrayIndex = (currentArrayIndex + offset) % arrayCapacity;

            //asl debug
            std::cout << "just moved to next location which is " << currentArrayIndex << std::endl;
        }

        //asl debug
        std::cout << "found an empty space for '" << *anEntry << "' at index " << currentArrayIndex << std::endl;

        //asl debug
        std::cout << "checking to see if anEntry is a nullptr -> ";
        std::string result = (anEntry == nullptr) ? "nullptr" : "not nullptr";
        std::cout << result << std::endl;

        // add the new entry to the array
        theArray[currentArrayIndex] = anEntry;

        //asl debug
        std::cout << "just added '" << *anEntry << "' to the array at index " << currentArrayIndex << ". now, theArray[" << currentArrayIndex << "] = " << *theArray[currentArrayIndex] << std::endl;
    }
}