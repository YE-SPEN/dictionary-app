// Dictionary.cpp
// Purpose: Implement Dictionary Class

/* ******************************************
 * @authors: Eric Spensieri
 * @version: 2.0
 * @since: May 31, 2023
 ******************************************** */

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <array>
#include <vector>
#include <set>
#include <forward_list>
#include "Dictionary.h"

using std::string;
using std::forward_list;
using std::vector;
using std::ostream;
using std::array;
using std::list;
using std::cout;
using std::endl;

// free function to compare words by text
bool comesBefore(const Word& w1, const Word& w2) {
    return w1.compare(w2) < 0;
}

// free function to compare words by string length
bool isShorter(const Word& w1, const Word& w2) {
    if (w1.getText().length() < w2.getText().length()) return true;
    if (w1.getText().length() > w2.getText().length()) return false;
    return w1.compare(w2) < 0;
}

// free function to compare words by frequency
bool lessFrequent(const Word& w1, const Word& w2) {
    if (w1.getFrequency() < w2.getFrequency()) return true;
    if (w1.getFrequency() > w2.getFrequency()) return false;
    return w1.compare(w2) < 0;
}

// free function for deduplicating forward_list objects
bool inFlist(const forward_list<int>& list, int value) {
    for (int num : list) {
        if (num == value) {
            return true;
        }
    }
    return false;
}

// Constructor
Dictionary::Dictionary(const string& filename, const string& delimiterSet) : filename(filename), delimiters(delimiterSet + " \t\n") {
    sortType = "in order of appearance.";
    std::ifstream fin(filename); // create an input file streamer;
    
    if (!fin) {
        cout << "could not open input file: " << filename << endl;
        exit(1);
    }
    
    int linenum = 0;
    string line;
    getline(fin, line);
    
    while (fin) {
        inputLines.push_back(line); // record the line string to the inputLines vector
        ++linenum; // count the line
        
        string token;
        size_t startIndex = line.find_first_not_of(delimiters);
        
        while (startIndex != std::string::npos) { // extract word tokens
            size_t endIndex = line.find_first_of(delimiters, startIndex + 1);

            if (endIndex == std::string::npos) {
                endIndex = line.length();
            }

            // add found token to the dictionary
            token = line.substr(startIndex, endIndex - startIndex);
            processWord(token, linenum);

            // shift the startIndex for next loop iteration
            startIndex = line.find_first_not_of(delimiters, endIndex + 1);
        }
        
        getline(fin, line); // attempt to read the next line, if any
    }
    
    fin.close();
}

vector<string> Dictionary::getInputLines() const {
    return inputLines;
}

bool Dictionary::checkDupe(const Word& newWord, list<Word>& wordList) {
    int index = lookup(newWord.getText());

    if (index != -1) {
        auto it = wordList.begin();
        std::advance(it, index);
        Word& existingWord = *it;
        existingWord.appendNumber(newWord.getNumList()[0]);
        return true;
    }
    return false;
}

// Lookup a specific word in the WordList and return the corresponding WordNode
int Dictionary::lookup(const string& toFind) const {
    
    // determine which bucket to search
    size_t bucket = bucketIndex(toFind);
    const list<Word>& searchList = wordBuckets[bucket];

    int index = 0;
    for (const Word& currentWord : searchList) {
        if (currentWord.getText() == toFind) {
            return index;
        }
        index++;
    }
    return -1;
}

// Calculate the bucket index for a given word
size_t Dictionary::bucketIndex(const string& word) const {
    size_t index = 26; // bucket index for words not beginning with a letter
    if (isalpha(word[0])) {
        if (isupper(word[0])) {
            index = word[0] - 'A';
        }
        else {
            index = word[0] - 'a';
        }
    }
    return index;
}

// Process a word by adding it to the appropriate WordList in the dictionary
void Dictionary::processWord(const string& word, int lineNum) {
    // Check if the word is empty
    if (word.empty()) {
        return;
    }

    // Determine the index of the WordList bucket
    size_t index = bucketIndex(word);

    // verify the word is not already in dictionary before insertion
    Word newWord(word, lineNum);
    if (!checkDupe(newWord, wordBuckets[index])) {
        wordBuckets[index].push_back(newWord);
    }
}

void Dictionary::sortByWord() {
    sortType = "Lexicographically";
    forward_list<Word> sortedList;

    // iterate over each word bucket
    for (list<Word>& bucket : wordBuckets) {
        while (!bucket.empty()) {
            sortedList.push_front(bucket.front());  // move bucket items into a forward list
            bucket.pop_front();
        }
        sortedList.sort(comesBefore);  // perform sort operation based on lexicographic order

        bucket = list<Word>(sortedList.begin(), sortedList.end());  // reallocate sortedList to the original bucket
        sortedList.clear();
    }
}

void Dictionary::sortByLength() {
    sortType = "by String Length";
    forward_list<Word> sortedList;

    // iterate over each word bucket
    for (list<Word>& bucket : wordBuckets) {
        while (!bucket.empty()) {
            sortedList.push_front(bucket.front());  // move bucket items into a forward list
            bucket.pop_front();
        }
        sortedList.sort(isShorter);  // perform sort operation based on string length

        bucket = list<Word>(sortedList.begin(), sortedList.end());  // reallocate sortedList to the original bucket
        sortedList.clear();
    }
}

// sort dictionary buckets by frequency of occurrence
void Dictionary::sortByFrequency() {
    sortType = "by Frequency";
    forward_list<Word> sortedList;

    // iterate over each word bucket
    for (list<Word>& bucket : wordBuckets) {
        while (!bucket.empty()) {
            sortedList.push_front(bucket.front());  // move bucket items into a forward list
            bucket.pop_front();
        }
        sortedList.sort(lessFrequent);  // perform sort operation based on frequency

        bucket = list<Word>(sortedList.begin(), sortedList.end());  // reallocate sortedList to the original bucket
        sortedList.clear();
    }
}

// Print the dictionary to the output stream
void Dictionary::print(string outputFileName) const {
    string output = outputFileName + ".txt";
    std::ofstream outputFile(output); // Create an output file stream

    if (!outputFile) {
        std::cout << "Could not open output file." << std::endl;
        return;
    }
    
    // initialize bucket label array
    int index = 0;
    char label[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                   'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '-'};

    outputFile << "Dictionary Index for: " << filename << endl;
    outputFile << "Word Lists Sorted " << sortType << endl;
    outputFile << "Using as Delimiting Characters: " << delimiters << endl;

    // print individual WordList elements
    while (index <= 26) {
        outputFile << "\n";
        outputFile << "<"; outputFile << label[index]; outputFile << ">" << "\n";
        outputFile << "\n";

        list<Word> currentList = wordBuckets[index];     
        for (Word currentWord : currentList) {
            currentWord.print(outputFile);
            outputFile << "\n";
        }
        index++;
    }

    // close output stream
    outputFile.close();
}

// Print the dictionary to the output stream with a specific set of buckets to print
void Dictionary::printSelect(const set<char> charSet, string outputFileName) const {
    string output = outputFileName + ".txt";
    std::ofstream outputFile(output); // Create an output file stream

    if (!outputFile) {
        std::cout << "Could not open output file." << std::endl;
        return;
    }

    // initialize bucket label array
    char label[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                   'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '-' };

    // read char set and retrieve associated buckets to be printed
    forward_list<int> bucketsToPrint; 
    for (char letter : charSet) {
        string str(1, letter);
        int nextIndex = bucketIndex(str);
        bucketsToPrint.push_front(nextIndex);
    }

    // sort the forward list containing the bucket indices
    bucketsToPrint.sort();

    outputFile << "Dictionary Index for: " << filename << endl;
    outputFile << "Word lists Sorted " << sortType << endl;
    outputFile << "Using as Delimiting Characters: " << delimiters << endl;

    // print individual WordList elements
    for (int index : bucketsToPrint) {
        outputFile << "\n";
        outputFile << "<"; outputFile << label[index]; outputFile << ">" << "\n";
        outputFile << "\n";

        list<Word> currentList = wordBuckets[index];
        for (Word currentWord : currentList) {
            currentWord.print(outputFile);
            outputFile << "\n";
        }
        index++;
    }

    // close output stream
    outputFile.close();
}

void Dictionary::printLines(const string& linesStr, string outputFileName) const {
    string output = outputFileName + ".txt";
    std::ofstream outputFile(output); // Create an output file stream

    if (!outputFile) {
        std::cout << "Could not open output file." << std::endl;
        return;
    }

    int range = inputLines.size();     // set line range to the size of the inputLines member vector
    forward_list<int> linesToPrint;    // vector storing line numbers to be printed

    // if no lines specified, print all
    if (linesStr.empty()) {
        for (int i = 1; i <= range; i++) {
            linesToPrint.push_front(i);
        }
    }

    else {
        std::istringstream sin(linesStr); // turn the line into an input string stream
        int nextLine;

        // continue reading until string is complete
        while (sin) {
            // check if next input is a valid integer within range or has already been read
            if (sin >> nextLine) {
                if (nextLine > 0 && nextLine <= range) {
                    if (!inFlist(linesToPrint, nextLine)) {
                        linesToPrint.push_front(nextLine);   // add valid input lines to the list to be printed
                    }
                }
            }
            else {
                sin.clear(); // If invalid token is read, clear the fail state
                string invalidToken;
                sin >> invalidToken; // Extract the invalid token and discard it
            }
        }
    }

    outputFile << "Selected Input Lines from: " << filename;
    outputFile << "\n\n";

    // sort the forward list
    linesToPrint.sort();

    // print individual Input Line elements
    for (int line : linesToPrint) {
        outputFile << "Line #" << line << ":\t";
        outputFile << inputLines[line - 1] << "\n";
    }

    // close output stream
    outputFile.close();
}

