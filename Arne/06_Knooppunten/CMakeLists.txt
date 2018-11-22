cmake_minimum_required(VERSION 3.12)
project(06_Knooppunten)

set(CMAKE_CXX_STANDARD 14)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

include_directories(.)

add_executable(06_Knooppunten
        fietsgraaf.xml
        graaf.h
        stroomnet17.cpp
        stroomnet17.h)
