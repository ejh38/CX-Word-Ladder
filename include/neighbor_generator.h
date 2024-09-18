#ifndef NEIGHBOR_GENERATOR_H
#define NEIGHBOR_GENERATOR_H

#include <string>
#include <vector>
#include <unordered_set>

class NeighborGenerator {
public:
    NeighborGenerator(const std::unordered_set<std::string>& wordSet);
    std::vector<std::string> generateNeighbors(const std::string& word) const;

private:
    const std::unordered_set<std::string>& wordSet_;
};

#endif // NEIGHBOR_GENERATOR_H