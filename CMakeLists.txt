cmake_minimum_required(VERSION 3.21.0)

# uncomment this if you're using `vcpkg` for MSVC
# 
set(CMAKE_TOOLCHAIN_FILE D:/vcpkg/scripts/buildsystems/vcpkg.cmake 
  CACHE STRING "Vcpkg toolchain file")

project(solar VERSION 0.2.0)

if(GNU OR MINGW)
set(CMAKE_CXX_STANDARD 17 REQUIRED)
add_compile_options(-std=gnu++17)
elseif(MSVC)
set(CMAKE_CXX_STANDARD 20 REQUIRED)
endif()

include(CTest)
enable_testing()

find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)

add_subdirectory(meshL)
add_subdirectory(scene_gl_utility)

add_executable(solar solar.cpp star.cpp)
target_link_libraries(solar PRIVATE OpenGL::GLU OpenGL::GL GLUT::GLUT mesh glScene)
target_precompile_headers(solar REUSE_FROM mesh)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
