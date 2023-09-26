// Program to perform spell checking
// The program will take 3 command line parameters, the names of two input files and one output file.
// The input files will be
//      1) a list of correctly spelled words, which will be stored in a dictionary
//      2) a file to check for correct spelling
// The output file will show the structure of the dictionary that was created (done for grading purposes)
// The program will output a list of incorrectly spelled words and suggestions for each word.
// By Mary Elaine Califf and Alex Lerch



/*---------------------------------------------------------------------------------------------------------*
 *   Header Files                                                                                          *
 *---------------------------------------------------------------------------------------------------------*/
#include "Dictionary.h"
#include <iostream>
#include <fstream>
#include <ctype.h>
using namespace std;



/*---------------------------------------------------------------------------------------------------------*
 *   Function Prototypes                                                                                   *
 *---------------------------------------------------------------------------------------------------------*/
// manipulates the misspelled word and checks alterations against the dictionary to provide possible correct suggestions
void generateSuggestions(std::string misspelledWord, const Dictionary& dict, int lineNum);

// adds one letter to every position of the word to try to find correct suggestions
void addOneLetter(std::string misspelledWord, const Dictionary& dict, bool& isSuggestionFound, bool& hasDisplayedSuggestionMessage);

// removes one letter at each position and with each removal the new word is attempted to match against the dictionary
void removeOneLetter(std::string misspelledWord, const Dictionary& dict, bool& isSuggestionFound, bool& hasDisplayedSuggestionMessage);

// swaps the adjacent letters in misspelledWord and then checks the new word against the dictionary to look for correct suggestions
void swapAdjacentLetters(std::string misspelledWord, const Dictionary& dict, bool& isSuggestionFound, bool& hasDisplayedSuggestionMessage);

// opens and reads the word list input file, building the dictionary
void buildDictionary(const string& inFileName, Dictionary& dict);

// opens the input file and checks the spelling of the input file, producing output to standard out
void checkSpelling(const string& inFileName, const Dictionary& dict);

// open the dictionary structure file and write the structure of the dictionary to it
void writeDictionaryStructure(const string& outFileName, const Dictionary& dict);



/*---------------------------------------------------------------------------------------------------------*
 *   Main Function                                                                                         *
 *---------------------------------------------------------------------------------------------------------*/
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

    // set up the dictionary
    Dictionary dict;

    // build the dictionary
    buildDictionary(wordListFileName, dict);

    // write the dictionary to the concordance file
    checkSpelling(inputFileName, dict);

    // write the dictionary structure to the dictionary structure file
    writeDictionaryStructure(dictFileName, dict);

} // end of main



/*---------------------------------------------------------------------------------------------------------*
 *   Function Definitions                                                                                  *
 *---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*
 *                                                                                                         *
 *   Function Name: buildDictionary                                                                        *
 *                                                                                                         *
 *   Description:                                                                                          *
 *      opens and reads the word list input file, building the dictionary                                  *
 *                                                                                                         *
 *   Returns: n/a                                                                                          *
 *                                                                                                         *
 *---------------------------------------------------------------------------------------------------------*/
void buildDictionary(const string& inFileName, Dictionary& dict)
{
    // the current word being built
    string curWord = "";

    // open the file
    ifstream infile(inFileName);
    if (infile.fail())
    {
        cerr << "Could not open " << inFileName << " for input" << endl;
        exit(1);
    }

    // YOUR CODE GOES HERE -- feel free to also add additional function(s) if desired
    char curChar = std::tolower(infile.get());
    /* while it is not the end of the file */
    while (!infile.eof()) {
        // if curChar is a-z
        if (isalpha(curChar)) {
            // add curChar to the back of curWord
            curWord.push_back(curChar);
        }
        else { // curChar is not a-z
            // if curWord is not empty
            if (curWord != "") {
                // add curWord to the dictionary
                dict.addEntry(new std::string(curWord));
            }
            // reset curWord
            curWord = "";
        }
        // get next character in the file
        curChar = std::tolower(infile.get());
    }
    // close the file
    infile.close();
}



/*---------------------------------------------------------------------------------------------------------*
 *                                                                                                         *
 *   Function Name: checkSpelling                                                                          *
 *                                                                                                         *
 *   Description:                                                                                          *
 *      opens the input file and checks the spelling of the input file, producing output to standard out   *
 *                                                                                                         *
 *   Returns: n/a                                                                                          *
 *                                                                                                         *
 *---------------------------------------------------------------------------------------------------------*/
void checkSpelling(const string& inFileName, const Dictionary& dict)
{
    // the text file line number that is currently being processed
    int lineNum = 1;

    // the current word being built
    string curWord = "";

    ifstream infile(inFileName);
    if (infile.fail())
    {
        cerr << "Could not open " << inFileName << " for input\n";
        return;
    }

    // the current character in the text file that is being worked with
    char curChar = std::tolower(infile.get());

    /* while the end of the file has not been reached */
    while (!infile.eof()) {
        if (isalpha(curChar)) { // if curChar is a letter
            curWord.push_back(curChar);
        }
        else { // curChar is not a letter
            if ( curWord != "" && (!dict.findEntry(curWord)) ) { // if curWord has at least one letter and curWord is not in the dictionary
                // generate suggestions for word
                generateSuggestions(curWord, dict, lineNum);
            }
            if (curChar == '\n') { // if the curChar is the new line character
                // increase the line number
                lineNum++;
            }
            // reset the curWord
            curWord = "";
        }
        // get the next character in the text file and make it lower case
        curChar = std::tolower(infile.get());
    }


    infile.close();
}



/*---------------------------------------------------------------------------------------------------------*
 *                                                                                                         *
 *   Function Name: writeDictionaryStructure                                                               *
 *                                                                                                         *
 *   Description:                                                                                          *
 *      open the dictionary structure file and write the structure of the dictionary to it                 *
 *                                                                                                         *
 *   Returns: n/a                                                                                          *
 *                                                                                                         *
 *---------------------------------------------------------------------------------------------------------*/
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



/*---------------------------------------------------------------------------------------------------------*
 *                                                                                                         *
 *   Function Name: generateSuggestions                                                                    *
 *                                                                                                         *
 *   Description:                                                                                          *
 *      manipulates the misspelled word and checks alterations against the dictionary to provide           *
 *      possible correct suggestions                                                                       *
 *                                                                                                         *
 *   Returns: n/a                                                                                          *
 *                                                                                                         *
 *---------------------------------------------------------------------------------------------------------*/
void generateSuggestions(std::string misspelledWord, const Dictionary& dict, int lineNum) {

    /* variable instantiation */
    bool hasDisplayedSuggestionMessage = false; // has 'suggested corrections:' been displayed yet
    bool isSuggestionFound = false; // has a word suggestion been found yet

    // print which line the misspelled word was found on
    std::cout << misspelledWord << " on line " << lineNum;

    // checks for a word suggestion by adding letters to the misspelledWord
    addOneLetter(misspelledWord, dict, isSuggestionFound, hasDisplayedSuggestionMessage);

    // checks for a word suggestion by removing a letter from misspelled word for each position in misspelledWord
    removeOneLetter(misspelledWord, dict, isSuggestionFound, hasDisplayedSuggestionMessage);

    // checks for a word suggestion by swapping adjacent letters in the misspelledWord
    swapAdjacentLetters(misspelledWord, dict, isSuggestionFound, hasDisplayedSuggestionMessage);

    /* if no suggestions were found, print message indicating this */
    if (!isSuggestionFound) { // if no suggestion is found
        std::cout << "\nNo suggestions found\n";
    }
}



/*---------------------------------------------------------------------------------------------------------*
 *                                                                                                         *
 *   Function Name: addOneLetter                                                                           *
 *                                                                                                         *
 *   Description:                                                                                          *
 *     inserts each letter a-z into each index of the misspelled word. after each insertion, the newly     *
 *     created word is check against the dictionary to see if it is now a valid word. If it is a valid     *
 *     word, then the suggestion is displayed                                                              *
 *                                                                                                         *
 *   Returns: n/a                                                                                          *
 *                                                                                                         *
 *---------------------------------------------------------------------------------------------------------*/
void addOneLetter(std::string misspelledWord, const Dictionary& dict, bool& isSuggestionFound, bool& hasDisplayedSuggestionMessage) {

    /* adds one letter to every position of the word to try to find correct suggestions and prints valid
       corrections to the screen */
    for (int misspelledWordIndex = 0; misspelledWordIndex <= misspelledWord.length(); misspelledWordIndex++) { // for each index in the misspelledWord
        for (char letter = 'a'; letter <= 'z'; letter++) { // for each letter in the alphabet

            // create string to hold new words that will be created
            std::string possibleCorrection = misspelledWord; // represents a possible corrected word

            // insert the current letter into the current index of possibleCorrection
            possibleCorrection.insert(misspelledWordIndex, 1, letter);

            /* if the newly created possibleCorrection is found in the dictionary, then print possibleCorrection to the screen */
            if (dict.findEntry(possibleCorrection)) { // if possibleCorrection is in the dictionary

                /* if the suggested corrections message hasn't been displayed yet do that and change flag to true*/
                if (!hasDisplayedSuggestionMessage) { // if suggested corrections message has't been displayed

                    // print the suggested corrections message
                    std::cout << "\nSuggested corrections:\n";

                    // set the suggested corrections message flag to true because we have now display the message
                    hasDisplayedSuggestionMessage = true;
                }

                // set the suggestion found flag to true because we have found at least one correct suggestion
                isSuggestionFound = true;
                std::cout << "    " << possibleCorrection << "\n";
            }
        }
    }
}



/*---------------------------------------------------------------------------------------------------------*
 *                                                                                                         *
 *   Function Name: removeOneLetter                                                                        *
 *                                                                                                         *
 *   Description:                                                                                          *
 *      removes one letter at each position and with each removal the new word is attempted to match       *
 *      against the dictionary                                                                             *
 *                                                                                                         *
 *   Returns: n/a                                                                                          *
 *                                                                                                         *
 *---------------------------------------------------------------------------------------------------------*/
void removeOneLetter(std::string misspelledWord, const Dictionary& dict, bool& isSuggestionFound, bool& hasDisplayedSuggestionMessage) {
    for (int misspelledWordIndex = 0; misspelledWordIndex <= misspelledWord.length(); misspelledWordIndex++) { // for each index in the misspelled word
        std::string possibleCorrection = misspelledWord; // represents a possible corrected word

        // erase possibleCorrection's letter at the currect index
        possibleCorrection.erase(misspelledWordIndex, 1);


        /* if the newly created possibleCorrection is found in the dictionary, then print possibleCorrection to the screen */
        if (dict.findEntry(possibleCorrection)) { // if possibleCorrection is in the dictionary

            /* if the suggested corrections message hasn't been displayed yet do that and change flag to true*/
            if (!hasDisplayedSuggestionMessage) { // if suggested corrections message has't been displayed

                // print the suggested corrections message
                std::cout << "\nSuggested corrections:\n";

                // set the suggested corrections message flag to true because we have now display the message
                hasDisplayedSuggestionMessage = true;
            }

            // set the suggestion found flag to true because we have found at least one correct suggestion
            isSuggestionFound = true;
            std::cout << "    " << possibleCorrection << "\n";
        }
    }
}



/*---------------------------------------------------------------------------------------------------------*
 *                                                                                                         *
 *   Function Name: swapAdjacentLetters                                                                    *
 *                                                                                                         *
 *   Description:                                                                                          *
 *      swaps the adjacent letters in misspelledWord and then checks the new word against the dictionary   *
 *      to look for correct suggestions                                                                    *
 *                                                                                                         *
 *   Returns: n/a                                                                                          *
 *                                                                                                         *
 *---------------------------------------------------------------------------------------------------------*/
void swapAdjacentLetters(std::string misspelledWord, const Dictionary& dict, bool& isSuggestionFound, bool& hasDisplayedSuggestionMessage) {
    for (int misspelledWordIndex = 0; misspelledWordIndex <= misspelledWord.length(); misspelledWordIndex++) { // for each index in the misspelled word

        std::string possibleCorrection = misspelledWord; // represents a possible corrected word

        // swap the two adjacent letters in possibleCorrection at the current index
        std::swap(possibleCorrection[misspelledWordIndex], possibleCorrection[misspelledWordIndex + 1]);


        /* if the newly created possibleCorrection is found in the dictionary, then print possibleCorrection to the screen */
        if (dict.findEntry(possibleCorrection)) { // if possibleCorrection is in the dictionary

            /* if the suggested corrections message hasn't been displayed yet do that and change flag to true*/
            if (!hasDisplayedSuggestionMessage) { // if suggested corrections message has't been displayed

                // print the suggested corrections message
                std::cout << "\nSuggested corrections:\n";

                // set the suggested corrections message flag to true because we have now display the message
                hasDisplayedSuggestionMessage = true;
            }

            // set the suggestion found flag to true because we have found at least one correct suggestion
            isSuggestionFound = true;
            std::cout << "    " << possibleCorrection << "\n";
        }
    }
}