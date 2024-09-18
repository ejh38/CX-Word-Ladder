#include <gtest/gtest.h>
#include "word_ladder.h"
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <sstream>

class WordLadderTest : public ::testing::Test {
protected:
    WordLadder wl;
    std::string tempFileName;

    // Helper function to create a temporary word list file
    std::string createTempWordList(const std::vector<std::string>& words) {
        std::string tempFile = "temp_test_word_list.txt";
        std::ofstream outFile(tempFile);
        for (const auto& word : words) {
            outFile << word << "\n";
        }
        outFile.close();
        return tempFile;
    }

    // Setup runs before each test to be sure we have correct settings
    void SetUp() override {
        std::vector<std::string> words = {
            "DAMP", "LAMP", "LIMP", "LIME", "LIKE",
            "BARK", "BANK", "HANK", "HANG", "HANI"
        };
        tempFileName = createTempWordList(words);
        wl.initialize(tempFileName, 4);
    }

    void TearDown() override {
        std::remove(tempFileName.c_str());
    }

    // Helper function to capture the output of calculateWords
    std::string captureOutput(const std::string& startWord, const std::string& endWord) {
        std::stringstream buffer;
        std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());
        
        wl.calculateWords(startWord, endWord);
        
        std::cout.rdbuf(oldCout);
        return buffer.str();
    }
};

TEST_F(WordLadderTest, CalculateWordsFindsCorrectPath) {
    std::string output = captureOutput("DAMP", "LIKE");
    std::string expectedOutput = "Word Ladder: DAMP -> LAMP -> LIMP -> LIME -> LIKE\n";
    EXPECT_EQ(output, expectedOutput);
}

TEST_F(WordLadderTest, CalculateWordsReturnsNoPathWhenNoPathExists) {
    std::string output = captureOutput("BARK", "LIKE");
    std::string expectedOutput = "No word ladder was found based on input.\n";
    EXPECT_EQ(output, expectedOutput);
}

TEST_F(WordLadderTest, InitializeWithDifferentWordLength) {
    std::string output = captureOutput("DAMP", "LIKE");
    EXPECT_FALSE(output.empty());

    // Create a new word list with 5-letter words
    std::vector<std::string> newWords = {"HELLO", "HOUSE", "HONEY"};
    std::string newTempFile = createTempWordList(newWords);

    bool reInitialized = wl.initialize(newTempFile, 5);
    EXPECT_TRUE(reInitialized);
    
    output = captureOutput("HELLO", "HONEY");
    std::string expectedOutput = "No word ladder was found based on input.\n";
    EXPECT_EQ(output, expectedOutput);

    std::remove(newTempFile.c_str());
}

TEST_F(WordLadderTest, CalculateWordsOutput) {
    std::string output = captureOutput("DAMP", "LIKE");
    std::string expectedOutput = "Word Ladder: DAMP -> LAMP -> LIMP -> LIME -> LIKE\n";
    EXPECT_EQ(output, expectedOutput);
}