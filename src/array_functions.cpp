/*
 * functionstocomplete.cpp
 *
 *  Created on: Sep 10, 2017
 *      Author: keith
 */

//============================================================================
//	TODO add necessary includes here
//============================================================================
#include "array_functions.h"
#include "utilities.h"
#include "cstring"
//============================================================================
//	stuff you will need
//============================================================================
//TODO define a structure to track words and number of times they occur

//TODO add a global array of entry structs (global to this file)

//TODO add variable to keep track of next available slot in array

//TODO define all functions in header file

//TODO look in utilities.h for useful functions, particularly strip_unwanted_chars!

struct words {
    std::string word;
    int count{};
    std::string upper;
};
struct words array[constants::MAX_WORDS];
int size = 0;

void clearArray() {
    size = 0;
}

int getArraySize() {
    return size;
}

std::string getArrayWordAt(int i) {
    return array[i].word;
}

int getArrayWord_NumbOccur_At(int i) {
    return array[i].count;
}
bool openFile(std::fstream &myfile, const std::string &myFileName, std::ios_base::openmode mode) {
    if (!myfile.is_open()) {
        myfile.open(myFileName, mode);
        return myfile.is_open();
    }
    return false;
}
void closeFile(std::fstream &myfile) {
    if (myfile.is_open()) {
        myfile.close();
    }
}
bool processFile(std::fstream &myfstream) {
    std::string line;
    if (myfstream.is_open()) {
        while (getline(myfstream, line)) {
            processLine(line);
        }
        return true;
    }
    return false;
}
void processLine(std::string &myString) {
    std::stringstream ss(myString);
    std::string token;

    while (getline(ss,token, constants::CHAR_TO_SEARCH_FOR)){
        processToken(token);
    }
}
void processToken(std::string &token) {
    strip_unwanted_chars(token);
    std::string uptoken = token;
    toUpper(uptoken);
    if (!uptoken.empty()) {
        bool exist = false;
        for (int i = 0; i < size; i++) {
            if (array[i].upper == uptoken) {
                array[i].count++;
                exist = true;
                }
        }
        if (!exist) {
            array[size].word = token;
            array[size].count = 1;
            array[size].upper = uptoken;
            size++;
        }
    }
}
int writeArraytoFile(const std::string &outputfilename) {
    if (size == 0) {
        return constants::FAIL_NO_ARRAY_DATA;
    }
    std::fstream myfile;
    openFile(myfile,outputfilename,std::ios::out);
    if (myfile.is_open()) {
       for (int i = 0; i < size; i++){
           myfile << array[i].word + " ";
           myfile << array[i].count;
           myfile << "\n";
       }
       closeFile(myfile);
       return constants::SUCCESS;
    }
    return constants::FAIL_FILE_DID_NOT_OPEN;
}

void sortArray(constants::sortOrder so) {
    struct words flip;
    switch (so) {
        case constants::NONE:
            return;
        case constants::ASCENDING:
            for (int i = size - 1; i > 0; i--) {
                for (int j = 0; j < i; j++) {
                    if (array[j].upper > array[j+1].upper) {
                        flip = array[j];
                        array[j] = array[j + 1];
                        array[j + 1] = flip;
                    }
                }
            }
            return;
        case constants::DESCENDING:
            for (int i = size - 1; i > 0; i--) {
                for (int j = 0; j < i; j++) {
                    if (array[j].upper.compare(array[j+1].upper) < 0) {
                        flip = array[j];
                        array[j] = array[j + 1];
                        array[j + 1] = flip;
                    }
                }
            }
            return;
        case constants::NUMBER_OCCURRENCES:
            for (int i = size - 1; i > 0; i--) {
                for (int j = 0; j < i; j++) {
                    if (array[j].count < array[j + 1].count) {
                        flip = array[j];
                        array[j] = array[j + 1];
                        array[j + 1] = flip;
                    }
                }
            }

    }
}
