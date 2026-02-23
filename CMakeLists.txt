cmake_minimum_required(VERSION 4.0.0)

set(PROJECT_NAME PlanetSimulator)
project(${PROJECT_NAME})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

find_package(OpenGL REQUIRED)


set(SRC 
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/base/GL/glad.c
    )

add_subdirectory(external/glfw)
    
add_executable(${PROJECT_NAME} ${SRC})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/external)


target_link_libraries(${PROJECT_NAME} glfw OpenGL::GL)



configure_file(${CMAKE_SOURCE_DIR}/Resources/sphere.model ${CMAKE_SOURCE_DIR}/bin/Resources/sphere.model COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/Resources/Shaders/default.vert ${CMAKE_SOURCE_DIR}/bin/Resources/Shaders/default.vert COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/Resources/Shaders/default.frag ${CMAKE_SOURCE_DIR}/bin/Resources/Shaders/default.frag COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/Resources/Shaders/instanced_default.frag ${CMAKE_SOURCE_DIR}/bin/Resources/Shaders/instanced_default.frag COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/Resources/Shaders/instanced_default.vert ${CMAKE_SOURCE_DIR}/bin/Resources/Shaders/instanced_default.vert COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/Resources/Textures/jp.jpg ${CMAKE_SOURCE_DIR}/bin/Resources/Textures/jp.jpg COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/Resources/Textures/ast.jpg ${CMAKE_SOURCE_DIR}/bin/Resources/Textures/ast.jpg COPYONLY)