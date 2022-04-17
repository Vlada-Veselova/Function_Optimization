cmake_minimum_required(VERSION 3.5)

project(Console_Optimization LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    main.cpp
    stochastic.cpp
    gradient.cpp
    criteria.cpp
    function.cpp)
set(HEADERS
    stochastic.h
    Optimization.h
    function.h
    criteria.h
    gradient.h
)
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC include)
