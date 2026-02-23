#include <algorithm>
#include <exception>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using HotelData = std::map<std::string, std::vector<std::pair<std::string, std::string>>>;
using HotelPairData = std::pair<std::string, std::vector<std::pair<std::string, std::string>>>;
using HotelUnitData = std::pair<std::string, std::string>;

void checkFile(std::ifstream& file) {
    if (!file.is_open()) {
        throw std::runtime_error("Cant open file");
    }
    if (file.peek() == EOF) {
        throw std::runtime_error("Empty file");
    }
}

HotelData readFromFlow(const std::string& filename) {
    std::ifstream file{filename};
    checkFile(file);
    HotelData Hotels;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }
        std::string city, name, stars;
        std::stringstream ss(line);
        if (std::getline(ss, city, ';') && std::getline(ss, name, ';') && std::getline(ss, stars)) {
            Hotels[city].push_back({name, stars});
        }
    }
    file.close();

    return Hotels;
}

void processLine(const std::string& type, const std::string argument, const HotelData& Hotels) {
    if (type == "1") {
        if (Hotels.count(argument)) {
            for (const auto& hotel : Hotels.at(argument)) {
                std::cout << "Отель: " << hotel.first << " | Звезд: " << hotel.second << "\n";
            }
        } else {
            std::cout << "Информация отсутствует (город не найден)\n";
        }
    } else if (type == "2") {
        // count_if - +1 если правда и 0 если false
        // any_of - 1 если выполняется условие
        size_t count =
            std::count_if(Hotels.begin(), Hotels.end(), [argument](const HotelPairData& elem) {
                return std::any_of(
                    elem.second.begin(), elem.second.end(),
                    [argument](const HotelUnitData& hotel) { return hotel.first == argument; });
            });

        if (count > 0) {
            std::cout << "Отель '" << argument << "' встречается в " << count << " гор.\n";
        } else {
            std::cout << "Информация отсутствует (отель не найден)\n";
        }

    } else if (type == "3") {
        // city , stars
        std::set<std::pair<std::string, std::string>> uniq_pairs;

        for (const auto& place : Hotels) {
            for (const auto& hotel : place.second) {
                uniq_pairs.insert({place.first, hotel.second});
            }
        }

        if (uniq_pairs.empty()) {
            std::cout << "Данные отсутствуют\n";
        } else {
            for (const auto& p : uniq_pairs) {
                std::cout << "<" << p.first << ", " << p.second << ">\n";
            }
        }
    }
}

void processQuery(const std::string& filename, const HotelData& Hotels) {
    std::ifstream file{filename};
    checkFile(file);

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }
        std::stringstream ss(line);
        std::string str, type, argument;
        type = line[0];
        argument = line.size() > 2 ? line.substr(2) : "";
        processLine(type, argument, Hotels);
    }
}

int main() {
    const std::string input{"DATA.TXT"};
    const std::string query{"QUERY.TXT"};
    std::setlocale(LC_ALL, "Russian");
    try {
        HotelData Hotels = readFromFlow("DATA.TXT");
        processQuery("QUERY.TXT", Hotels);

    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}