#pragma once
#include <string>
#include <vector>
#include <chrono>
#include <spdlog/spdlog.h>




/**
 * @brief Implementation of Brute Force string search algorithm
 *
 * This class provides a simple but reliable string searching implementation
 * using the brute force approach.
 */
class BruteForceSearch {
public:
    /**
     * @brief Searches for all occurrences of a pattern in text
     *
     * Performs a character by character comparison at each possible position
     * in the text to find all matches of the pattern.
     *
     * @param text The text to search in
     * @param pattern The pattern to search for
     * @return std::vector<int> Vector containing all starting positions where pattern was found
     * @throws std::invalid_argument If either text or pattern is empty
     *
     * @note Time complexity: O(n*m) where n is text length and m is pattern length
     *
     * Example:
     * @code
     *     BruteForceSearch searcher;
     *     auto positions = searcher.search("AABAACAADAABAAABAA", "AABA");
     * @endcode
     */
    std::vector<int> search(const std::string& text, const std::string& pattern);

    /**
     * @brief Get the execution time of the last search operation
     * @return double Time in milliseconds
     */
    double getLastExecutionTime() const { return lastExecutionTime; }

private:
    double lastExecutionTime = 0.0; ///< Stores the execution time of the last search operation
};
