#ifndef OPENAI_H
#define OPENAI_H

#include <string>
#include <vector>

class OpenAI {
public:
    OpenAI(const std::string& api_key);

    std::vector<float> embed(const std::string& text);

private:
    std::string api_key;
};

#endif  // OPENAI_H
