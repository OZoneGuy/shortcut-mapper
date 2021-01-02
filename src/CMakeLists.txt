find_package(X11 REQUIRED)
link_libraries(${X11_LIBRARIES})
include_directories(${X11_INCLUDE_DIRS})

set(SOURCE key_mapper.cpp key_map_loader.cpp key_map_node.cpp utils.cpp)
add_executable(key_mapper ${SOURCE})
