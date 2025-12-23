#pragma once

#include <iostream>
#include <string>
#include "time_utility.h"

using TrainId = size_t;
using namespace time_utility;

enum class TrainType { PASSENGER, FREIGHT, HIGH_SPEED, SUBWAY, SPECIALIZED };

class Train {
private:
    TrainId id_;
    TrainType type_;
    std::string destination_;
    std::time_t dispatch_time_;
    std::time_t travelling_time_;

public:
    // your code
    Train(TrainId id, TrainType type, std::string dest, std::time_t dispatch, std::time_t travel)
        : id_(id),
          type_(type),
          destination_(dest),
          dispatch_time_(dispatch),
          travelling_time_(travel) {
    }

    TrainId GetId() const {
        return id_;
    }
    TrainType GetType() const {
        return type_;
    }
    std::string GetDestination() const {
        return destination_;
    }
    std::time_t GetDispatchTime() const {
        return dispatch_time_;
    }
    std::time_t GetTravellingTime() const {
        return travelling_time_;
    }

    void Print() const {
        std::cout << "Id: " << id_ << " | Dest: " << destination_
                  << " | Type: " << static_cast<int>(type_) << "\n";
        std::cout << "Departure: ";
        PrintTime(dispatch_time_);
        std::cout << "In trip:   ";
        PrintTime(travelling_time_);
        std::cout << "----------------------------------------" << std::endl;
    }
};
