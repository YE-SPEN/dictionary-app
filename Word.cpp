// Word.cpp
// Purpose: Implement Word Class

/* ******************************************
 * Authors: Eric Spensieri
 * Version: 2.0
 * Since: May 30, 2023
 ******************************************** */

#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <string>
#include <vector>
#include "Word.h"

using std::string;
using std::vector;
using std::ostream;
using std::find;

// Default constructor
Word::Word(const string word, size_t lineNum) : text(word), lineNumbers(), frequency(1) {
    lineNumbers.push_back(lineNum);
}

// Copy constructor
Word::Word(const Word& toCopy) : text(toCopy.text), lineNumbers(toCopy.lineNumbers), frequency(toCopy.frequency) {}

// Move constructor
Word::Word(Word&& toMove) noexcept : text(std::move(toMove.text)), lineNumbers(std::move(toMove.lineNumbers)), frequency(toMove.frequency) {}

// Copy assignment operator
Word& Word::operator=(const Word& rhs) {
    if (this != &rhs) {
        text = rhs.text;
        frequency = rhs.frequency;
        lineNumbers = rhs.lineNumbers;
    }
    return *this;
}

// Move assignment operator
Word& Word::operator=(Word&& rhs) noexcept {
    if (this != &rhs) {
        text = std::move(rhs.text);
        frequency = rhs.frequency;
        lineNumbers = std::move(rhs.lineNumbers);
    }
    return *this;
}

// Destructor
Word::~Word() {}

// Get the word text
string Word::getText() const {
    return text;
}

// Get the size (length) of the word
int Word::getSize() const {
    return text.length();
}

// Get the frequency of the word
int Word::getFrequency() const {
    return frequency;
}

// Get the associated NumList object for the Word
const vector<size_t>& Word::getNumList() const {
    return lineNumbers;
}

// Check if the Numlist contains a specific value
bool Word::numListContains(size_t value) const {
    for (size_t num : lineNumbers) {
        if (num == value) {
            return true;
        }
    }
    return false;
}

// Append a line number to the NumList and increment the frequency
void Word::appendNumber(int lineNum) {
    if (!numListContains(lineNum)) {
        lineNumbers.push_back(lineNum);
    }
    frequency++;
}

// Print the word, frequency, and associated line numbers
void Word::print(std::ostream& os) const {
    os << std::right << std::setw(15) << text << " -> ";
    os << "(" << frequency << ") ";
    
    for (int line : lineNumbers) {
        os << line;
        if (line != lineNumbers.back()) {
            os << ", ";
        }
    }
}

// Compare two words lexicographically
int Word::compare(const Word& otherWord) const {
    if (text < otherWord.text) {
        return -1;
    }
    else if (text > otherWord.text) {
        return 1;
    }
    return 0;
}
