# TODO 1: Add a library called MathFunctions
add_library(MathFunctions mysqrt.cxx)
#3-1
target_include_directories(MathFunctions
          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} )