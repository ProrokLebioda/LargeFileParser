cmake_minimum_required(VERSION 3.5.0)
project(largeFileParser)
set(CMAKE_CXX_STANDARD 17)
set(SOURCE_FILES
    source/main.cpp
    source/fileprocessor.cpp)
    
include_directories(${PROJECT_SOURCE_DIR})
add_executable(${PROJECT_NAME} ${SOURCE_FILES})