#pragma once

#include "domain/model/location.hpp"
#include <string>
#include <optional>

namespace Infrastructure
{
    std::optional<Domain::Model::Location> FetchCoordinatesFromAddress(const std::string &address);
}
