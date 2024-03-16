# Generic test that uses conan libs
add_executable(toy view.cpp matrix4f.cpp ${PROJECT_SOURCE_DIR}/inc/view.hpp ${PROJECT_SOURCE_DIR}/inc/matrix4f.hpp)
target_link_libraries(
  toy PRIVATE project_options project_warnings ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})