#include "word_ladder.h"

#include <algorithm>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: ./wordladder <wordListFilePath> <startWord> <endWord>\n";
        return 1;
    }

    std::string wordListFile = argv[1];
    std::string startWord = WordParser::toUpperCase(argv[2]);
    std::string endWord = WordParser::toUpperCase(argv[3]);

    // Ensure start and end words are of the same length
    size_t wordLength = startWord.length();
    if (endWord.length() != wordLength) {
        std::cerr << "Start and end words must be of the same length.\n";
        return 1;
    }

    WordLadder wl;
    if (!wl.initialize(wordListFile, wordLength)) {
        std::cerr << "Initialization failed.\n";
        return 1;
    }

    // Calculate and display the word ladder
    wl.calculateWords(startWord, endWord);
    return 0;
}