cmake_minimum_required(VERSION 3.10)
project(VulkanLearning)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
 
# packages
find_package(GLFW3 REQUIRED)
find_package(Vulkan REQUIRED)

# Include directories
include_directories(${GLFW_INCLUDE_DIR} ${Vulkan_INCLUDE_DIR})

# Link directories
link_directories(${GLFW_LIBRARY_DIR} ${Vulkan_LIBRARY_DIR})

# Define the source files
set(SOURCES main.cpp)

# Add the executable
add_executable(vulkan ${SOURCES})

# Link the libraries
target_link_libraries(vulkan glfw ${Vulkan_LIBRARIES} dl pthread)
