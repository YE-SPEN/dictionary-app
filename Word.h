// Word.h
// Purpose: Define Word Class member functions

/* ******************************************

 * @authors: Eric Spensieri
 * @version: 2.0
 * @since: May 30, 2023

 ******************************************** */

#ifndef WORD_H
#define WORD_H

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::ostream;

class Word {
    private:
        vector<size_t> lineNumbers;
        int frequency;
        string text;
    public:
        Word() = delete;    
        Word(const string text, size_t lineNum);
        Word(const Word& toCopy);
        Word(Word&& toMove) noexcept;
        ~Word();
        Word& operator=(const Word& rhs);
        Word& operator=(Word&& rhs) noexcept;
        string getText() const;
        void appendNumber(int lineNum);
        int getSize() const;
        int getFrequency() const;
        void print(ostream& os) const;
        const vector<size_t>& getNumList() const;
        bool numListContains(size_t value) const;
        int compare(const Word& otherWord) const;
};

#endif
