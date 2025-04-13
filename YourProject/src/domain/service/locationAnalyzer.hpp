#pragma once
#include "domain/model/Location.hpp"
#include <vector>
#include <string>

namespace Domain::Service {

class MapAnalyzer {
public:
    std::string classifyRegion(const std::vector<Domain::Model::Location>& points) const {
        if (points.size() < 3) {
            return "Too few points to classify region.";
        }
        // Fake classification logic
        return "Likely urban area based on density.";
    }
};

}  // namespace Domain::Service
