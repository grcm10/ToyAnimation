# Generic test that uses conan libs
file(GLOB SRCS *.cpp  ${PROJECT_SOURCE_DIR}/inc/*.hpp )
add_executable(toy ${SRCS})
target_link_libraries(
  toy PRIVATE project_options project_warnings ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})