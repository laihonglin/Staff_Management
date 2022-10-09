cmake_minimum_required(VERSION 3.16)
project(Staff_Management)

set(CMAKE_CXX_STANDARD 11)

add_executable(Staff_Management Staff_System.cpp workerManager.cpp worker.cpp
        employee.cpp manager.cpp boss.cpp)