/*
ProcessString сделает вектор вещественных чисел
GetSum через accumulate
IsDoubleNum

*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <vector>

bool IsEmpty(std::ifstream& f) {
    return f.peek() == std::ifstream::traits_type::eof();
}

bool IsDoubleNum(std::string& num) {
    size_t dot_count = 0;
    size_t num_count = 0;

    for (const char s : num) {
        if (std::isdigit(s)) {
            ++num_count;
        } else if (s == '.') {
            ++dot_count;
        } else {
            return false;
        }
    }

    if (dot_count != 1 || num_count < 1) {
        return false;
    }
    return true;
}

void ProcessLine(std::string& line, std::string& delims, std::vector<double>& nums) {
    size_t pos = 0;
    std::string word;
    while (pos < line.size()) {
        size_t start = line.find_first_not_of(delims, pos);
        if (start == std::string::npos) {
            break;
        }
        size_t end = line.find_first_of(delims, start);
        word = line.substr(start, end - start);
        if (IsDoubleNum(word)) {
            nums.push_back(std::stod(word));
        }
        pos = (end == std::string::npos) ? line.size() : end;
    }
}

double Sum(std::vector<double>& nums) {
    return std::accumulate(nums.begin(), nums.end(), 0.0);
}

int main() {
    const std::string inf = "IN33.txt";
    const std::string outf = "OUT33.txt";

    try {
        std::ifstream in{inf};
        if (!in.is_open()) {
            throw "Can't open input file";
        }
        if (IsEmpty(in)) {
            throw "Empty file";
        }

        std::ofstream out{outf};
        if (!out.is_open()) {
            throw "Can't open outpt file";
        }

        std::string delim;
        if (!std::getline(in, delim)) {
            throw "Can't read delimiters";
        }

        std::string line;

        while (std::getline(in, line)) {
            std::vector<double> nums;
            ProcessLine(line, delim, nums);

            if (nums.size() != 0) {
                for (size_t i = 0; i < nums.size(); ++i) {
                    out << nums[i];
                    if (i != nums.size() - 1) {
                        out << " + ";
                    }
                }

                out << " = " << Sum(nums) << '\n';
            } else {
                out << "В строке нет чисел\n";
            }
        }
        in.close();
        out.close();
    } catch (const char* msg) {
        std::cerr << msg << '\n';
        return 1;
    }
}