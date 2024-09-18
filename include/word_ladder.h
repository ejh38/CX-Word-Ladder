#ifndef WORD_LADDER_H
#define WORD_LADDER_H

#include <memory>
#include <string>
#include <vector>
#include <unordered_set>

#include "neighbor_generator.h"
#include "word_finder.h"
#include "word_parser.h"

class WordLadder {
public:
    WordLadder();
    ~WordLadder();
    bool initialize(const std::string& wordSetFile, size_t wordLength);
    void calculateWords(const std::string& startWord, const std::string& endWord);

private:
    size_t wordLength_;
    std::string wordFilePath_;
    WordParser wordParser_;
    std::unique_ptr<NeighborGenerator> neighborGenerator_;
    std::unique_ptr<WordFinder> wordFinder_;
    size_t currentWordLength_;

    bool endWordExists(const std::string& endWord) const;
};

#endif // WORD_LADDER_H