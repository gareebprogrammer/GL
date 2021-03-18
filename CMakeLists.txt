cmake_minimum_required(VERSION 3.10)

project(gl)


add_subdirectory(external/glad)
add_subdirectory(external/glfw3)
find_package(OpenGL REQUIRED)


include_directories(include)

file(GLOB SOURCES
    src/window.cc
    src/main.cc
    )

add_executable(gl ${SOURCES} ${OPENGL_INCLUDE_DIRS})

target_link_libraries(gl glfw glad ${OPENGL_LIBRARIES} )


