cmake_minimum_required(VERSION 3.27)
project(renderer)
# Set C++ standard
set(CMAKE_CXX_STANDARD 20)

# Find GLFW package
find_package(glfw3 3.3 REQUIRED)
# Find GLEW package
find_package(GLEW REQUIRED)
# Find OpenGL manually
find_package(OpenGL REQUIRED)
# Find GLM package
find_package(glm REQUIRED)

# Add executable
add_executable(renderer main.cpp)
# Add list of source files
file(GLOB_RECURSE SOURCE_FILES
    "include/**/*.h"
    "source/**/*.cpp"
)
target_sources(renderer PRIVATE ${SOURCE_FILES})

# Link libraries
target_link_libraries(renderer PRIVATE ${OPENGL_LIBRARIES} glfw GLEW::GLEW glm::glm)
# Include directories
target_include_directories(renderer PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${OPENGL_INCLUDE_DIR}
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/source>
    $<INSTALL_INTERFACE:source>
)


