cmake_minimum_required(VERSION 3.16)
project(Super_Vision)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

include_directories(
    ${OpenCV_INCLUDE_DIRS}
    /opt/homebrew/include
    ${CMAKE_SOURCE_DIR}/include
)

link_directories(/opt/homebrew/lib)

add_executable(Super_Vision
     main.cpp
     src/ImageLoader.cpp
     src/Application.cpp
     src/EdgeDetector.cpp
     src/GaussianBlur.cpp
     src/ThresholdProcessor.cpp
     src/MorphologicalFiltering.cpp
     src/CameraProcessor.cpp
     src/InferenceEngine.cpp
)

target_link_libraries(Super_Vision
    ${OpenCV_LIBS}
    onnxruntime
)