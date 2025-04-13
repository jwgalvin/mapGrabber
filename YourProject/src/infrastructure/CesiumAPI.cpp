#include "./CesiumConfig.hpp"
#include <curl/curl.h>
#include <iostream>
#include <string>

namespace Infrastructure {

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

void FetchCesiumAssets() {
    std::cout << "📡 Entered FetchCesiumAssets()\n";
    std::string token = CesiumConfig::LoadAccessToken();
    if (token.empty()) {
        std::cerr << "❌ Cesium token not found.\n";
        return;
    }

    CURL* curl = curl_easy_init();
    if (curl) {
        std::string response;
        std::string url = "https://api.cesium.com/v1/assets";
        std::string authHeader = "Authorization: Bearer " + token;
        std::cout << "🔗 Requesting URL: " << url << "\n";
        std::cout << "🐞 Using token: " << token.substr(0, 10) << "...\n";


        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, authHeader.c_str());

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); // 🔍 Debug HTTP trace

        std::cout << "⚡ Attempting request to Cesium Ion...\n";
        std::cout << "🔗 Requesting URL: " << url << "\n";

        CURLcode res = curl_easy_perform(curl);
        std::cout << "🌐 Request completed\n";

        if (res != CURLE_OK) {
            std::cerr << "❌ curl_easy_perform() failed: " << curl_easy_strerror(res) << "\n";
        } else {
            if (response.empty()) {
                std::cout << "⚠️ curl succeeded, but response was empty.\n";
            } else {
                std::cout << "✅ Response from Cesium Ion:\n" << response << "\n";
            }
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    } else {
        std::cerr << "❌ curl_easy_init() failed.\n";
    }
}

}