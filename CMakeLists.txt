cmake_minimum_required(VERSION 3.10)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build)

get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${PROJECT_NAME})

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_library(glad external/src/glad.c)
target_include_directories(glad PUBLIC external/include/glad)

include_directories(${CMAKE_SOURCE_DIR}/external/include)
link_directories(${CMAKE_SOURCE_DIR}/external/lib)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
   PRIVATE
      glad
      glfw3
      opengl32
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_SOURCE_DIR}/external/lib/glfw3.dll"
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
)
