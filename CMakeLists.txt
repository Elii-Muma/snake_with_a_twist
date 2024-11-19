cmake_minimum_required(VERSION 3.5.0)
project(main VERSION 0.1.0 LANGUAGES C CXX)

project(main)

set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/cmake/SFML")

set(CMAKE_BUILD_TYPE Debug)

set(SOURCE_FILES
    src/main.cpp
    src/Game.cpp
    src/Board.cpp
    src/List.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

#set c++ std
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

#find sfml package
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.6.1 COMPONENTS graphics window system REQUIRED)

#include dirs
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

#link sfml libs
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window sfml-system)

#add defs for static sfml linking
target_compile_definitions(${PROJECT_NAME} PRIVATE SFML_STATIC)

#additional propertis

if(WIN32)
    target_link_options(${PROJECT_NAME} PRIVATE -mconsole)
endif()
