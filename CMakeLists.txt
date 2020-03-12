cmake_minimum_required(VERSION 3.13)
project(ConConRepeat)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

add_executable(ConConRepeat
    main.cpp
)
target_include_directories(ConConRepeat PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(ConConRepeat ${OpenCV_LIBS})
