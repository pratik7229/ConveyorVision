cmake_minimum_required(VERSION 3.16)
project(Super_Vision)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

include_directories(${ONNXRUNTIME_ROOT_DIR}/include)
if(NOT DEFINED ONNXRUNTIME_ROOT_DIR)
    message(FATAL_ERROR "ONNXRUNTIME_ROOT_DIR is not set. Use -DONNXRUNTIME_ROOT_DIR=/path/to/ort")
endif()


include_directories(
    ${OpenCV_INCLUDE_DIRS}
    #/opt/homebrew/include
    ${CMAKE_SOURCE_DIR}/include
)

find_library(ONNXRUNTIME_LIB onnxruntime
    PATHS ${ONNXRUNTIME_ROOT_DIR}/lib
    NO_DEFAULT_PATH)

#link_directories(/opt/homebrew/lib)

add_executable(Super_Vision
     main.cpp
     src/ImageLoader.cpp
     src/Application.cpp
     src/CameraProcessor.cpp
     src/InferenceEngine.cpp
)

target_link_libraries(Super_Vision PRIVATE ${ONNXRUNTIME_LIB} opencv_core opencv_imgproc opencv_highgui)
# target_link_libraries(Super_Vision
#     ${OpenCV_LIBS}
#     onnxruntime
# )