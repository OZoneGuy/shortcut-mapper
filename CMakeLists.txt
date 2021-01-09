cmake_minimum_required(VERSION 3.17)
project(shortcut-mapper VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

################################ Project files #################################
find_package(X11 REQUIRED)
link_libraries(${X11_LIBRARIES})
include_directories(${X11_INCLUDE_DIRS})

set(SOURCE src/key_mapper.cpp src/key_map_loader.cpp src/key_map_node.cpp src/utils.cpp)
add_executable(${PROJECT_NAME} ${SOURCE})

install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION /bin/)

install(FILES template/key-map
  DESTINATION /usr/share/shortcut-mapper/key-map)
