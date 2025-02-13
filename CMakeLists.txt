cmake_minimum_required(VERSION 3.10)
project(WebServer)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

# Add spdlog
include(FetchContent)
FetchContent_Declare(
  spdlog
  GIT_REPOSITORY git@github.com:gabime/spdlog.git
  GIT_TAG v1.10.0
)
FetchContent_MakeAvailable(spdlog)

# Add nlohmann/json
FetchContent_Declare(
  json
  GIT_REPOSITORY git@github.com:nlohmann/json.git
  GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(json)

add_executable(webserver src/main.cpp src/server.cpp src/http_parser.cpp src/router.cpp src/urls.cpp src/views.cpp src/logger.cpp)

# Link spdlog
target_link_libraries(webserver PRIVATE spdlog::spdlog)

# Link nlohmann/json
target_link_libraries(webserver PRIVATE nlohmann_json::nlohmann_json)