#include <iostream>
#include <string>
#include <vector>


class BruteForceSearch {
public:

    std::vector<int> search(const std::string& text, const std::string& pattern) {
        std::vector<int> results;
        int n = text.length();
        int m = pattern.length();

        if (m == 0 || n == 0 || m > n) {
            return results;
        }

        for (int i = 0; i <= n - m; i++) {
            bool found = true;

            for (int j = 0; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    found = false;
                    break;
                }
            }

            if (found) {
                results.push_back(i);
            }
        }

        return results;
    }
};

int main() {
    BruteForceSearch bf;

    std::string text = "ABAAABCDABAAABCD";
    std::string pattern = "ABC";


    std::vector<int> positions = bf.search(text, pattern);
    std::cout << "Pattern found at positions: ";
    for (int pos : positions) {
        std::cout << pos << " ";
    }

    std::cout << std::endl;

    return 0;
}
