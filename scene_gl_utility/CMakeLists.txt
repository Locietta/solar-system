
find_package(OpenGL REQUIRED)

add_library(glScene light.cpp camera.cpp)
target_include_directories(
    glScene 
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE   ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(glScene PRIVATE OpenGL::GL GLUT::GLUT)
target_precompile_headers(glScene REUSE_FROM mesh)
