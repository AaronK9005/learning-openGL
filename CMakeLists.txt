cmake_minimum_required(VERSION 4.4.3)
project(learning_opengl LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

find_package(glm 1.0.3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

add_subdirectory(thirdparty/glfw)

add_library(glad STATIC thirdparty/glad/src/gl.c)
target_include_directories(glad PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glad/include")

add_executable("${CMAKE_PROJECT_NAME}")

target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/")
target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC SHADERS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/shaders/")

target_sources("${CMAKE_PROJECT_NAME}" PRIVATE ${SRC_FILES})

target_include_directories("${CMAKE_PROJECT_NAME}" PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE
    glm::glm
    glfw
    glad
    OpenGL::GL
)