# TODO 1: Add a library called MathFunctions
add_library(MathFunctions mysqrt.cxx)
#3-1
target_include_directories(MathFunctions
          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} )
#4-3
#link MathFunctions library to new tutorial_compiler_flags library
target_link_libraries(MathFunctions tutorial_compiler_flags)

# TODO 5-1: Create a variable called installable_libs that is a list of all libraries we want to install (e.g. MathFunctions and tutorial_compiler_flags) ,then install the installable libraries to the lib folder.
#set(installable_libs MathFunctions tutorial_compiler_flags)
#install(TARGETS ${installable_libs} DESTINATION lib)

# TODO 5-2: Install the library headers to the include folder.
#install(FILES MathFunctions.h DESTINATION include)
