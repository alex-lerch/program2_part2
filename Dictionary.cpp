
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
 *      operator=                  help with dynamic memory management                                     *
 *      addEntry                   add an entry                                                            *
 *      findEntry                  determine whether the string is in the dictionary                       *
 *      printDictionaryInOrder     print entries in order                                                  *
 *      printDictionaryKeys        prints keys only, demonstrates dictionary structure                     *
 *      clear                      recursive clear helper                                                  *
 *      copy                       recursive copy helper                                                   *
 *      insert                     recursive helper method for insertion                                   *
 *      printInOrder               recursive helper for printDictionaryInOrder                             *
 *      printTree                  printDictionaryKeys helper, prints tree structure                       *
 *      balance                    rotates nodes and balances tree                                         *
 *      rotateWithLeftChild        single rotation with the left child                                     *
 *      doubleWithLeftChild        double rotation with the left child                                     *
 *      rotateWithRightChild       single rotation with the right child                                    *
 *      doubleWithRightChild       double rotation with the right child                                    *
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
 *   Member functions and operator function definitions                                                    *
 *---------------------------------------------------------------------------------------------------------*/

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
    if (this->root != rhs.root) //comparing the tree roots because that's as effective as comparing the object addresses here
    {
        clear();           // delete the current tree;
        copy(rhs); // copy rhs's tree into this
    }
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
    // call private recursive insert method
    insert(anEntry, root);
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
    Node* curNode = root;
    while (curNode && *(curNode->data) != key)
    {
        if (*(curNode->data) > key)
        {
            curNode = curNode->left;
        }
        else
        {
            curNode = curNode->right;
        }
    }
    return curNode != nullptr;
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
    if (root)
        printInOrder(outputStream, root);
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
    if (root)
        printTree(outputStream, root, 0);
}



/*---------------------------------------------------------------------------------------------------------*
 *                                                                                                         *
 *   Function Name: clear                                                                                  *
 *                                                                                                         *
 *   Description:                                                                                          *
 *      this is doing a postOrder traversal of the tree, deleting the string and then Node in each node    *
 *      of the tree the Dictionary is taking responsibility for the entry objects, because they have to    *
 *      be dynamically allocated and only the tree has them all. recursive clear helper                    *
 *                                                                                                         *
 *   Returns: n/a                                                                                          *
 *                                                                                                         *
 *   Precondition: none                                                                                    *
 *                                                                                                         *
 *   Postcondition: none                                                                                   *
 *                                                                                                         *
 *---------------------------------------------------------------------------------------------------------*/
void Dictionary::clear(Node* node)
{
    if (node)
    {
        clear(node->left);
        clear(node->right);
        delete node->data;
        delete node;
    }
}



/*---------------------------------------------------------------------------------------------------------*
 *                                                                                                         *
 *   Function Name: copy                                                                                   *
 *                                                                                                         *
 *   Description:                                                                                          *
 *      copy helper method for destructor and assignment operator. this is doing a postOrder traversal     *
 *      of the original tree, making a copy of each node                                                   *
 *                                                                                                         *
 *   Returns: nullptr if origNode is null, the copied origNode otherwise                                   *
 *                                                                                                         *
 *   Precondition: none                                                                                    *
 *                                                                                                         *
 *   Postcondition: none                                                                                   *
 *                                                                                                         *
 *---------------------------------------------------------------------------------------------------------*/
Dictionary::Node* Dictionary::copy(Dictionary::Node* origNode)
{
    if (origNode)
    {
        // recursively copy the left and right subtrees
        Node* newLeft = copy(origNode->left);
        Node* newRight = copy(origNode->right);

        string* newData = new string(*(origNode->data)); // copies the Entry from the original node
        int newHeight = origNode->height;

        Node* node = new Node(newData);
        node->height = newHeight;
        node->left = newLeft;
        node->right = newRight;

        return node;
    }
    else
    {
        return nullptr;
    }
}



/*---------------------------------------------------------------------------------------------------------*
 *                                                                                                         *
 *   Function Name: insert                                                                                 *
 *                                                                                                         *
 *   Description:                                                                                          *
 *      recursive helper method for insertion                                                              *
 *                                                                                                         *
 *   Returns: n/a                                                                                          *
 *                                                                                                         *
 *   Precondition: none                                                                                    *
 *                                                                                                         *
 *   Postcondition: none                                                                                   *
 *                                                                                                         *
 *---------------------------------------------------------------------------------------------------------*/
void Dictionary::insert(string* value, Node*& curPtr)
{
    if (!curPtr) // this is where the item goes
        curPtr = new Node(value);
    else if (*value < *(curPtr->data)) // heading left
        insert(value, curPtr->left);
    else // heading right
        insert(value, curPtr->right);

    // balances the tree as it navigates back up the tree
    balance(curPtr);
}



/*---------------------------------------------------------------------------------------------------------*
 *                                                                                                         *
 *   Function Name: printInOrder                                                                           *
 *                                                                                                         *
 *   Description:                                                                                          *
 *      recursive helper for printDictionaryInOrder. this is doing an inOrder traversal of the tree,       *
 *      calling printEntry on each entry in the tree                                                       *
 *                                                                                                         *
 *   Returns: n/a                                                                                          *
 *                                                                                                         *
 *   Precondition: none                                                                                    *
 *                                                                                                         *
 *   Postcondition: none                                                                                   *
 *                                                                                                         *
 *---------------------------------------------------------------------------------------------------------*/
void Dictionary::printInOrder(ostream& outputStream, Node* curNode) const
{
    string endOfLine = "\n"; // dealing with weird compiler issue
    if (curNode->left)
        printInOrder(outputStream, curNode->left);
    outputStream << (*(curNode->data)) << endOfLine;
    if (curNode->right)
        printInOrder(outputStream, curNode->right);
}



/*---------------------------------------------------------------------------------------------------------*
 *                                                                                                         *
 *   Function Name: printTree                                                                              *
 *                                                                                                         *
 *   Description:                                                                                          *
 *      printDictionaryKeys helper, prints tree structure. this is doing a preOrder traversal of the       *
 *      tree, printing it out in a way that shows the structure                                            *
 *                                                                                                         *
 *   Returns: n/a                                                                                          *
 *                                                                                                         *
 *   Precondition: none                                                                                    *
 *                                                                                                         *
 *   Postcondition: none                                                                                   *
 *                                                                                                         *
 *---------------------------------------------------------------------------------------------------------*/
void Dictionary::printTree(ostream& outputStream, Node* curNode, int depth) const
{
    string padding = "  "; // dealing with weird compiler error
    string endOfLine = "\n";
    for (int i = 0; i < depth; i++)
    {
        outputStream << padding;
    }
    outputStream << *(curNode->data) << endOfLine;
    if (curNode->left)
    {
        printTree(outputStream, curNode->left, depth + 1);
    }
    if (curNode->right)
    {
        printTree(outputStream, curNode->right, depth + 1);
    }
}



/*---------------------------------------------------------------------------------------------------------*
 *                                                                                                         *
 *   Function Name: balance                                                                                *
 *                                                                                                         *
 *   Description:                                                                                          *
 *      rotates nodes and balances tree until AVL conditions are satisfied.                                *
 *                                                                                                         *
 *   Returns: n/a                                                                                          *
 *                                                                                                         *
 *   Precondition: none                                                                                    *
 *                                                                                                         *
 *   Postcondition: none                                                                                   *
 *                                                                                                         *
 *---------------------------------------------------------------------------------------------------------*/
void Dictionary::balance(Node*& root) {
    /* if the root is nullptr */
    if (!root) {
        return;
    }
    /* if there is an imbalance from the left subtree of root */
    if ( height(root->left) - height(root->right) > ALLOWED_IMBALANCE ) {

        // if the imbalance is from the left child of the left subtree
        if ( height(root->left->left) >= height(root->left->right) ) {
            rotateWithLeftChild(root);
        }
        else { // the imbalance is from the right child of the left subtree
            doubleWithLeftChild(root);
        }
    }
    else { // check the balance factor to the right of root

        // if there is an imbalance from the right subtree of root
        if ( height(root->right) - height(root->left) > ALLOWED_IMBALANCE ) {

            // if the imbalance is from the right child of the right subtree
            if ( height(root->right->right) >= height(root->right->left) ) {
                rotateWithRightChild(root);
            }
            else { // the imbalance is from the left child of the right subtree
                doubleWithRightChild(root);
            }
        }
    }
    // set the new height
    root->height = max( height(root->left), height(root->right) ) + 1;

}



/*---------------------------------------------------------------------------------------------------------*
 *                                                                                                         *
 *   Function Name: rotateWithLeftChild                                                                    *
 *                                                                                                         *
 *   Description:                                                                                          *
 *      single rotation with the left child                                                                *
 *                                                                                                         *
 *   Returns: n/a                                                                                          *
 *                                                                                                         *
 *   Precondition: none                                                                                    *
 *                                                                                                         *
 *   Postcondition: none                                                                                   *
 *                                                                                                         *
 *---------------------------------------------------------------------------------------------------------*/
void Dictionary::rotateWithLeftChild(Node*& node) {
    /* rotate the left child */
    Node* child = node->left;
    node->left = child->right;
    child->right = node;

    /* set the new heights for node and child */
    node->height = max( height(node->left), height(node->right) ) + 1;
    child->height = max( height(child->left), height(child->right) ) + 1;

    // set the left subtree pointer of node's parent to child
    node = child;
}



/*---------------------------------------------------------------------------------------------------------*
 *                                                                                                         *
 *   Function Name: doubleWithLeftChild                                                                    *
 *                                                                                                         *
 *   Description:                                                                                          *
 *      double rotation with the left child implemented as two single rotations                            *
 *                                                                                                         *
 *   Returns: n/a                                                                                          *
 *                                                                                                         *
 *   Precondition: none                                                                                    *
 *                                                                                                         *
 *   Postcondition: none                                                                                   *
 *                                                                                                         *
 *---------------------------------------------------------------------------------------------------------*/
void Dictionary::doubleWithLeftChild(Node*& node) {
    rotateWithRightChild(node->left);
    rotateWithLeftChild(node);
}



/*---------------------------------------------------------------------------------------------------------*
 *                                                                                                         *
 *   Function Name: rotateWithRightChild                                                                   *
 *                                                                                                         *
 *   Description:                                                                                          *
 *      single rotation with the right child                                                               *
 *                                                                                                         *
 *   Returns: n/a                                                                                          *
 *                                                                                                         *
 *   Precondition: none                                                                                    *
 *                                                                                                         *
 *   Postcondition: none                                                                                   *
 *                                                                                                         *
 *---------------------------------------------------------------------------------------------------------*/
void Dictionary::rotateWithRightChild(Node*& node) {
    /* rotate the right child */
    Node* child = node->right;
    node->right = child->left;
    child->left = node;

    /* set the new heights for node and child */
    node->height = max( height(node->left), height(node->right) ) + 1;
    child->height = max( height(child->left), height(child->right) ) + 1;

    // set the right subtree pointer of node's parent to child
    node = child;
}



/*---------------------------------------------------------------------------------------------------------*
 *                                                                                                         *
 *   Function Name: doubleWithRightChild                                                                   *
 *                                                                                                         *
 *   Description:                                                                                          *
 *      double rotation with the right child implemented as two single rotations                           *
 *                                                                                                         *
 *   Returns: n/a                                                                                          *
 *                                                                                                         *
 *   Precondition: none                                                                                    *
 *                                                                                                         *
 *   Postcondition: none                                                                                   *
 *                                                                                                         *
 *---------------------------------------------------------------------------------------------------------*/
void Dictionary::doubleWithRightChild(Node*& node) {
    rotateWithLeftChild(node->right);
    rotateWithRightChild(node);
}
