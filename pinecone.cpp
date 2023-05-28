#include "pinecone.h"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <iostream>

Pinecone::Pinecone(const std::string& api_key) : api_key(api_key) {}

std::string Pinecone::query(const std::vector<float>& vec) {
    nlohmann::json body;
    body["topK"] = 1;
    body["vector"] = vec;

    cpr::Header headers{
        {"Api-Key", api_key},
        {"Content-Type", "application/json"}
    };

    auto response = cpr::Post(
        cpr::Url{"https://xkcd-de1fb6b.svc.us-central1-gcp.pinecone.io/query"},
        headers,
        cpr::Body{body.dump()});

    if (response.status_code == 200) {
        auto res_json = nlohmann::json::parse(response.text);
        auto matches = res_json["matches"];
        return matches[0]["id"];
    } else {
        std::cerr << "Error: " << response.status_code << std::endl;
        return "";
    }
}
