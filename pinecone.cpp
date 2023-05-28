#include "pinecone.h"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <iostream>

Pinecone::Pinecone(const std::string& api_key) : api_key(api_key) {}

std::string Pinecone::query(const std::vector<float>& vec) {
    // Convert the embedded vector to a JSON array
    nlohmann::json json_vec(vec);

    // Create the request payload
    nlohmann::json payload;
    payload["query"] = json_vec;

    // Convert the payload to string
    std::string payload_str = payload.dump();

    // Send the POST request to the Pinecone query endpoint
    cpr::Response response = cpr::Post(cpr::Url{"https://api.pinecone.io/v1/indexes/<INDEX_NAME>/query"},
                                       cpr::Header{{"Authorization", "Bearer " + api_key},
                                                   {"Content-Type", "application/json"}},
                                       cpr::Body{payload_str});

    if (response.status_code == 200) {
        // Parse the JSON response
        nlohmann::json json_response = nlohmann::json::parse(response.text);
        std::string comic_id = json_response["hits"][0]["id"];
        return comic_id;
    } else {
        // Handle error response
        std::cout << "Pinecone query failed. Status code: " << response.status_code << std::endl;
        return "";
    }
}
