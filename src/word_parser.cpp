#include "word_parser.h"
#include <fstream>
#include <algorithm>
#include <cctype>
#include <iostream>

// Loads words from a file, filtering by the specified word length
bool WordParser::loadWords(const std::string& filePath, size_t wordLength) {
    std::ifstream wordFile(filePath);
    if (!wordFile.is_open()) {
        std::cerr << "Error opening file: " << filePath << '\n';
        return false;
    }

    // Clear existing set before loading new words
    wordSet_.clear();

    std::string word;
    while (wordFile >> word) {
        // Need to normalize input to make sure comparisons work
        if (word.length() == wordLength) {
            toUpperCase(word);
            wordSet_.insert(word);
        }
    }

    wordFile.close();
    std::cout << "WordParser loaded " << wordSet_.size() 
              << " words of length " << wordLength << ".\n";
    return true;
}

const std::unordered_set<std::string>& WordParser::getWordSet() const {
    return wordSet_;
}

static std::string toUpperCase(const std::string& str) {
    std::string upperStr = str;
    std::transform(upperStr.begin(), upperStr.end(), upperStr.begin(),
                   [](unsigned char c) { return std::toupper(c); });
    return upperStr;
}