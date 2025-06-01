cmake_minimum_required(VERSION 3.10)

project(TRAB_1)
# Gets all the .cpp files in the src directory
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(TRAB_1 ${SOURCES})

# Where to look for .h files
target_include_directories(TRAB_1 PRIVATE
    ${PROJECT_SOURCE_DIR}/include/entity
    ${PROJECT_SOURCE_DIR}/include/event
    ${PROJECT_SOURCE_DIR}/include/participant
    ${PROJECT_SOURCE_DIR}/include/subject
    ${PROJECT_SOURCE_DIR}/include/university
)
