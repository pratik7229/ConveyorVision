cmake_minimum_required(VERSION 3.16)
project(Super_Vision)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Find OpenCV (Works on both Mac and Linux automatically)
find_package(OpenCV REQUIRED)

# 2. Handle ONNX Runtime Paths (Conditional Logic)
if(DEFINED ENV{ONNXRUNTIME_ROOT})
    # This block executes on GitHub Actions (Linux)
    set(ONNX_INCLUDE_DIR "$ENV{ONNXRUNTIME_ROOT}/include")
    set(ONNX_LIB_DIR "$ENV{ONNXRUNTIME_ROOT}/lib")
    message(STATUS "CI detected: Using ONNX at ${ONNX_INCLUDE_DIR}")
else()
    # This block executes on your Mac
    set(ONNX_INCLUDE_DIR "/opt/homebrew/include")
    set(ONNX_LIB_DIR "/opt/homebrew/lib")
    message(STATUS "Local Mac detected: Using Homebrew paths")
endif()

# 3. Set Include Directories
include_directories(
    ${OpenCV_INCLUDE_DIRS}
    ${ONNX_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/include
)

# 4. Set Link Directories
link_directories(${ONNX_LIB_DIR})

# 5. Define Executable
add_executable(Super_Vision
     main.cpp
     src/ImageLoader.cpp
     src/Application.cpp
     src/CameraProcessor.cpp
     src/InferenceEngine.cpp
)

# 6. Link Libraries
target_link_libraries(Super_Vision
    ${OpenCV_LIBS}
    onnxruntime
)