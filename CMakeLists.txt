# TODO 4-4: Update the minimum required version to 3.15
cmake_minimum_required(VERSION 3.15)

# set the project name and version
project(Tutorial VERSION 1.0)

#4-1 
#create an interface library, tutorial_compiler_flags and then 
add_library(tutorial_compiler_flags INTERFACE)
#use target_compile_features() to add the compiler feature cxx_std_11
target_compile_features(tutorial_compiler_flags INTERFACE cxx_std_11)

# TODO 4-5: Create helper variables to determine which compiler we are using:
set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")

# TODO 4-7: With nested generator expressions, only use the flags for the build-tree
# we only want these warning flags to be used during builds. Consumers of our installed project should not inherit our warning flags.
target_compile_options(
   tutorial_compiler_flags INTERFACE
  "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
  "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>" )


#10-1: to control the default behavior of add_library(), and allow control over how libraries without an explicit type (STATIC, SHARED, MODULE or OBJECT) are built.
# control where the static and shared libraries are built so that on windows
# we don't need to tinker with the path to run the executable
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)


# configure a header file to pass some of the CMake settings
# to the source code
configure_file(TutorialConfig.h.in TutorialConfig.h)

#10-1:  add the MathFunctions library
add_subdirectory(MathFunctions)

# add the executable
add_executable(Tutorial tutorial.cxx)

#4-2
#link executable Target to new tutorial_compiler_flags library
target_link_libraries(Tutorial PUBLIC MathFunctions tutorial_compiler_flags)

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
target_include_directories(Tutorial PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )














# TODO 5-3: Install Tutorial in the bin directory
install(TARGETS Tutorial DESTINATION bin)

# TODO 5-4: Install TutorialConfig.h to the include directory
install(FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h" DESTINATION include )

#11-1: explicitly install the generated MathFunctionsTargets.cmake file
install(EXPORT MathFunctionsTargets
  FILE MathFunctionsTargets.cmake
  DESTINATION lib/cmake/MathFunctions
)
#11-3: Helpers functions for creating config files that can be included by other projects to find and use a package.
include(CMakePackageConfigHelpers)

#11-4:to generate the config file that includes the exports
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/MathFunctionsConfig.cmake"
  INSTALL_DESTINATION "lib/cmake/example"
  NO_SET_AND_CHECK_MACRO
  NO_CHECK_REQUIRED_COMPONENTS_MACRO
  )

#11-5: writes a file which is used by find_package(), documenting the version and compatibility of the desired package
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/MathFunctionsConfigVersion.cmake"
  VERSION "${Tutorial_VERSION_MAJOR}.${Tutorial_VERSION_MINOR}"
  COMPATIBILITY AnyNewerVersion
)

#11-6: set both generated files to be installed
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/MathFunctionsConfig.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/MathFunctionsConfigVersion.cmake
  DESTINATION lib/cmake/MathFunctions
  )


  #11-7:to make is usable from a build directory
  export(EXPORT MathFunctionsTargets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/MathFunctionsTargets.cmake" )

















# TODO 5-5: Enable testing
enable_testing()

# TODO 5-6: Add a test called Runs which runs the following command:
add_test(NAME Runs COMMAND Tutorial 25)

# TODO 5-7: Add a test called Usage which use the PASS_REGULAR_EXPRESSION test property to verify that the output of the test contains certain strings
add_test(NAME Usage COMMAND Tutorial)
set_tests_properties(Usage  PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.*number"  )

# TODO 5-8: Add a test which runs and verifies the computed value is truly the square root.
add_test(NAME StandardUse COMMAND Tutorial 4)
set_tests_properties(StandardUse   PROPERTIES PASS_REGULAR_EXPRESSION "4 is 2"  )

# TODO 9: Add more tests. Create a function called do_test that runs the application and verifies that the computed square root is correct for given input.
function(do_test target arg result)
  add_test(NAME Comp${arg} COMMAND ${target} ${arg})
  set_tests_properties(Comp${arg}
    PROPERTIES PASS_REGULAR_EXPRESSION ${result}
    )
endfunction()

# do a bunch of result based tests
do_test(Tutorial 4 "4 is 2")
do_test(Tutorial 9 "9 is 3")
do_test(Tutorial 5 "5 is 2.236")
do_test(Tutorial 7 "7 is 2.645")
do_test(Tutorial 25 "25 is 5")
do_test(Tutorial -25 "-25 is (-nan|nan|0)")
do_test(Tutorial 0.0001 "0.0001 is 0.01")

#TODO Step 6
#to enable dashboard submissions to CDash by including the CTest
include(CTest)


#9-1:use CPack to create platform specific installers
#To search for compiler-provided system runtime libraries and add install rules for them
include(InstallRequiredSystemLibraries)
#To set some CPack variables to where we have stored the license
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
#To set some CPack variables to where we have stored the version information for this project
set(CPACK_PACKAGE_VERSION_MAJOR "${Tutorial_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${Tutorial_VERSION_MINOR}")
#To select a file format for the source package
set(CPACK_SOURCE_GENERATOR "TGZ")
#Include the CPack module which will use these variables and some other properties of the current system to setup an installer.
include(CPack)