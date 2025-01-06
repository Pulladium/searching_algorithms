//
// Created by palladusr on 1/6/25.
//

#include "../include/boyer_moore.h"
#include <stdexcept>
#include <algorithm>

std::vector<int> BoyerMoore::search(const std::string& text, const std::string& pattern) {
    std::vector<int> results;

    // Log the start of search operation
    spdlog::debug("Starting Boyer-Moore search for pattern: '{}' in text of length {}",
                  pattern, text.length());

    // Start measuring execution time
    auto start = std::chrono::high_resolution_clock::now();

    // Validate input parameters
    if (pattern.empty() || text.empty()) {
        spdlog::warn("Empty pattern or text provided");
        throw std::invalid_argument("Pattern and text must not be empty");
    }

    int n = text.length();
    int m = pattern.length();

    // Check if pattern is longer than text
    if (m > n) {
        spdlog::debug("Pattern length {} is greater than text length {}", m, n);
        return results;
    }

    // Initialize preprocessing tables
    std::vector<int> badChar(NO_OF_CHARS, -1);
    std::vector<int> goodSuffix(m);

    // Preprocess pattern for both heuristics
    spdlog::debug("Preprocessing pattern for bad character rule");
    badCharHeuristic(pattern, badChar);

    spdlog::debug("Preprocessing pattern for good suffix rule");
    goodSuffixHeuristic(pattern, goodSuffix);

    // Main search loop
    int s = 0; // Current shift of the pattern
    while (s <= n - m) {
        int j = m - 1; // Start matching from the rightmost character

        // Match characters from right to left
        while (j >= 0 && pattern[j] == text[s + j]) {
            j--;
        }

        if (j < 0) {
            // Pattern found - complete match
            spdlog::debug("Pattern found at position: {}", s);
            results.push_back(s);

            // Calculate shift for the next position
            s += (s + m < n) ? m - badChar[text[s + m]] : 1;
        }
        else {
            // Mismatch occurred - calculate shift using both heuristics
            int badCharShift = j - badChar[text[s + j]];
            int goodSuffixShift = goodSuffix[j];

            // Take the maximum of both shifts
            s += std::max(badCharShift, goodSuffixShift);
        }
    }

    // Calculate and store execution time
    auto end = std::chrono::high_resolution_clock::now();
    lastExecutionTime = std::chrono::duration<double, std::milli>(end - start).count();

    spdlog::info("Search completed. Found {} matches in {} ms",
                 results.size(), lastExecutionTime);

    return results;
}

void BoyerMoore::badCharHeuristic(const std::string& pattern, std::vector<int>& badChar) {
    int m = pattern.length();

    // Initialize all occurrences as -1
    for (int i = 0; i < NO_OF_CHARS; i++) {
        badChar[i] = -1;
    }

    // Fill the actual last occurrence positions of characters
    for (int i = 0; i < m; i++) {
        badChar[(int)pattern[i]] = i;
    }

    spdlog::debug("Bad character rule preprocessing completed");
}

void BoyerMoore::goodSuffixHeuristic(const std::string& pattern, std::vector<int>& goodSuffix) {
    int m = pattern.length();
    std::vector<int> suffix(m);

    // Initialize the suffix array
    suffix[m - 1] = m;
    int g = m - 1;
    int f = m - 1;

    // Compute suffix lengths
    for (int i = m - 2; i >= 0; --i) {
        if (i > g && suffix[i + m - 1 - f] < i - g) {
            // Case 1: Use previously computed suffix lengths
            suffix[i] = suffix[i + m - 1 - f];
        }
        else {
            // Case 2: Need to compute suffix length explicitly
            if (i < g) {
                g = i;
            }
            f = i;
            while (g >= 0 && pattern[g] == pattern[g + m - 1 - f]) {
                --g;
            }
            suffix[i] = f - g;
        }
    }

    // Initialize good suffix table
    for (int i = 0; i < m; ++i) {
        goodSuffix[i] = m;
    }

    // Fill the good suffix table using suffix array
    int j = 0;
    for (int i = m - 1; i >= 0; --i) {
        if (suffix[i] == i + 1) {
            // Case 1: The substring matches a prefix of pattern
            for (; j < m - 1 - i; ++j) {
                if (goodSuffix[j] == m) {
                    goodSuffix[j] = m - 1 - i;
                }
            }
        }
    }

    // Fill the remaining cases
    for (int i = 0; i <= m - 2; ++i) {
        goodSuffix[m - 1 - suffix[i]] = m - 1 - i;
    }

    spdlog::debug("Good suffix rule preprocessing completed");
}
