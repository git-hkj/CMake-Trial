# TODO 1: Add a library called MathFunctions
add_library(MathFunctions mysqrt.cxx)
#3-1
target_include_directories(MathFunctions
          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} )
#4-3
##link MathFunctions library to new tutorial_compiler_flags library
target_link_libraries(MathFunctions tutorial_compiler_flags)