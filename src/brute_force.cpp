//
// Created by palladusr on 1/6/25.
//
#include "../include/brute_force.h"
#include <stdexcept>

std::vector<int> BruteForceSearch::search(const std::string& text, const std::string& pattern) {
    std::vector<int> results;

    spdlog::debug("Starting brute force search for pattern: '{}' in text of length {}",
                  pattern, text.length());

    // Record start time
    auto start = std::chrono::high_resolution_clock::now();

    // Input validation
    if (pattern.empty() || text.empty()) {
        spdlog::warn("Empty pattern or text provided");
        throw std::invalid_argument("Pattern and text must not be empty");
    }

    int n = text.length();
    int m = pattern.length();

    if (m > n) {
        spdlog::debug("Pattern length {} is greater than text length {}", m, n);
        return results;
    }

    // Main search loop
    for (int i = 0; i <= n - m; i++) {
        bool found = true;

        // Check for pattern match at current position
        for (int j = 0; j < m; j++) {
            if (text[i + j] != pattern[j]) {
                found = false;
                break;
            }
        }

        // If pattern found, add position to results
        if (found) {
            spdlog::debug("Pattern found at position: {}", i);
            results.push_back(i);
        }
    }

    // Calculate execution time
    auto end = std::chrono::high_resolution_clock::now();
    lastExecutionTime = std::chrono::duration<double, std::milli>(end - start).count();

    spdlog::info("Search completed. Found {} matches in {} ms",
                 results.size(), lastExecutionTime);

    return results;
}
