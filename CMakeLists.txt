cmake_minimum_required(VERSION 3.10)

project(TRAB_1)
# Gets all the .cpp files in the
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(TRAB_1 ${SOURCES})

target_include_directories(TRAB_1 PRIVATE
    ${PROJECT_SOURCE_DIR}/include/entity
    ${PROJECT_SOURCE_DIR}/include/event
    ${PROJECT_SOURCE_DIR}/include/participant
)
