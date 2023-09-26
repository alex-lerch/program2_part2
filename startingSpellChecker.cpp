// Program to perform spell checking
// The program will take 3 command line parameters, the names of two input files and one output file.
// The input files will be
//      1) a list of correctly spelled words, which will be stored in a dictionary
//      2) a file to check for correct spelling
// The output file will show the structure of the dictionary that was created (done for grading purposes)
// The program will output a list of incorrectly spelled words and suggestions for each word.
// By Mary Elaine Califf and

#include "Dictionary.h"
#include <iostream>
#include <fstream>
#include <ctype.h>
using namespace std;

// function prototypes

// opens and reads the word list input file, building the dictionary
void buildDictionary(const string& inFileName, Dictionary& dict);

// opens the input file and checks the spelling of the input file, producing output to standard out
void checkSpelling(const string& inFileName, const Dictionary& dict);

// open the dictionary structure file and write the structure of the dictionary to it
void writeDictionaryStructure(const string& outFileName, const Dictionary& dict);

// your additional function prototypes go here


int main(int argc, char** argv)
{
    // gather the file name arguments
    if (argc < 4)
    {
        // we didn't get enough arguments, so complain and quit
        cout << "Usage: " << argv[0] << " wordListFile inputFile dictionaryStructureFile" << endl;
        exit(1);
    }

    string wordListFileName = argv[1];
    string inputFileName = argv[2];
    string dictFileName = argv[3];

    Dictionary dict; // set up the dictionary

    // build the dictionary
    buildDictionary(wordListFileName, dict);

    // write the dictionary to the concordance file
    checkSpelling(inputFileName, dict);

    // write the dictionary structure to the dictionary structure file
    writeDictionaryStructure(dictFileName, dict);
}

void buildDictionary(const string& inFileName, Dictionary& dict)
{
    string curWord = "";

    // open the file
    ifstream infile(inFileName);
    if (infile.fail())
    {
        cerr << "Could not open " << inFileName << " for input" << endl;
        exit(1);
    }

    // YOUR CODE GOES HERE -- feel free to also add additional function(s) if desired

    // close the file
    infile.close();
}

void checkSpelling(const string& inFileName, const Dictionary& dict)
{
    int lineNum = 1;
    string curWord = "";

    ifstream infile(inFileName);
    if (infile.fail())
    {
        cerr << "Could not open " << inFileName << " for input\n";
        return;
    }

    // YOUR CODE GOES HERE -- you will want to add additional function(s) to further break down this logic 


    infile.close();
}

void writeDictionaryStructure(const string& outFileName, const Dictionary& dict)
{
    ofstream outfile(outFileName);
    if (outfile.fail())
    {
        cerr << "Could not open " << outFileName << " for output\n";
        cerr << "Dictionary structure file not written " << endl;
        return;
    }
    dict.printDictionaryKeys(outfile);
    outfile.close();
}

// your additional function implementations go here
