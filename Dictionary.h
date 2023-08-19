// Dictionary.h
// Purpose: Define Dictionary Class member functions

/* ******************************************

 * @authors: Eric Spensieri
 * @version: 2.0
 * @since: May 30, 2023

 ******************************************** */

#ifndef DICTIONARY_H_
#define DICTIONARY_H_

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <array>
#include <vector>
#include <set>
#include <forward_list>
#include "Word.h"

using std::string;
using std::forward_list;
using std::set;
using std::vector;
using std::ostream;
using std::array;
using std::list;


class Dictionary {
    private:
        string filename;
        string sortType;
        const string delimiters;    // user-specified delimiter set
        vector<string> inputLines;  // lines in the input file
        array<list<Word>, 27> wordBuckets; // 26 alpha buckets + 1 none-alpha bucket
        size_t bucketIndex(const string& word) const;
    public:
        explicit Dictionary(const string& inputFile, const string& delimiters = " \n\t");
        vector<string> getInputLines() const;
        void processWord(const string& word, int linenum);
        void sortByWord();  // sort dictionary object by word text
        void sortByLength();    // sort dictionary object by string length
        void sortByFrequency(); // sort dictionary object by word frequency
        void print(string outputFileName) const; // default print 
        void printSelect(const set<char> charSet, string outputFileName) const;    // print user specified buckets only
        void printLines(const string& linesStr, string outputFileName) const;  // print user specified lines from input file as string
        bool checkDupe(const Word& word, list<Word>& wordList); // handler for reading words already included in dictionary object
        int lookup(const string& toFind) const; // retrieve index where given word is stored in its bucket
        Dictionary() = delete; // no default ctor
        ~Dictionary() = default; // default dtor
        Dictionary(const Dictionary&) = default; // copy ctor
        Dictionary( Dictionary&&) = default; // move ctor
        Dictionary& operator=(const Dictionary&) = default; // copy assignment
        Dictionary& operator=( Dictionary&&) = default; // move assignment
};

#endif
