#include "openai.h"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <iostream>

OpenAI::OpenAI(const std::string& api_key) : api_key(api_key) {}

std::vector<float> OpenAI::embed(const std::string& text) {
    // Create the request payload
    nlohmann::json payload;
    payload["texts"] = {text};

    // Convert the payload to string
    std::string payload_str = payload.dump();

    // Send the POST request to the OpenAI embedding endpoint
    cpr::Response response = cpr::Post(cpr::Url{"https://api.openai.com/v1/engines/davinci/codex/completions"},
                                       cpr::Header{{"Authorization", "Bearer " + api_key},
                                                   {"Content-Type", "application/json"}},
                                       cpr::Body{payload_str});

    if (response.status_code == 200) {
        // Parse the JSON response
        nlohmann::json json_response = nlohmann::json::parse(response.text);
        std::vector<float> embedded_vector = json_response["choices"][0]["embedding"];
        return embedded_vector;
    } else {
        // Handle error response
        std::cout << "OpenAI embedding failed. Status code: " << response.status_code << std::endl;
        return std::vector<float>();
    }
}
