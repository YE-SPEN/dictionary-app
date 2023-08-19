// DictionaryApp.cpp
// Purpose: Run Execution of Final Dictionary Class

/* ******************************************

 * @authors: Eric Spensieri
 * @version: 1.0
 * @since: May 23, 2023

 ******************************************** */

#ifndef DICTIONARYAPP_CPP
#define DICTIONARYAPP_CPP

#include <iostream>
#include <string>
#include "Dictionary.h"

using std::cout;
using std::cin;
using std::string;
using std::endl;

int main() {
    cout << "Welcome to Assignment #2!" << endl;
    cout << "=========================" << endl << endl;
    
    // read input file name
    cout << "Enter the name of input text file:  ";
    string filename;
    cin >> filename;

    int action = -1;
    while (action != 0) {

        // display menu options
        bool inError = true;
        while (inError) {
            cout << endl;
            cout << "Choose one of the following options" << endl;
            cout << "1 - Print input lines" << endl;
            cout << "2 - Print original unsorted words" << endl;
            cout << "3 - Print words sorted by text" << endl;
            cout << "4 - Print words sorted by frequency" << endl;
            cout << "5 - Print words sorted by length" << endl;
            cout << "0 - Exit" << endl;

            // read and validate input action
            cout << endl << "Enter your selection: ";
            cin >> action;
            if (action >= 0 && action <= 5) {
                inError = false;
            }

            else {
                // display error message
                cout << endl<< "Invalid input, please try again." << endl;
            }
        }

        cout << endl;
        cout << "SELECTION: " << action << endl;

        // direct termination of program
        if (action == 0) {
            cout << "Program Terminated";
            exit(0);
        }

        // read output file name
        cout << "Enter a name for your output text file:  ";
        string outputFile;
        cin >> outputFile;

        // print lines selection
        if (action == 1) {
            // generate the dictionary object
            Dictionary dictionary(filename);

            // clear stream state to read line numbers
            cout << filename << " has " << dictionary.getInputLines().size() << " lines." << endl;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            cout << "Which lines would you like to print? (Enter each number separated by a space, out of range numbers will be ignored)  " << endl;
            string lines;
            getline(cin, lines);

            dictionary.printLines(lines, outputFile);
        }

        // case for action 2,3,4,5
        else {
            // read separator characters
            cout << "Enter the Separator Characters:  ";
            string delimiters;
            cin >> delimiters;

            // generate the dictionary object
            Dictionary dictionary(filename, delimiters);

            // read selected buckets to print, or read empty line if user hits enter
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Which buckets? (Type Enter to Print All)  ";
            string buckets;
            getline(cin, buckets);

            // if user specifies buckets to print, convert the input string to a set<char>
            set<char> bucketSet;
            if (!buckets.empty()) {
                bucketSet.insert(buckets.begin(), buckets.end());
            }

            // sort dictionary according to user preference if specified
            if (action == 3) {
                dictionary.sortByWord();
            }
            if (action == 4) {
                dictionary.sortByFrequency();
            }
            if (action == 5) {
                dictionary.sortByLength();
            }

            // print final dictionary
            bucketSet.empty() ? dictionary.print(outputFile) : dictionary.printSelect(bucketSet, outputFile);
        }

        // display confirmation message before next loop iteration
        cout << endl << "Output file generated Successfully!" << endl;
        cout << "Continue?" << endl;
    }
    
    return 0; // 0 means success!
}

#endif