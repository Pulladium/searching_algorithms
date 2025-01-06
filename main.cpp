#include <brute_force.h>
#include <iostream>
#include <string>
#include <vector>
#include <spdlog/spdlog.h>


int main() {
    spdlog::set_level(spdlog::level::debug);
    spdlog::info("Starting string search program");

    try {
        BruteForceSearch bf;
        std::string text = "ABAAABCDABAAABCD";
        std::string pattern = "ABC";

        spdlog::info("Searching for pattern '{}' in text '{}'", pattern, text);

        std::vector<int> positions = bf.search(text, pattern);

        std::cout << "Pattern found at positions: ";
        for (int pos : positions) {
            std::cout << pos << " ";
        }
        std::cout << "\nExecution time: " << bf.getLastExecutionTime() << " ms\n";

    } catch (const std::exception& e) {
        spdlog::error("Error occurred: {}", e.what());
        return 1;
    }

    return 0;
}
