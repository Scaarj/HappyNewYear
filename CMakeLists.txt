cmake_minimum_required(VERSION 3.14)

project(HappyNewYear LANGUAGES CXX)
find_package (Threads REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCE ${PROJECT_SOURCE_DIR} *.cpp)
file(GLOB_RECURSE HEADER ${PROJECT_SOURCE_DIR} *.h)

add_executable(HappyNewYear
    main.cpp
    ${SOURCE}
    ${HEADER}
)

target_link_libraries(HappyNewYear
    PUBLIC
    ${CMAKE_THREAD_LIBS_INIT}
)
