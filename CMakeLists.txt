cmake_minimum_required(VERSION 3.10)
project(WebServer)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

# Add spdlog
include(FetchContent)
FetchContent_Declare(
  spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG v1.10.0  # Use the latest stable version
)
FetchContent_MakeAvailable(spdlog)

add_executable(webserver src/main.cpp src/server.cpp src/http_parser.cpp src/router.cpp)

# Link spdlog
target_link_libraries(webserver PRIVATE spdlog::spdlog)