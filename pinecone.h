#ifndef PINECONE_H
#define PINECONE_H

#include <string>
#include <vector>

class Pinecone {
public:
    Pinecone(const std::string& api_key);

    std::string query(const std::vector<float>& vec);

private:
    std::string api_key;
};

#endif  // PINECONE_H
