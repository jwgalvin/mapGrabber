#include "infrastructure/Geocode.hpp"
#include "domain/model/location.hpp"

#include <iostream>
#include <unistd.h>
#include <limits.h>
#include <string>
#include <fstream>

int main()
{
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != nullptr)
    {
        std::cout << "Current working directory: " << cwd << std::endl;
    }
    else
    {
        std::cerr << "Error getting current working directory" << std::endl;
    }

    // Prompt for address components
    std::string street, city, state, zip;
    std::cout << "\U0001F4E8 Enter street and number: ";
    std::getline(std::cin, street);
    std::cout << "\U0001F4E8 Enter city: ";
    std::getline(std::cin, city);
    std::cout << "\U0001F4E8 Enter state (2-letter abbreviation): ";
    std::getline(std::cin, state);
    std::cout << "\U0001F4E8 Enter zip code: ";
    std::getline(std::cin, zip);

    // Build full address string
    std::string address = street + ", " + city + ", " + state + " " + zip;

    // Call Nominatim
    std::optional<Domain::Model::Location> location = Infrastructure::FetchCoordinatesFromAddress(address);
    if (location.has_value())
    {
        auto loc = location.value();
        std::cout << "\n\U0001F4CD Resolved Location:\n";
        std::cout << "   Latitude:  " << loc.latitude << "\n";
        std::cout << "   Longitude: " << loc.longitude << "\n";
        std::cout << "   Height:    " << loc.height << "\n";

        // Save to JSON file
        std::ofstream out("location.json");
        if (out.is_open())
        {
            out << "{\n";
            out << "  \"latitude\": " << loc.latitude << ",\n";
            out << "  \"longitude\": " << loc.longitude << ",\n";
            out << "  \"height\": " << loc.height << ",\n";
            out << "  \"boundingBox\": ["
                << loc.boundingBox[0] << ", "
                << loc.boundingBox[1] << ", "
                << loc.boundingBox[2] << ", "
                << loc.boundingBox[3] << "]\n";
            out << "}" << std::endl;
            out.close();
            std::cout << "✅ location.json written successfully.\n";
        }
        else
        {
            std::cerr << "❌ Failed to open location.json for writing.\n";
        }
    }
    else
    {
        std::cerr << "❌ Could not resolve the address with Nominatim.\n";
    }

    return 0;
}
