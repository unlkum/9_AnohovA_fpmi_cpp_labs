#include <cctype>
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

bool IsEmpty(std::ifstream& file) {
    return file.peek() == std::ifstream::traits_type::eof();
}

size_t CountWords(const std::string& line) {
    size_t counter{};
    bool is_word = false;
    for (const char c : line) {
        if (!std::isspace(static_cast<unsigned char>(c)) && !is_word) {
            is_word = true;
            ++counter;
        } else if (is_word == true) {
            is_word = false;
        }
    }
    return counter;
}

std::vector<std::string> GetBestLines(const std::filesystem::path& input, size_t& max_count) {
    std::ifstream in{input};
    if (!in.is_open()) {
        throw std::runtime_error("Can't open file \"" + input.string() + "\"");
    }
    if (IsEmpty(in)) {
        throw std::runtime_error("File \"" + input.string() + "\" is empty");
    }

    std::string line;
    std::vector<std::string> bestLines;
    while (std::getline(in, line)) {
        size_t now_count = CountWords(line);
        if (now_count > max_count) {
            max_count = now_count;
            bestLines.clear();
            bestLines.push_back(line);
        } else if (now_count == max_count && bestLines.size() < 10) {
            bestLines.push_back(line);
        }
    }
    in.close();
    return bestLines;
}

void PrintLines(const std::vector<std::string>& bestLines, size_t max_count) {
    std::cout << "Max words count in line is " << max_count << "\n\n";
    std::cout << "First 10 lines with max words count: \n";
    std::cout << "------------------------------------\n";
    for (size_t i = 0; i < bestLines.size(); ++i) {
        std::cout << i + 1 << ". " << bestLines[i] << "\n";
    }
}

int main() {
    const std::filesystem::path input{"input.txt"};
    try {
        size_t max_count{};
        std::vector<std::string> bestLines = GetBestLines(input, max_count);
        PrintLines(bestLines, max_count);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }

    return 0;
}