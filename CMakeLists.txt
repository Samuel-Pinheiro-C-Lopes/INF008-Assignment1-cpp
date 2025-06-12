cmake_minimum_required(VERSION 3.10)

project(ASSGN_1)

# FetchContent to download the library
include(FetchContent)
FetchContent_Declare(
  json
  URL https://github.com/nlohmann/json/releases/latest/download/json.tar.xz
)

FetchContent_MakeAvailable(json)

# Gets all the .cpp files in the src directory
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(ASSGN_1 ${SOURCES})

# Where to look for .h files
target_include_directories(ASSGN_1 PRIVATE
    ${PROJECT_SOURCE_DIR}/include/entity
    ${PROJECT_SOURCE_DIR}/include/prompt
    ${PROJECT_SOURCE_DIR}/include/named_entity
    ${PROJECT_SOURCE_DIR}/include/registration
    ${PROJECT_SOURCE_DIR}/include/event
    ${PROJECT_SOURCE_DIR}/include/participant
    ${PROJECT_SOURCE_DIR}/include/subject
    ${PROJECT_SOURCE_DIR}/include/university
    ${PROJECT_SOURCE_DIR}/include/values
    ${PROJECT_SOURCE_DIR}/include/data_gen
    ${PROJECT_SOURCE_DIR}/include/alias
    ${PROJECT_SOURCE_DIR}/include/json_generator
)

# linking the library
target_link_libraries(ASSGN_1 PRIVATE nlohmann_json)
