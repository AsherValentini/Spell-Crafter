cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17) 
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Spell-Crafter)

include_directories(src)
add_executable(prog
	src/main.cpp
)
