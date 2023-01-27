cmake_minimum_required(VERSION 3.18)

project(coreqml_project VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6 COMPONENTS Core Quick Gui Qml REQUIRED)

add_subdirectory(coreqml)
target_include_directories(coreqml PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(example)

