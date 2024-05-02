# CMakeList.txt : CMake project for mathutils, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("C-Gym-Envs")

add_subdirectory(pybind11)
include_directories("${CMAKE_SOURCE_DIR}/include")

PYBIND11_ADD_MODULE(TradingEnv main.cpp)
# TODO: Add tests and install targets if needed.
