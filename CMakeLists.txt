cmake_minimum_required(VERSION 3.17)
project(2)

set(CMAKE_CXX_STANDARD 14)
find_package(GLEW 2.0 REQUIRED)


find_package( glm REQUIRED )

find_package(GLUT REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})


add_executable(2
        glad/include/glad/glad.h
        main_Cut.cpp
        glm/glm/glm.hpp
        glm/glm/gtc/matrix_transform.hpp
        glm/glm/gtc/type_ptr.hpp
        figures/Squres.h figures/Tringle2D.h Camera.h)

if (APPLE)
    target_link_libraries(2 ${GLEW_LIBRARY})
    target_link_libraries(2 "-framework GLUT")
    target_link_libraries(2 "-framework OpenGL")
endif ()
target_link_libraries(2 glfw)
target_link_libraries(2 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
target_link_libraries(2 OpenGL::GL)

target_link_libraries(2 glfw ${GLEW_LIBRARIES})