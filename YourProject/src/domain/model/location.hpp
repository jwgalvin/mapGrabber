#pragma once
#include <string>

namespace Domain::Model {

struct Location {
    double latitude;
    double longitude;

    Location(double lat, double lon) : latitude(lat), longitude(lon) {}
    
    std::string toString() const {
        return "Lat: " + std::to_string(latitude) + ", Lon: " + std::to_string(longitude);
    }
};

}  // namespace Domain::Model
