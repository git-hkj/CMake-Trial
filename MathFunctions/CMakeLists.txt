# TODO 1: Add a library called MathFunctions
add_library(MathFunctions MathFunctions.cxx)

#3-1: state that anybody linking  needs to include the current source dir to find MathFunctions.h
target_include_directories(MathFunctions
          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} )


# should we use our own math functions
option(USE_MYMATH "Use tutorial provided math implementation" ON)
if(USE_MYMATH)

  target_compile_definitions(MathFunctions PRIVATE "USE_MYMATH")

  # first we add the executable that generates the table
  add_executable(MakeTable MakeTable.cxx)
  target_link_libraries(MakeTable PRIVATE tutorial_compiler_flags)

  # add the command to generate the source code
  add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Table.h
    COMMAND MakeTable ${CMAKE_CURRENT_BINARY_DIR}/Table.h
    DEPENDS MakeTable
    )

  # library that just does sqrt
  add_library(SqrtLibrary STATIC
              mysqrt.cxx
              ${CMAKE_CURRENT_BINARY_DIR}/Table.h
              )

  # state that we depend on our binary dir to find Table.h
  target_include_directories(SqrtLibrary PRIVATE
                             ${CMAKE_CURRENT_BINARY_DIR}
                             )

  target_link_libraries(SqrtLibrary PUBLIC tutorial_compiler_flags)
  target_link_libraries(MathFunctions PRIVATE SqrtLibrary)
endif()


#4-3
#link MathFunctions library to new tutorial_compiler_flags library
target_link_libraries(MathFunctions PUBLIC tutorial_compiler_flags)

#10-1: define the symbol stating we are using the declspec(dllexport) when building on windows
target_compile_definitions(MathFunctions PRIVATE "EXPORTING_MYMATH")

#10-1: state that SqrtLibrary need PIC when the default is shared libraries
  set_target_properties(SqrtLibrary PROPERTIES
                        POSITION_INDEPENDENT_CODE ${BUILD_SHARED_LIBS}
                        )


# TODO 5-1: Create a variable called installable_libs that is a list of all libraries we want to install (e.g. MathFunctions and tutorial_compiler_flags) ,then install the installable libraries to the lib folder.
set(installable_libs MathFunctions tutorial_compiler_flags)
if(TARGET SqrtLibrary)
  list(APPEND installable_libs SqrtLibrary)
endif()
#11-1: explicitly EXPORT the MathFunctions library
install(TARGETS ${installable_libs}
        EXPORT MathFunctionsTargets
        DESTINATION lib)

install(TARGETS ${installable_libs} DESTINATION lib)

# TODO 5-2: Install the library headers to the include folder.
install(FILES MathFunctions.h DESTINATION include)
