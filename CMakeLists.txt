cmake_minimum_required(VERSION 3.5)

project(httpweather LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(HEADERS
    lib/httplib.h
    lib/ini.h
    lib/json.hpp
    )

set(SOURCES
    main.cpp
    )
add_executable(httpweather ${HEADERS} ${SOURCES})
file(COPY ${PROJECT_SOURCE_DIR}/html  DESTINATION ${PROJECT_BINARY_DIR})
