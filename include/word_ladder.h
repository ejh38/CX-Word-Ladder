#ifndef WORD_LADDER_H
#define WORD_LADDER_H

#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

#include "word_finder.h"
#include "word_parser.h"

class WordLadder {
public:
    WordLadder() = default;
    bool initialize(const std::string& wordSetFile, size_t wordLength);
    void calculateWords(const std::string& startWord, const std::string& endWord);

private:
    size_t wordLength_ = 0;
    size_t currentWordLength_ = 0;
    std::string wordFilePath_;
    WordParser wordParser_;
    std::unique_ptr<WordFinder> wordFinder_;

    bool endWordExists(const std::string& endWord) const;
};

#endif // WORD_LADDER_H