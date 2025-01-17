cmake_minimum_required(VERSION 3.28)
project(OI)

set(CMAKE_CXX_STANDARD 17)

add_executable(OI
        algorytmy/inne/monotonic-queue.cpp
        budowa-jezyka/move.cpp
)