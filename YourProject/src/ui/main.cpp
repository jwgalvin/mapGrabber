#include "../../infrastructure/OpenStreetMapAdapter.hpp"
#include "../domain/service/locationAnalyzer.hpp"
#include <iostream>

int main() {
    Infrastructure::OpenStreetMapAdapter mapApi;
    auto points = mapApi.fetchSurroundingLocations(37.7749, -122.4194);  // SF coords

    Domain::Service::MapAnalyzer analyzer;
    std::string classification = analyzer.classifyRegion(points);

    std::cout << "Provider: " << mapApi.getProviderName() << "\n";
    std::cout << "Region classification: " << classification << "\n";
    return 0;
}
