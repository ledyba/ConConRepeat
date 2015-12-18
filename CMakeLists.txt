cmake_minimum_required(VERSION 3.2.2)
project(ConConRepeat)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(OpenCV)

set(SOURCE_FILES main.cpp)
add_executable(ConConRepeat ${SOURCE_FILES})
target_include_directories(ConConRepeat PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(ConConRepeat ${OpenCV_LIBS})
