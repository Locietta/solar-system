cmake_minimum_required(VERSION 3.21.0)

# if you're using `vcpkg` to resolve dependencies
# please set `toolchainFile` to path-to-vcpkg\\scripts\\buildsystems\\vcpkg.cmake for presets in your cmake-tools-kits.json

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
find_package(OpenCV CONFIG REQUIRED)

add_subdirectory(meshL)
add_subdirectory(scene_gl_utility)

add_executable(solar solar.cpp star.cpp)
target_link_libraries(solar PRIVATE OpenGL::GLU OpenGL::GL GLUT::GLUT mesh glScene ${OpenCV_LIBRARIES})
target_precompile_headers(solar PRIVATE ${solar_SOURCE_DIR}/pch/pch.h)

add_custom_command(TARGET solar POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:solar> $<TARGET_FILE_DIR:solar>
  COMMAND_EXPAND_LISTS
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
