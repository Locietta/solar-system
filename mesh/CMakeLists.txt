
find_package(OpenGL REQUIRED)
find_package(OpenCV REQUIRED)

add_library(mesh mesh.cpp material.cpp)
target_include_directories(
    mesh 
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE   ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(mesh PRIVATE OpenGL::GL OpenGL::GLU GLUT::GLUT ${OpenCV_LIBRARIES})
target_precompile_headers(mesh PUBLIC ${PROJECT_SOURCE_DIR}/pch/pch.h)

add_executable(test_obj test_obj.cpp)
target_link_libraries(test_obj mesh)