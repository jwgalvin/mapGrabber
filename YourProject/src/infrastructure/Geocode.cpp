#include "Geocode.hpp"
#include "domain/model/location.hpp"

#include <curl/curl.h>
#include <iostream>
#include <sstream>
#include <string>
#include "json.hpp"
#include <libpostal/libpostal.h>
#include <optional>
#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <array>

using json = nlohmann::json;

namespace Infrastructure
{

    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *output)
    {
        size_t totalSize = size * nmemb;
        output->append((char *)contents, totalSize);
        return totalSize;
    }

    std::string urlEncode(const std::string &value)
    {
        CURL *curl = curl_easy_init();
        char *encoded = curl_easy_escape(curl, value.c_str(), value.length());
        std::string result(encoded);
        curl_free(encoded);
        curl_easy_cleanup(curl);
        return result;
    }

    std::optional<Domain::Model::Location> FetchCoordinatesFromAddress(const std::string &address)
    {
        if (!libpostal_setup() || !libpostal_setup_parser())
        {
            std::cerr << "❌ Failed to initialize libpostal.\n";
            return std::nullopt;
        }

        std::string mutableAddress = address;
        libpostal_address_parser_response_t *parsed =
            libpostal_parse_address(mutableAddress.data(), libpostal_get_address_parser_default_options());

        if (!parsed)
        {
            std::cerr << "❌ Failed to parse address.\n";
            return std::nullopt;
        }

        std::string street, city, state, zip;
        for (size_t i = 0; i < parsed->num_components; i++)
        {
            std::string component = parsed->components[i];
            std::string label = parsed->labels[i];

            if (label == "house_number" || label == "road")
            {
                street += component + " ";
            }
            else if (label == "city")
            {
                city = component;
            }
            else if (label == "state")
            {
                state = component;
            }
            else if (label == "postcode")
            {
                zip = component;
            }
        }

        libpostal_address_parser_response_destroy(parsed);
        libpostal_teardown();
        libpostal_teardown_parser();

        if (street.empty() || city.empty() || state.empty() || zip.empty())
        {
            std::cerr << "❌ Address components are incomplete.\n";
            return std::nullopt;
        }

        if (zip.length() != 5 || !std::all_of(zip.begin(), zip.end(), ::isdigit))
        {
            std::cerr << "❌ Invalid ZIP code. Please enter a valid 5-digit ZIP code.\n";
            return std::nullopt;
        }

        std::ostringstream urlBuilder;
        urlBuilder << "https://nominatim.openstreetmap.org/search?";
        urlBuilder << "street=" << urlEncode(street)
                   << "&city=" << urlEncode(city)
                   << "&state=" << urlEncode(state)
                   << "&postalcode=" << urlEncode(zip)
                   << "&format=json";

        std::string url = urlBuilder.str();
        std::cout << "🌍 Geocoding URL: " << url << "\n";

        CURL *curl = curl_easy_init();
        if (!curl)
        {
            std::cerr << "❌ Failed to initialize curl.\n";
            return std::nullopt;
        }

        std::string response;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "MapGrabberCLI/1.0");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            std::cerr << "❌ curl_easy_perform() failed: " << curl_easy_strerror(res) << "\n";
            curl_easy_cleanup(curl);
            return std::nullopt;
        }

        curl_easy_cleanup(curl);

        try
        {
            auto jsonResponse = json::parse(response);
            if (!jsonResponse.empty())
            {
                const auto &result = jsonResponse[0];
                Domain::Model::Location loc;
                loc.latitude = std::stod(result["lat"].get<std::string>());
                loc.longitude = std::stod(result["lon"].get<std::string>());
                loc.height = 0.0; // Nominatim doesn't return elevation

                if (result.contains("boundingbox"))
                {
                    auto bb = result["boundingbox"];
                    if (bb.is_array() && bb.size() == 4)
                    {
                        loc.boundingBox = {
                            std::stod(bb[0].get<std::string>()),
                            std::stod(bb[1].get<std::string>()),
                            std::stod(bb[2].get<std::string>()),
                            std::stod(bb[3].get<std::string>())};
                    }
                }

                return loc;
            }
            else
            {
                std::cerr << "⚠️ No geocode results found. Response: " << response << "\n";
                return std::nullopt;
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "❌ JSON parse error: " << e.what() << ". Response: " << response << "\n";
            return std::nullopt;
        }

        return std::nullopt;
    }

}
