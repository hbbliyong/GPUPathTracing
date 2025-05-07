cmake_minimum_required(VERSION 3.28)

project(
    CPUPathTracing
    LANGUAGES CXX
)
set(CMAKE_CXX_STANDARD 17)
set(RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
add_subdirectory(thirdparty/glm)
add_subdirectory(source)