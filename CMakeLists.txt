cmake_minimum_required(VERSION 3.17)
project(shortcut-mapper VERSION 0.1)

################################ Project files #################################
find_package(X11 REQUIRED)
link_libraries(${X11_LIBRARIES})
include_directories(${X11_INCLUDE_DIRS})

set(SOURCE src/key_mapper.cpp src/key_map_loader.cpp src/key_map_node.cpp src/utils.cpp)
add_executable(${PROJECT_NAME} ${SOURCE})
