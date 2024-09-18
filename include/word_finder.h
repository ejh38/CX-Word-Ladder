// include/word_finder.h
#ifndef WORD_FINDER_H
#define WORD_FINDER_H

#include <string>
#include <unordered_set>
#include <vector>

#include "neighbor_generator.h"

class WordFinder {
public:
    WordFinder(const std::unordered_set<std::string>& wordSet, NeighborGenerator* neighborGenerator);
    std::vector<std::string> findWordsBFS(const std::string& startWord, const std::string& endWord) const;

private:
    const std::unordered_set<std::string>& wordSet_;
    NeighborGenerator* neighborGenerator_;
};

#endif // WORD_FINDER_H