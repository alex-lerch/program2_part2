
/*---------------------------------------------------------------------------------------------------------*
 *                                                                                                         *
 *   File: Dictionary.h                                                                                    *
 *                                                                                                         *
 *   Description:                                                                                          *
 *      A dictionary created using an AVL tree                                                             *
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
 *                                                                                                         *
 *   Class Interface: Dictionary                                                                           *
 *                                                                                                         *
 *   Description:                                                                                          *
 *      An dictionary created using a basic binary search tree                                             *
 *                                                                                                         *
 *---------------------------------------------------------------------------------------------------------*/
class Dictionary
{

/*---------------------------------------------------------------------------------------------------------*
 *   Private Structures and Member Variables                                                               *
 *---------------------------------------------------------------------------------------------------------*/
private:
    struct Node // struct because I want everything to be public within the Node
    {
        std::string* data; // the data being stored in the node
        Node* left; // the left subtree of the node
        Node* right; // the right subtree of the node
        int height; // the height of the node

        // constructor
        Node(std::string*& theData): data(theData), left(nullptr), right(nullptr), height(0) {}
    };

    /* private instance variables */
    Node* root;


/*---------------------------------------------------------------------------------------------------------*
 *   Public Member Functions                                                                               *
 *---------------------------------------------------------------------------------------------------------*/
public:
    // definition for the allowed imbalance of the tree
    #define ALLOWED_IMBALANCE 1

    // Constructor
    Dictionary(): root(nullptr) {}

    // Copy constructor
    Dictionary(const Dictionary& orig) { copy(orig); }

    // Destructor
    ~Dictionary() { clear(); }

    // Assignment operator
    Dictionary& operator=(const Dictionary& rhs);

    // Check to see if the Dictionary isEmpty
    bool isEmpty() const { return root == nullptr; }

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
    void clear() { clear(root); }

    // recursive clear helper
    void clear(Node* node);

    // copy helper method for destructor and assignment operator
    void copy(const Dictionary& orig) { this->root = copy(orig.root); }

    // recursive copy helper
    Node* copy(Node* origNode);

    // recursive helper method for insertion
    void insert(std::string* value, Node*& curPtr);

    // recursive helper for printDictionaryInOrder
    void printInOrder(std::ostream& outputStream, Node* curNode) const;

    // tree printer helper -- recursive function to print the tree structure
    void printTree(std::ostream& outputStream, Node* curNode, int depth) const;

    // rotates nodes and balances tree until AVL conditions are satisfied
    void balance(Node*& root);

    // returns the height of the node or -1 if the node is nullptr
    int height(Node* node) {return node == nullptr ? -1 : node->height;}

    // single rotation with the left child
    void rotateWithLeftChild(Node*& node);

    // double rotation with the left child implemented as two single rotations
    void doubleWithLeftChild(Node*& node);

    // single rotation with the right child
    void rotateWithRightChild(Node*& node);

    // double rotation with the right child implemented as two single rotations
    void doubleWithRightChild(Node*& node);
    
};

// closing file definition
#endif