#1
cmake_minimum_required(VERSION 3.10)
#2
project(Tutorial)
#3
add_executable(Tutorial tutorial.cxx)
#6
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
#7
project(Tutorial VERSION 1.0)
#8
configure_file(TutorialConfig.h.in TutorialConfig.h)
#9
target_include_directories(Tutorial PUBLIC "${PROJECT_BINARY_DIR}" )
#2-2
add_subdirectory(MathFunctions)
#2-3
target_link_libraries(Tutorial PUBLIC MathFunctions)
#2-4
target_include_directories(Tutorial PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/MathFunctions" )
