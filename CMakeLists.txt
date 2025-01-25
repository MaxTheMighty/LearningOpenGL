cmake_minimum_required(VERSION 3.30)
project(Enviornment_Setup)

set(CMAKE_CXX_STANDARD 20)

add_executable(main
        main.cpp
        headers/Shader.h
        src/Shader.cpp)

# Add GLAD library as 'glad'
add_library(glad STATIC
        ${CMAKE_SOURCE_DIR}/external/glad/src/glad.c)

# Tell GLAD where to find its own headers (?)
target_include_directories(glad PRIVATE ${CMAKE_SOURCE_DIR}/external/glad/include)

# Link GLFW and GLAD headers to our project
target_include_directories(main PRIVATE
        ${CMAKE_SOURCE_DIR}/external/glfw/include/  #glfw headers
        ${CMAKE_SOURCE_DIR}/external/glad/include/  #glad headers
)

# Add GLFW library
target_link_libraries(main PRIVATE
        ${CMAKE_SOURCE_DIR}/external/glfw/lib/libglfw3.a
       glad
)

# On macOS, we need to link some additional frameworks
if(APPLE)
    target_link_libraries(main PRIVATE
            "-framework QuartzCore"
            "-framework Cocoa"
            "-framework IOKit"
            "-framework CoreFoundation"
    )
endif()
