// include/word_finder.h
#ifndef WORD_FINDER_H
#define WORD_FINDER_H

#include <memory>
#include <queue>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "neighbor_generator.h"

class WordFinder {
public:
    WordFinder(const std::unordered_set<std::string>& wordSet, std::unique_ptr<NeighborGenerator> neighborGenerator);
    std::vector<std::string> findWordsBFS(const std::string& startWord, const std::string& endWord) const;

private:
    const std::unordered_set<std::string>& wordSet_;
    std::unique_ptr<NeighborGenerator> neighborGenerator_;

    bool expandBFS(std::queue<std::string>& paths,
                   std::unordered_map<std::string, std::string>& parents,
                   std::unordered_map<std::string, bool>& visited,
                   const std::unordered_map<std::string, bool>& otherVisited,
                   std::string& connection) const;

    std::vector<std::string> traverseParents(const std::unordered_map<std::string, std::string>& parents,
                                             const std::string& word) const;               

    std::vector<std::string> reconstructPath(const std::string& meetingWord,
                                            const std::unordered_map<std::string, std::string>& parentsStart,
                                            const std::unordered_map<std::string, std::string>& parentsEnd) const;
};

#endif // WORD_FINDER_H