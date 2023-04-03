# TODO 4-4: Update the minimum required version to 3.15
cmake_minimum_required(VERSION 3.15)

# set the project name and version
project(Tutorial VERSION 1.0)

# should we use our own math functions
option(USE_MYMATH "Use tutorial provided math implementation" ON)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file(TutorialConfig.h.in TutorialConfig.h)

# add the MathFunctions library
if(USE_MYMATH)
  add_subdirectory(MathFunctions)
  list(APPEND EXTRA_LIBS MathFunctions)
endif()

# add the executable
add_executable(Tutorial tutorial.cxx)

#4-1 
#create an interface library, tutorial_compiler_flags and then 
add_library(tutorial_compiler_flags INTERFACE)
#use target_compile_features() to add the compiler feature cxx_std_11
target_compile_features(tutorial_compiler_flags INTERFACE cxx_std_11)
#4-2
#link executable Target to new tutorial_compiler_flags library
target_link_libraries(Tutorial PUBLIC ${EXTRA_LIBS} tutorial_compiler_flags)

# TODO 4-5: Create helper variables to determine which compiler we are using:
set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")

# TODO 4-6: Add warning flag compile options to the interface library tutorial_compiler_flags.
#target_compile_options( tutorial_compiler_flags INTERFACE "$<${gcc_like_cxx}:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>" "$<${msvc_cxx}:-W3>" )

# TODO 4-7: With nested generator expressions, only use the flags for the build-tree
# we only want these warning flags to be used during builds. Consumers of our installed project should not inherit our warning flags.
target_compile_options(
   tutorial_compiler_flags INTERFACE
  "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
  "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>" )



# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
target_include_directories(Tutorial PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )


# TODO 5-3: Install Tutorial in the bin directory
#install(TARGETS Tutorial DESTINATION bin)

# TODO 5-4: Install TutorialConfig.h to the include directory
#install(FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h" DESTINATION include )

# TODO 5: Enable testing

# TODO 6: Add a test called Runs which runs the following command:
# $ Tutorial 25

# TODO 7: Add a test called Usage which runs the following command:
# $ Tutorial
# Make sure the expected output is displayed.
# Hint: Use the PASS_REGULAR_EXPRESSION property with "Usage.*number"

# TODO 8: Add a test which runs the following command:
# $ Tutorial 4
# Make sure the result is correct.
# Hint: Use the PASS_REGULAR_EXPRESSION property with "4 is 2"

# TODO 9: Add more tests. Create a function called do_test to avoid copy +
# paste. Test the following values: 4, 9, 5, 7, 25, -25 and 0.0001.