#include <cctype>
#include <fstream>
#include <iostream>
#include <vector>
// TODO solve lab 6 and 7 
// TODO перегрузки операторов, все про классы 

int count_words(const std::string &str) {
    bool is_word = false;
    int counter = 0;
    int answer = 0;
    for (size_t i = 0; i < str.length(); i++) {
        if (!std::isspace(str[i])) {
            if (!is_word) {
                is_word = true;
                answer++;
            }
        } else {
            is_word = false;
        }
    }

    return answer;
}

int main() {

    const std::string input_file = "input.txt";
    const std::string output_file = "output.txt";

    std::ifstream fin("../input.txt");
    if (!fin.is_open()) {
        std::cout << "Error opening file :(\n";
        std::exit(1);
    }

    int max_word_count = 0;
    bool found_non_empty_line = false;

    std::vector<std::string> lines_with_max_words;

    std::string str;
    while (getline(fin, str)) {
        int word_count = count_words(str);
        if (word_count > 0) {
            found_non_empty_line = true;
        }
        if (word_count > max_word_count) {
            max_word_count = word_count;
            lines_with_max_words.clear();
            lines_with_max_words.push_back(str);
        } else if (word_count == max_word_count) {
            lines_with_max_words.push_back(str);
        }
    }

    if (!found_non_empty_line) {
        std::cout << "All lines in the file are empty or contain no words\n";
        fin.close();
        return 0;
    }

    int len = lines_with_max_words.size();
    for (int i = 0; i < std::min(10, len); i++) {
        std::cout << lines_with_max_words[i] << '\n';
    }

    fin.close();
    return 0;
}