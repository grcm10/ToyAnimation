cmake_minimum_required(VERSION 3.15)

set(project_name ToyAnimation)
project(${project_name} CXX)
set(CMAKE_BUILD_TYPE Debug )

add_library(project_warnings INTERFACE)
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_20)

set(WARNINGS
    -Wall
    -Wextra # reasonable and standard
    -Wshadow # warn the user if a variable declaration shadows one from a parent context
    -Wnon-virtual-dtor # warn the user if a class with virtual functions has a non-virtual destructor. This helps
                    # catch hard to track down memory errors
    -Wold-style-cast # warn for c-style casts
    -Wcast-align # warn for potential performance problem casts
    -Wunused # warn on anything being unused
    -Woverloaded-virtual # warn if you overload (not override) a virtual function
    -Wpedantic # warn if non-standard C++ is used
    -Wconversion # warn on type conversions that may lose data
    -Wsign-conversion # warn on sign conversions
    -Wnull-dereference # warn if a null dereference is detected
    -Wdouble-promotion # warn if float is implicit promoted to double
    -Wformat=2 # warn on security issues around functions that format output (ie printf)
    -Wmisleading-indentation # warn if indentation implies blocks where blocks do not exist
    -Wduplicated-cond # warn if if / else chain has duplicated conditions
    -Wduplicated-branches # warn if if / else branches have duplicated code
    -Wlogical-op # warn about logical operations being used where bitwise were probably wanted
    -Wuseless-cast # warn if you perform a cast to the same type
  ) 

target_compile_options(project_warnings INTERFACE ${WARNINGS})

set(LIST_OF_SANITIZERS "leak,address,undefined")

# TODO: disable for now, not sure why using freeglut will have memory leak.
#target_compile_options(project_options INTERFACE -fsanitize=${LIST_OF_SANITIZERS})
#target_link_options(project_options INTERFACE -fsanitize=${LIST_OF_SANITIZERS})

set(DOXYGEN_CALLER_GRAPH YES)
set(DOXYGEN_CALL_GRAPH YES)
set(DOXYGEN_EXTRACT_ALL YES)
find_package(Doxygen REQUIRED OPTIONAL_COMPONENTS dot)
doxygen_add_docs(doxygen-docs ${PROJECT_SOURCE_DIR})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )


enable_testing()
  message(
    "Building Tests."
  )
add_subdirectory(test)
add_subdirectory(src)