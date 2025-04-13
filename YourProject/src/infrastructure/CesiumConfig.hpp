#pragma once
#include <string>

namespace Infrastructure {
    class CesiumConfig {
    public:
        static std::string LoadAccessToken(const std::string& path = "env.local");
    };
}
