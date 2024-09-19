#include "word_ladder.h"

#include <iostream>
#include <algorithm>

// Initializes the WordLadder with the given word list file and word length
bool WordLadder::initialize(const std::string& wordSetFile, size_t wordLength) {
    if (wordLength != currentWordLength_) {
        currentWordLength_ = wordLength;
        wordLength_ = wordLength;

        bool loaded = wordParser_.loadWords(wordSetFile, wordLength_);
        if (!loaded) {
            return false;
        }

        wordFinder_ = std::make_unique<WordFinder>(wordParser_.getWordSet(), std::make_unique<NeighborGenerator>(wordParser_.getWordSet()));
        wordFilePath_ = wordSetFile;
    }

    return true;
}

// Calculates and displays the word ladder from startWord to endWord
void WordLadder::calculateWords(const std::string& startWord, const std::string& endWord) {
    const std::string upperStart { WordParser::toUpperCase(startWord) };
    const std::string upperEnd = { WordParser::toUpperCase(endWord)   };

    if (!endWordExists(upperEnd)) {
        std::cout << "End word does not exist in the word list.\n";
        return;
    }

    auto wordLadder = wordFinder_->findWordsBFS(upperStart, upperEnd);

    if (!wordLadder.empty()) {
        std::cout << "Word Ladder: ";
        for (const auto& word : wordLadder) {
            std::cout << word;
            if (word != wordLadder.back()) {
                std::cout << " -> ";
            }
        }
        std::cout << '\n';
    } else {
        std::cout << "No word ladder was found based on input.\n";
    }
}

// Checks if the end word exists in the loaded word set.
// This should avoid unecessary computations
bool WordLadder::endWordExists(const std::string& endWord) const {
    const auto& wordSet = wordParser_.getWordSet();
    return wordSet.find(endWord) != wordSet.end();
}