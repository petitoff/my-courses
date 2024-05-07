cmake_minimum_required(VERSION 3.27)
project(lista3)

set(CMAKE_CXX_STANDARD 17)
add_definitions(-DUNICODE -D_UNICODE) # Dla wsparcia Unicode

add_executable(lista3 main.cpp)
