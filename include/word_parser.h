#ifndef WORD_PARSER_H
#define WORD_PARSER_H

#include <string>
#include <vector>
#include <unordered_set>

class WordParser {
public:
    WordParser() = default;
    bool loadWords(const std::string& filePath, size_t wordLength);
    const std::unordered_set<std::string>& getWordSet() const;
    static std::string toUpperCase(const std::string& str);
private:
    std::unordered_set<std::string> wordSet_;
};

#endif // WORD_PARSER_H