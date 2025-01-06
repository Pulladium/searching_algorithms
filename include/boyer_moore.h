#pragma once
#include <string>
#include <vector>
#include <chrono>
#include <spdlog/spdlog.h>

/**
 * @brief Implementation of Boyer-Moore string searching algorithm
 *
 * This class implements the Boyer-Moore string search algorithm, which is considered
 * one of the most efficient string searching algorithms in practice. It uses two
 * main heuristics:
 * 1. Bad Character Rule
 * 2. Good Suffix Rule
 *
 * @note Average case time complexity: O(n/m)
 * @note Worst case time complexity: O(nm)
 * where n is text length and m is pattern length
 */
class BoyerMoore {
public:
    /**
     * @brief Searches for all occurrences of a pattern in text
     *
     * Implements the Boyer-Moore algorithm to find all matches of the pattern
     * in the given text. Uses both bad character and good suffix heuristics
     * for optimal performance.
     *
     * @param text The text to search in
     * @param pattern The pattern to search for
     * @return std::vector<int> Vector containing all starting positions where pattern was found
     * @throws std::invalid_argument If either text or pattern is empty
     *
     * Example:
     * @code
     *     BoyerMoore searcher;
     *     auto positions = searcher.search("ABAAABCDABAAABCD", "ABC");
     * @endcode
     */
    std::vector<int> search(const std::string& text, const std::string& pattern);

    /**
     * @brief Get the execution time of the last search operation
     * @return double Time in milliseconds
     */
    double getLastExecutionTime() const { return lastExecutionTime; }

private:
    static const int NO_OF_CHARS = 256; ///< Size of the character set

    /**
     * @brief Preprocesses pattern for bad character rule
     *
     * Creates a table of the rightmost occurrence of each character in the pattern
     *
     * @param pattern The pattern to preprocess
     * @param badChar Vector to store the bad character rule table
     */
    void badCharHeuristic(const std::string& pattern, std::vector<int>& badChar);

    /**
     * @brief Preprocesses pattern for good suffix rule
     *
     * Creates a table for the good suffix rule which helps in determining
     * the shift distance when a mismatch occurs
     *
     * @param pattern The pattern to preprocess
     * @param goodSuffix Vector to store the good suffix rule table
     */
    void goodSuffixHeuristic(const std::string& pattern, std::vector<int>& goodSuffix);

    double lastExecutionTime = 0.0; ///< Stores the execution time of the last search operation
};
