COMP5421 Assignment #2
Submitted by: Eric Spensieri (ID #26997252)
==================

The Dictionary project is a program that reads a text file containing words and line numbers, processes the data, and provides an outfile containing an index-like interface to search for words and retrieve their associated line numbers. The DictionaryApp also includes an in-terminal menu structure enabling users to customize their output to exclude word buckets, input lines, or delimiting characters as needed.


Features
========

The below functionalities are carried over from Assignment #1, now implemented using standard C++ data container types.

1.	Reads a text file containing words and line numbers.
2.	Builds an efficient data structure to store the words and line numbers.
3.	Provides functionality to search for words and retrieve their line numbers.
4.	Handles duplicate words by appending line numbers to the existing word entry.
5.	Handles duplicate words on the same line by recording each instance of the sord without duplicating line numbers
6.	Outputs the dictionary to a text file for easy viewing.

In addition to these, the updated DictionaryApp executable supports the following actions:

7.	Ability to print all or individual lines from the input file as selected by the user.
8.	Ability to display only individual word buckets within the dictionary object as selected by the user.
9.	Ability to sort words in the output dictionary index either by string length, frequency of occurence, lexicographically, or in order of their first appearance in the input file (default).
10.	Ability to specify delimiting characters by which words are split in the input file in addition to the standard white-space characters.


Requirements
============

To run the Dictionary project, you need:

C++ compiler that supports C++11 or higher.
Text file containing words and line numbers.


Usage
=====

Run the project from your chosen IDE, ensuring to have all header and implementation files, the DictionaryApp.cpp executable, and your input text file in the same directory. 

Build and compile the project, and input the title of your input text file when prompted, including the file extension .txt.
Next, select a name for your output file excluding the file extension.

Follow the instructions in the program to select your desired action(s), specify the desired delimiting characters (if applicable) and specify the lines or word buckets to include in your output.


File Structure
==============

The Dictionary project consists of the following files:

Word.h: 		Header file for the Word class.
Word.cpp: 		Implementation of the Word class.
Dictionary.h: 		Header file for the Dictionary class.
Dictionary.cpp: 	Implementation of the Dictionary class.
DictionaryApp.cpp: 	Main program execution file with menu interface to facilitate dictionary generation.
Seuss.txt:	 	Sample input file containing words and line numbers.

