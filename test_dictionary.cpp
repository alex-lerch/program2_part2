// test file
#include "Dictionary.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

int main()
{

    Dictionary* myDict = new Dictionary;
    string str = "firstWord";

    string* myEntry = new string(str);
    myDict->addEntry(myEntry);
    str = "goodStuff";
    myEntry = new string(str);
    myDict->addEntry(myEntry);
    str = "abc";
    myEntry = new string(str);
    myDict->addEntry(myEntry);
    str = "someWord";
    myEntry = new string(str);
    myDict->addEntry(myEntry);

    Dictionary secondDict(*myDict); // use copy constructor to create 2nd dictionary

    Dictionary thirdDict;
    thirdDict = secondDict; // assignment operator with 2nd dictionary to 3rd dictionary

    //asl debug
    std::cout << "assignment operator just used to create thirdDict from secondDict" << std::endl;
    std::cout << "thirdDict is " << std::endl;
    thirdDict.printDictionaryKeys(cout);
    std::cout << std::endl;
    

    str = "bbbb";
    myEntry = new string(str);
    myDict->addEntry(myEntry);

    //asl debug
    std::cout << "thirdDict.findEntry(\"bbbb\") returns " << thirdDict.findEntry("bbbb") << std::endl;
    std::cout << "\n'bbbb' just added and thirdDict is " << std::endl;
    thirdDict.printDictionaryKeys(cout);
    std::cout << std::endl;

    str = "mmmm";
    myEntry = new string(str);
    secondDict.addEntry(myEntry);

    //asl debug
    std::cout << "\n'mmmm' just added and thirdDict is " << std::endl;
    thirdDict.printDictionaryKeys(cout);
    std::cout << std::endl;

    str = "zzzz";
    myEntry = new string(str);
    thirdDict.addEntry(myEntry);

    //asl debug
    std::cout << "\n'zzzz' just added and thirdDict is " << std::endl;
    thirdDict.printDictionaryKeys(cout);
    std::cout << std::endl;

    cout << "\nprint original modified dictionary" << endl;
    myDict->printDictionaryKeys(cout);

    cout << "\nprint second modified dictionary" << endl;
    secondDict.printDictionaryKeys(cout);

    cout << "\nprint third modified dictionary" << endl;
    thirdDict.printDictionaryKeys(cout);

    str = "deaf";
    if (myDict->findEntry("deaf"))
        cout << "we have a problem" << endl;

    str = "zzzz";
    if (myDict->findEntry(str))
        cout << "we have a problem" << endl;

    str = "bbbb";
    if (secondDict.findEntry(str))
        cout << "we have a problem" << endl;

    if (thirdDict.findEntry(str))
        cout << "we have a problem" << endl;


    myDict->printDictionaryInOrder(cout);

    delete myDict;

    cout << "\nprinting second dictionary after deleting the first" << endl;
    secondDict.printDictionaryInOrder(cout);

    cout << "\nprinting third dictionary after deleting the first" << endl;
    thirdDict.printDictionaryInOrder(cout);
}