#include "neighbor_generator.h"

#include <algorithm>

NeighborGenerator::NeighborGenerator(const std::unordered_set<std::string>& wordSet)
    : wordSet_(wordSet) {}

// Generates all valid neighboring words by changing one letter at a time
std::vector<std::string> NeighborGenerator::generateNeighbors(const std::string& word) {
    
    // Check if neighbors are already computed to save time.
    auto it = history_.find(word);
    if (it != history_.end()) {
        return it->second;
    }
    
    std::vector<std::string> neighbors;
    std::string temp = word;

    for (size_t i = 0; i < temp.size(); ++i) {
        char originalChar = temp.at(i);
        for (char c = 'A'; c <= 'Z'; ++c) {
            if (c == originalChar) {
                continue;
            }

            temp[i] = c;
            if (wordSet_.count(temp)) {
                neighbors.push_back(temp);
            }
        }
        temp.at(i) = originalChar; // Restore original character
    }

    // Need to sort these to make sure words appear in same order despite wordSet
    std::sort(neighbors.begin(), neighbors.end());

    // Essentially caching the neighbors to avoid recomputing if called again.
    history_[word] = neighbors;

    return neighbors;
}