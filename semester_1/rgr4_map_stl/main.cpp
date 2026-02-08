#include "database.h"

#include <iostream>
#include <stdexcept>
#include <string>

int main() {
    try {
        Database data;
        data.readFromFile("info.txt");
        data.printOriginal(std::cout);
        data.printCardSorted(std::cout);
        data.printAveragePoint(std::cout);
        data.printNameSorted(std::cout);

        double min, max;
        std::cout << "\nEnter average score range (min - max): ";
        if (!(std::cin >> min >> max)) {
            std::runtime_error("Invalid input!");
        }

        data.printFromRange(std::cout, min, max);
        std::string subject;
        std::cout << "\nEnter subject name to search: ";
        if (!(std::cin >> subject)) {
            std::runtime_error("Invalid input!");
        }

        data.printWithSubject(std::cout, subject);
        data.printSubjectStatistics(std::cout);
        data.printBestStudents(std::cout);
        data.printBadStudents(std::cout);
    } catch (const std::exception& err) {
        std::cout << err.what() << std::endl;
    }

    return 0;
}