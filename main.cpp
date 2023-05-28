#include "openai.h"
#include "pinecone.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

bool arg_exists(const std::string& arg, char** begin, char** end) {
    std::vector<std::string> args(begin, end);
    return std::find(args.begin(), args.end(), arg) != args.end();
}

int main(int argc, char* argv[]) {
    // Parse command-line arguments
    bool img_flag = arg_exists("--img", argv, argv + argc);
    std::string search_text;
    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) != "--img") {
            search_text = argv[i];
            break;
        }
    }

    // Enter your OpenAI API key
    std::string openai_api_key = "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";
    OpenAI openai(openai_api_key);

    // Enter your Pinecone API key
    std::string pinecone_api_key = "e0efc429-00c7-430d-920e-310a6c58f74b";
    Pinecone pinecone(pinecone_api_key);

    // Embed the search text
    std::vector<float> embedded_query = openai.embed(search_text);

    // Query Pinecone with the embedded search text
    std::string comic_id = pinecone.query(embedded_query);

    // Construct the URL of the relevant comic or its image based on the comic ID
    std::string url = "https://xkcd.com/" + comic_id;
    if (img_flag) {
        url += "/info.0.json";
    }

    // Print the URL
    std::cout << url << std::endl;

    return 0;
}
