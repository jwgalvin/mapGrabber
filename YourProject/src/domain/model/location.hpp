#pragma once
#include <string>
#include <optional>
#include <array>

namespace Domain::Model
{

    struct Location
    {
        double latitude;
        double longitude;
        double height;
        std::array<double, 4> boundingBox;

        Location() : latitude(0.0), longitude(0.0), height(0.0), boundingBox{0.0, 0.0, 0.0, 0.0} {}
        Location(double lat, double lon, double h = 0.0) : latitude(lat), longitude(lon), height(h), boundingBox{0.0, 0.0, 0.0, 0.0} {}

        std::string toString() const
        {
            std::string result = "Lat: " + std::to_string(latitude) + ", Lon: " + std::to_string(longitude) + ", Height: " + std::to_string(height);
            const auto &bb = boundingBox;
            result += ", BBox: [" + std::to_string(bb[0]) + ", " + std::to_string(bb[1]) + ", " + std::to_string(bb[2]) + ", " + std::to_string(bb[3]) + "]";
            return result;
        }
    };

} // namespace Domain::Model
