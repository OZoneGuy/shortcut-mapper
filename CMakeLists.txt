cmake_minimum_required(VERSION 3.17)
project(key-mapper VERSION 0.1)

# ############################ Set up 'clip' library #############################

# # Disable clip examples and tests
# set(CLIP_EXAMPLES OFF CACHE BOOL "Compile clip examples")
# set(CLIP_TESTS OFF CACHE BOOL "Compile clip tests")

# # In case that you have ${PNG_LIBRARY} set to support copy/paste images on Linux
# #set(CLIP_X11_PNG_LIBRARY "${PNG_LIBRARY}")

# # Add clip subdirectory to compile the library
# add_subdirectory(clip)

################################ Project files #################################
find_package(X11 REQUIRED)
link_libraries(${X11_LIBRARIES})
include_directories(${X11_INCLUDE_DIRS})

set(SOURCE src/key_mapper.cpp src/key_map_loader.cpp src/key_map_node.cpp src/utils.cpp)
add_executable(key-mapper ${SOURCE})
