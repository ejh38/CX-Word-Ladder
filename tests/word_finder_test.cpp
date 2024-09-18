#include <gtest/gtest.h>
#include <unordered_set>

#include "neighbor_generator.h"
#include "word_finder.h"

class WordFinderTest : public ::testing::Test {
protected:
    std::unordered_set<std::string> wordSet;
    std::unique_ptr<NeighborGenerator> neighborGenerator;
    std::unique_ptr<WordFinder> wordFinder;

    void SetUp() override {
        wordSet = {"DAMP", "LAMP", "LIMP", "LIME", "LIKE", "BARK", "BANK", "HANK", "HANG", "HANI"};
        neighborGenerator = std::make_unique<NeighborGenerator>(wordSet);
        wordFinder = std::make_unique<WordFinder>(wordSet, neighborGenerator.get());
    }
};

TEST_F(WordFinderTest, FindsShortestPath) {
    auto result = wordFinder->findWordsBFS("DAMP", "LIKE");
    std::vector<std::string> expected = {"DAMP", "LAMP", "LIMP", "LIME", "LIKE"};
    EXPECT_EQ(result, expected);
}

TEST_F(WordFinderTest, ReturnsEmptyPathWhenNoPathExists) {
    auto result = wordFinder->findWordsBFS("BARK", "LIKE");
    EXPECT_TRUE(result.empty());
}

TEST_F(WordFinderTest, HandlesStartWordEqualToEndWord) {
    auto result = wordFinder->findWordsBFS("DAMP", "DAMP");
    std::vector<std::string> expected = {"DAMP"};
    EXPECT_EQ(result, expected);
}

TEST_F(WordFinderTest, HandlesNonExistentWords) {
    auto result = wordFinder->findWordsBFS("XXXX", "YYYY");
    EXPECT_TRUE(result.empty());
}