#include <gtest/gtest.h>
#include "neighbor_generator.h"
#include <unordered_set>
#include <string>
#include <vector>
#include <algorithm>

class NeighborGeneratorTest : public ::testing::Test {
protected:
    std::unordered_set<std::string> wordSet = {
        "DAMP", "LAMP", "LIMP", "LIME", "LIKE", "BARK", "BANK", "HANK", "HANG", "HANI", "DOG"
    };
    NeighborGenerator generator{wordSet};
};

TEST_F(NeighborGeneratorTest, GenerateNeighborsForExistingWord) {
    std::vector<std::string> expectedNeighbors = {"LAMP"};
    std::vector<std::string> neighbors = generator.generateNeighbors("DAMP");

    EXPECT_EQ(neighbors.size(), expectedNeighbors.size());
    for (const auto& neighbor : expectedNeighbors) {
        EXPECT_NE(std::find(neighbors.begin(), neighbors.end(), neighbor), neighbors.end());
    }
}

TEST_F(NeighborGeneratorTest, GenerateNeighborsForWordWithNoNeighbors) {
    std::vector<std::string> neighbors = generator.generateNeighbors("DOG");
    EXPECT_TRUE(neighbors.empty());
}

TEST_F(NeighborGeneratorTest, GenerateNeighborsNonExistentWord) {
    std::vector<std::string> neighbors = generator.generateNeighbors("XXXX");
    EXPECT_TRUE(neighbors.empty());
}