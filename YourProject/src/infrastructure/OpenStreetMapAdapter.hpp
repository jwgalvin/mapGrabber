#pragma once
#include "domain/model/Location.hpp"
#include <vector>
#include <string>

namespace Infrastructure {

class OpenStreetMapAdapter {
public:
    std::vector<Domain::Model::Location> fetchSurroundingLocations(double lat, double lon) const {
        // Simulate external API call
        return {
            {lat + 0.001, lon + 0.001},
            {lat + 0.002, lon - 0.001},
            {lat - 0.001, lon + 0.002}
        };
    }

    std::string getProviderName() const {
        return "OpenStreetMap (simulated)";
    }
};

}  // namespace Infrastructure
