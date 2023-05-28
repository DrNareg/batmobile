cmake_minimum_required(VERSION 3.20)
project(xkcd)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE "Debug")

add_executable(xkcd main.cpp openai.cpp pinecone.cpp)

include(FetchContent)

FetchContent_Declare(cpr
    GIT_REPOSITORY https://github.com/libcpr/cpr.git
    GIT_TAG 3020c34ae2b732121f37433e61599c34535e68a8
)

FetchContent_Declare(
  nlohmann_json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.11.2
)

FetchContent_MakeAvailable(cpr nlohmann_json)

target_link_libraries(xkcd PRIVATE cpr::cpr nlohmann_json::nlohmann_json)
