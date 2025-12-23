#include "time_utility.h"
#include "train.h"
#include <algorithm>
#include <exception>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>

bool IsEmptyFile(std::ifstream& file) {
    return file.peek() == std::ifstream::traits_type::eof();
}

std::vector<Train> ReadFromFile(const std::string& filename) {
    std::ifstream file{filename};
    if (!file.is_open()) {
        throw std::runtime_error("Error: Could not open the file \"" + filename + "\"...");
    }

    if (IsEmptyFile(file)) {
        throw std::runtime_error("Error: File \"" + filename + "\" is empty...");
    }
    size_t id, type_int, h1, m1, h2, m2;
    std::string dest;

    std::vector<Train> v;
    while (file >> id >> type_int >> dest >> h1 >> m1 >> h2 >> m2) {
        std::time_t dispatch = SetTime(h1, m1);
        std::time_t travel = SetTime(h2, m2);

        v.push_back(Train(id, static_cast<TrainType>(type_int), dest, dispatch, travel));
    }
    file.close();

    return v;
}

void SortByTime(std::vector<Train>& v) {
    std::sort(v.begin(), v.end(), [](const Train& a, const Train& b) {
        return a.GetDispatchTime() < b.GetDispatchTime();
    });
}

void PrintFromTimeInterval(const std::time_t start_time, const std::time_t end_time,
                           const std::vector<Train>& trains) {
    std::cout << "\nTrains departing between ";
    PrintTime(start_time);
    std::cout << " and ";
    PrintTime(end_time);
    std::cout << " :\n";

    for (const auto& t : trains) {
        if (t.GetDispatchTime() >= start_time && t.GetDispatchTime() <= end_time) {
            t.Print();
        }
    }
}

void PrintFromDest(const std::string& dest, const std::vector<Train>& trains) {
    std::cout << "\nTrains to " << dest << ":\n";

    for (const auto& t : trains) {
        if (t.GetDestination() == dest) {
            t.Print();
        }
    }
}

void PrintSameTypeFromDest(const std::string& dest, const TrainType type,
                           const std::vector<Train>& trains) {
    std::cout << "\nTrains to " << dest << " with type index " << static_cast<int>(type) << ":\n";
    for (const auto& t : trains) {
        if (t.GetDestination() == dest && t.GetType() == type) {
            t.Print();
        }
    }
}

void PrintFastestTrain(const std::string& dest, const std::vector<Train>& trains) {

    const Train* fastest = nullptr;

    for (const auto& t : trains) {
        if (t.GetDestination() == dest) {
            if (fastest == nullptr || t.GetTravellingTime() < fastest->GetTravellingTime()) {
                fastest = &t;
            }
        }
    }

    std::cout << "\nFastest train to " << dest << ":\n";
    if (fastest) {
        fastest->Print();
    } else {
        std::cout << "There are no trains :(\n";
    }
}

void PrintTrains(const std::vector<Train>& trains) {
    for (const auto& t : trains) {
        t.Print();
    }
}

int main() {

    using namespace time_utility;

    std::random_device rd;
    std::mt19937 generator(rd());

    std::time_t t1 = SetTime(12, 23);
    try {
        t1 = SetTime(12, 60);
    } catch (const std::out_of_range& err) {
        std::cerr << err.what() << std::endl;
    }

    std::time_t t2 = GenerateRandomTime(generator);

    std::cout << "t1: ";
    PrintTime(t1);

    std::cout << "t2: ";
    PrintTime(t2);

    std::cout << "t1 < t2: " << std::boolalpha << (t1 < t2) << '\n';
    std::cout << "t2 < t1: " << std::boolalpha << (t2 < t1) << '\n';

    const std::string input_file = "data.txt";

    try {
        std::vector<Train> v = ReadFromFile(input_file);
        std::cout << "\n\nFound " << v.size() << " trains\n";
        // Sort trains
        SortByTime(v);
        std::cout << "Sorted trains by dispatch time: \n";
        PrintTrains(v);

        // Trains from interval
        PrintFromTimeInterval(SetTime(9, 0), SetTime(18, 0), v);

        // Trains to one destination
        const std::string city = "Moscow";
        PrintFromDest(city, v);

        // Trains to one destination and type
        const TrainType train_type = TrainType::PASSENGER;
        PrintSameTypeFromDest(city, train_type, v);

        // Fastest train
        PrintFastestTrain(city, v);

    } catch (const std::exception& err) {
        std::cerr << err.what() << std::endl;
    }

    return EXIT_SUCCESS;
}

// g++ main.cpp time_utility.cpp -o lab2
// ./lab2