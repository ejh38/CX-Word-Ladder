#include "neighbor_generator.h"

NeighborGenerator::NeighborGenerator(const std::unordered_set<std::string>& wordSet)
    : wordSet_(wordSet) {}

// Generates all valid neighboring words by changing one letter at a time
std::vector<std::string> NeighborGenerator::generateNeighbors(const std::string& word) const {
    std::vector<std::string> neighbors;
    std::string temp = word;

    for (size_t i = 0; i < temp.size(); ++i) {
        char original_char = temp[i];
        for (char c = 'A'; c <= 'Z'; ++c) {
            if (c == original_char) continue;
            temp[i] = c;
            if (wordSet_.find(temp) != wordSet_.end()) {
                neighbors.push_back(temp);
            }
        }
        temp[i] = original_char; // Restore original character
    }

    return neighbors;
}