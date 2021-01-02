cmake_minimum_required(VERSION 3.17)
project(kay-mapper VERSION 0.1)

# ############################ Set up 'clip' library #############################

# # Disable clip examples and tests
# set(CLIP_EXAMPLES OFF CACHE BOOL "Compile clip examples")
# set(CLIP_TESTS OFF CACHE BOOL "Compile clip tests")

# # In case that you have ${PNG_LIBRARY} set to support copy/paste images on Linux
# #set(CLIP_X11_PNG_LIBRARY "${PNG_LIBRARY}")

# # Add clip subdirectory to compile the library
# add_subdirectory(clip)

################################ Project files #################################
add_subdirectory(src)

# add_subdirectory(tests)
