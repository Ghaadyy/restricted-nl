cmake_minimum_required(VERSION 3.10)
project(restricted_nl)

include(FetchContent)

set(CMAKE_CXX_STANDARD 23)
set(FETCHCONTENT_QUIET OFF)

FetchContent_Declare(
    CLI11
    GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
    GIT_TAG        v2.4.2
    GIT_PROGRESS   TRUE
    GIT_SHALLOW    TRUE
)

FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG        v3.11.3
    GIT_PROGRESS   TRUE
    GIT_SHALLOW    TRUE
)

FetchContent_MakeAvailable(CLI11)
FetchContent_MakeAvailable(json)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "src/*.h")

add_executable(restricted_nl main.cpp ${SOURCE_FILES})

target_link_libraries(restricted_nl PRIVATE CLI11)

target_include_directories(restricted_nl PRIVATE ${json_SOURCE_DIR}/include)