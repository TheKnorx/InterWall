cmake_minimum_required(VERSION 3.16)
set (CMAKE_CXX_STANDARD 23)  # this could work with c11, but to be sure we only support c23 and above
project(InterWall LANGUAGES C)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# This assumes the SDL source is available in vendored/SDL
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

# Create your executable target as usual
add_executable(main src/main.c src/window.c src/animation.c)

# Link to the actual SDL3 library.
target_link_libraries(main PRIVATE SDL3::SDL3 m)