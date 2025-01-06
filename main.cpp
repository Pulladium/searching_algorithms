#include <brute_force.h>
#include <boyer_moore.h>
#include <iostream>
#include <string>
#include <vector>
#include <spdlog/spdlog.h>


int main() {
    spdlog::set_level(spdlog::level::debug);
    spdlog::info("Starting string search program");

    try {
        std::string text = "ABAAABCDABAAABCD";
        std::string pattern = "ABC";

        spdlog::info("Searching for pattern '{}' in text '{}'", pattern, text);

        // Brute Force search
        BruteForceSearch bf;
        std::vector<int> bf_positions = bf.search(text, pattern);

        // Boyer-Moore search
        BoyerMoore bm;
        std::vector<int> bm_positions = bm.search(text, pattern);

        std::cout << "Pattern found at positions: ";
        for (int pos : bf_positions) {
            std::cout << pos << " ";
        }
        for (int pos : bm_positions) {
            std::cout << pos << " ";
        }

        std::cout << "\nBF Execution time: " << bf.getLastExecutionTime() << " ms\n";
        std::cout << "\nBM Execution time: " << bm.getLastExecutionTime() << " ms\n";

    } catch (const std::exception& e) {
        spdlog::error("Error occurred: {}", e.what());
        return 1;
    }

    return 0;
}
