#include "word_finder.h"

#include <queue>
#include <unordered_map>

WordFinder::WordFinder(const std::unordered_set<std::string>& wordSet, NeighborGenerator* neighborGenerator)
    : wordSet_(wordSet), neighborGenerator_(neighborGenerator) {}

// Finds the word ladder from startWord to endWord using BFS
std::vector<std::string> WordFinder::findWordsBFS(const std::string& startWord, const std::string& endWord) const {
    if (startWord.compare(endWord) == 0) {
        return {startWord};
    }
    
    std::unordered_set<std::string> visited;
    std::queue<std::vector<std::string>> paths;

    paths.push({startWord});
    visited.insert(startWord);

    while (!paths.empty()) {
        size_t level_size = paths.size();
        std::unordered_set<std::string> currentLevelVisited;

        // Iterate through all paths at the current BFS level
        for (size_t i = 0; i < level_size; ++i) {
            auto path = paths.front();
            paths.pop();
            std::string last_word = path.back();

            // Generate neighbors of the last word in the current path
            auto neighbors = neighborGenerator_->generateNeighbors(last_word);
            for (const auto& neighbor : neighbors) {
                if (neighbor.compare(endWord) == 0) {
                    path.push_back(neighbor);
                    return path;
                }
                if (!visited.count(neighbor)) {
                    currentLevelVisited.insert(neighbor);
                    auto newPath = path;
                    newPath.push_back(neighbor);
                    paths.push(newPath);
                }
            }
        }

        for (const auto& word : currentLevelVisited) {
            visited.insert(word);
        }
    }
    // No word ladder found
    return {};
}