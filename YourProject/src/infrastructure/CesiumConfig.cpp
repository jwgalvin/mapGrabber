#include "infrastructure/CesiumConfig.hpp"
#include <fstream>
#include <sstream>

namespace Infrastructure {

std::string CesiumConfig::LoadAccessToken(const std::string& path) {
    std::ifstream file(path);
    std::string line;
    const std::string key = "CESIUM_ACCESS_TOKEN=";

    while (std::getline(file, line)) {
        if (line.rfind(key, 0) == 0) {
            return line.substr(key.length());
        }
    }

    return "";
}

}
