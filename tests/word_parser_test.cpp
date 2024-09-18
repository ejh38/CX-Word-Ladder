#include <gtest/gtest.h>
#include "word_parser.h"
#include <vector>
#include <string>
#include <fstream>
#include <cstdio>

class WordParserTest : public ::testing::Test {
protected:
    WordParser parser;
    std::string tempFileName;

    std::string createTempWordList(const std::vector<std::string>& words) {
        std::string tempFile = "temp_test_word_list.txt";
        std::ofstream outFile(tempFile);
        for (const auto& word : words) {
            outFile << word << "\n";
        }
        outFile.close();
        return tempFile;
    }

    void SetUp() override {
        std::vector<std::string> words = {
            "DAMP",
            "LAMP",
            "LIMP",
            "LIME",
            "LIKE",
            "BARK",
            "BANK",
            "HANK",
            "HANG",
            "HANI"
        };
        tempFileName = createTempWordList(words);
    }

    void TearDown() override {
        std::remove(tempFileName.c_str());
    }
};

TEST_F(WordParserTest, LoadWordsSuccessfully) {
    bool loaded = parser.loadWords(tempFileName, 4);
    EXPECT_TRUE(loaded);
    EXPECT_EQ(parser.getWordSet().size(), 10);
}

TEST_F(WordParserTest, LoadWordsWithDifferentLength) {
    bool loaded = parser.loadWords(tempFileName, 5);
    EXPECT_TRUE(loaded);
    EXPECT_EQ(parser.getWordSet().size(), 0); // No 5-letter words in the list
}

TEST_F(WordParserTest, LoadWordsHandlesFileNotFound) {
    bool loaded = parser.loadWords("non_existent_file.txt", 4);
    EXPECT_FALSE(loaded);
    EXPECT_EQ(parser.getWordSet().size(), 0);
}