# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)

set(PROJECT_VER "0.1.0")
set(CMAKE_CXX_STANDARD 11)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(glaze VERSION ${PROJECT_VER})
