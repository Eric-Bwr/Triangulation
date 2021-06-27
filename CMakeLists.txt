cmake_minimum_required(VERSION 3.2)
project(Triangulation)

SET(CMAKE_EXE_LINKER_FLAGS "-v")

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCE_FILES "Triangulation/*.cpp" "Triangulation/*.h")

set(dir ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(Dependencies)

include_directories(${PROJECT_NAME} "Dependencies/OpenGL/include")
include_directories(${PROJECT_NAME} "Dependencies/Math/include")

include_directories(${PROJECT_NAME})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME}
        ${CMAKE_CURRENT_LIST_DIR}/Dependencies/OpenGL/OpenGL.a
        ${CMAKE_CURRENT_LIST_DIR}/Dependencies/Math/Math.a
        opengl32.lib
        )