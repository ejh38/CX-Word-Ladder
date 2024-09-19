#include "word_finder.h"

#include <algorithm>
#include <iostream>

WordFinder::WordFinder(const std::unordered_set<std::string>& wordSet, std::unique_ptr<NeighborGenerator> neighborGenerator)
    : wordSet_(wordSet), neighborGenerator_(std::move(neighborGenerator)) {}

bool WordFinder::expandBFS(std::queue<std::string>& paths,
                           std::unordered_map<std::string, std::string>& parents,
                           std::unordered_map<std::string, bool>& visited,
                           const std::unordered_map<std::string, bool>& otherVisited,
                           std::string& connection) const 
{
    auto currentLevelSize = paths.size();
    for (auto i = 0; i < currentLevelSize; ++i) {
        auto currentWord = paths.front();
        paths.pop();

        // Generate all valid neighbors.
        auto neighbors = neighborGenerator_->generateNeighbors(currentWord);
        for (const auto& neighbor : neighbors) {
            if (!visited[neighbor]) {
                parents[neighbor] = currentWord;
                visited[neighbor] = true;
                paths.push(neighbor);

                // Check if the neighbor has been visited from the other side.
                if (otherVisited.find(neighbor) != otherVisited.end()) {
                    connection = neighbor;
                    return true;
                }
            }
        }
    }
    return false;
}

std::vector<std::string> WordFinder::traverseParents(
    const std::unordered_map<std::string, std::string>& parents,
    const std::string& word) const
{
    std::vector<std::string> path;
    std::string currentWord = word;

    while (!currentWord.empty()) {
        path.push_back(currentWord);
        auto it = parents.find(currentWord);
        if (it != parents.end()) {
            currentWord = it->second;
        } else {
            currentWord = "";
        }
    }

    return path;
}


// We need to reconstruct the paths after getting both halves.
std::vector<std::string> WordFinder::reconstructPath(
    const std::string& meetingWord,
    const std::unordered_map<std::string, std::string>& parentsStart,
    const std::unordered_map<std::string, std::string>& parentsEnd) const
{
    // Traverse from our meetingWord back to the startWord.
    std::vector<std::string> pathStart = traverseParents(parentsStart, meetingWord);
    // Need to reverse to get correct order for path.
    std::reverse(pathStart.begin(), pathStart.end());

    // Traverse from our meetingWord back to the endWord.
    std::vector<std::string> pathEnd = traverseParents(parentsEnd, meetingWord);

    // Merge the paths leaving out meetingWord dup.
    if (!pathEnd.empty()) {
        pathEnd.erase(pathEnd.begin());
    }

    pathStart.insert(pathStart.end(), pathEnd.begin(), pathEnd.end());
    return pathStart;
}


std::vector<std::string> WordFinder::findWordsBFS(const std::string& startWord, const std::string& endWord) const {
    if (startWord.compare(endWord) == 0) {
        return {startWord};
    }

    // Initialize everything for bi-directional bfs
    std::queue<std::string> queueStart;
    std::queue<std::string> queueEnd;
    queueStart.push(startWord);
    queueEnd.push(endWord);

    std::unordered_map<std::string, bool> visitedStart;
    std::unordered_map<std::string, bool> visitedEnd;
    visitedStart[startWord] = true;
    visitedEnd[endWord] = true;

    std::unordered_map<std::string, std::string> parentsStart;
    std::unordered_map<std::string, std::string> parentsEnd;
    parentsStart[startWord] = "";
    parentsEnd[endWord] = "";

    std::string connection = "";

    // Perform BFS from both ends (bi-directional bfs)
    while (!queueStart.empty() && !queueEnd.empty()) {
        // Go from start word side.
        if (expandBFS(queueStart, parentsStart, visitedStart, visitedEnd, connection)) {
            break;
        }

        // Go from end word side.
        if (expandBFS(queueEnd, parentsEnd, visitedEnd, visitedStart, connection)) {
            break;
        }
    }

    if (connection.empty()) {
        // No connection found
        return {};
    }

    auto path = reconstructPath(connection, parentsStart, parentsEnd);
    return path;
}