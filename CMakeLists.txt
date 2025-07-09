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

set(SOURCE_FILES
    src/main.cpp
    src/server.cpp
    src/http_parser.cpp
    src/router.cpp
    src/views.cpp
    src/urls.cpp
    src/logger.cpp
    src/thread_pool.cpp
)

# Add source files to the executable
add_executable(webserver ${SOURCE_FILES})

# Link libraries
target_link_libraries(webserver PRIVATE spdlog::spdlog nlohmann_json::nlohmann_json)