# TODO 1: Add a library called MathFunctions
add_library(MathFunctions mysqrt.cxx ${CMAKE_CURRENT_BINARY_DIR}/Table.h )
#3-1
target_include_directories(MathFunctions
          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} )
#4-3
#link MathFunctions library to new tutorial_compiler_flags library
target_link_libraries(MathFunctions tutorial_compiler_flags)

# TODO 5-1: Create a variable called installable_libs that is a list of all libraries we want to install (e.g. MathFunctions and tutorial_compiler_flags) ,then install the installable libraries to the lib folder.
set(installable_libs MathFunctions tutorial_compiler_flags)
install(TARGETS ${installable_libs} DESTINATION lib)

# TODO 5-2: Install the library headers to the include folder.
install(FILES MathFunctions.h DESTINATION include)


#8-1: the executable for MakeTable 
add_executable(MakeTable MakeTable.cxx)

#8-2: specifies how to produce Table.h
add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Table.h
  COMMAND MakeTable ${CMAKE_CURRENT_BINARY_DIR}/Table.h
  DEPENDS MakeTable )

#8-3:to let CMake know that mysqrt.cxx depends on the generated file Table.h. This is done by adding the generated Table.h to the list of sources for the library MathFunctions.
#add_library(MathFunctions mysqrt.cxx ${CMAKE_CURRENT_BINARY_DIR}/Table.h )

#8-4: to add the current binary directory to the list of include directories so that Table.h can be found and included by mysqrt.cxx.
target_include_directories(MathFunctions
          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
          PRIVATE   ${CMAKE_CURRENT_BINARY_DIR} )

# link our compiler flags interface library
target_link_libraries(MathFunctions tutorial_compiler_flags)