#include <brute_force.h>
#include <boyer_moore.h>
#include <iostream>
#include <string>
#include <vector>
#include <spdlog/spdlog.h>
#include <fstream>



void printUsage() {
    std::cout << "Usage:\n";
    std::cout << "1. Search in file: program <algorithm> -f <filename> -p <pattern>\n";
    std::cout << "2. Search in text: program <algorithm> -t <text> -p <pattern>\n";
    std::cout << "where algorithm is: bf (Brute Force) or bm (Boyer-Moore)\n";
}

std::string readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }
    return std::string((std::istreambuf_iterator<char>(file)),
                       std::istreambuf_iterator<char>());
}

void printResults(const std::string& algorithm,
                 const std::vector<int>& positions,
                 double executionTime) {
    std::cout << algorithm << " results:\n";
    std::cout << "Pattern found at positions: ";
    for (int pos : positions) {
        std::cout << pos << " ";
    }
    std::cout << "\nExecution time: " << executionTime << " ms\n\n";
}

int main(int argc, char* argv[]) {
    try {
        spdlog::set_level(spdlog::level::debug);
        spdlog::info("Starting string search program");

        if (argc < 5) {
            printUsage();
            return 1;
        }

        std::string algorithm = argv[1];
        std::string text;
        std::string pattern;

        // Parse command line arguments
        for (int i = 2; i < argc; i += 2) {
            std::string flag = argv[i];
            if (i + 1 >= argc) {
                std::cerr << "Missing value for " << flag << std::endl;
                return 1;
            }

            if (flag == "-f") {
                text = readFile(argv[i + 1]);
            }
            else if (flag == "-t") {
                text = argv[i + 1];
            }
            else if (flag == "-p") {
                pattern = argv[i + 1];
            }
            else {
                std::cerr << "Unknown flag: " << flag << std::endl;
                printUsage();
                return 1;
            }
        }

        if (text.empty() || pattern.empty()) {
            std::cerr << "Both text and pattern must be provided" << std::endl;
            printUsage();
            return 1;
        }

        spdlog::info("Searching for pattern '{}' in text of length {}",
                     pattern, text.length());

        if (algorithm == "bf") {
            BruteForceSearch bf;
            auto positions = bf.search(text, pattern);
            printResults("Brute Force", positions, bf.getLastExecutionTime());
        }
        else if (algorithm == "bm") {
            BoyerMoore bm;
            auto positions = bm.search(text, pattern);
            printResults("Boyer-Moore", positions, bm.getLastExecutionTime());
        }
        else {
            std::cerr << "Unknown algorithm: " << algorithm << std::endl;
            printUsage();
            return 1;
        }

    } catch (const std::exception& e) {
        spdlog::error("Error occurred: {}", e.what());
        return 1;
    }

    return 0;
}