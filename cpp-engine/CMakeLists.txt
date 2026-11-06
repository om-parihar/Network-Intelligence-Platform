
cmake_minimum_required(VERSION 3.20)

project(NetworkIntelligencePlatform LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(nip_engine
    src/main.cpp
    src/graph/Graph.cpp
)

target_include_directories(nip_engine PRIVATE include)
