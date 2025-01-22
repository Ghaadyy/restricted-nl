cmake_minimum_required(VERSION 3.10)
project(restricted_nl)

set(CMAKE_CXX_STANDARD 23)

set(INCLUDE_DIR "${CMAKE_BINARY_DIR}/include")

set(JSON_HPP_URL "https://github.com/nlohmann/json/releases/download/v3.11.3/json.hpp")
set(JSON_HPP_PATH "${INCLUDE_DIR}/nlohmann/json.hpp")

set(CLI_HPP_URL "https://github.com/CLIUtils/CLI11/releases/download/v2.4.2/CLI11.hpp")
set(CLI_HPP_PATH "${INCLUDE_DIR}/CLI/CLI.hpp")

file(DOWNLOAD ${JSON_HPP_URL} ${JSON_HPP_PATH} SHOW_PROGRESS)
file(DOWNLOAD ${CLI_HPP_URL} ${CLI_HPP_PATH} SHOW_PROGRESS)

include_directories(${INCLUDE_DIR})

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "src/*.h")

add_executable(restricted_nl main.cpp ${SOURCE_FILES})

target_link_libraries(restricted_nl PRIVATE ${INCLUDE_DIR}/CLI/CLI.hpp)