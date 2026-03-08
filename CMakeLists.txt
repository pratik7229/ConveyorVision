cmake_minimum_required(VERSION 3.16)
project(Super_Vision)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)
include_directories(
    ${OpenCV_INCLUDE_DIRS},
    ${CMAKE_SOURCE_DIR}/include
)

add_executable(Super_Vision
     main.cpp
     src/ImageLoader.cpp
     src/Application.cpp
     src/EdgeDetector.cpp
     src/GaussianBlur.cpp
     src/ThresholdProcessor.cpp
     src/MorphologicalFiltering.cpp
     )
target_link_libraries(Super_Vision ${OpenCV_LIBS})