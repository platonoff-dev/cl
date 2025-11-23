cmake_minimum_required(VERSION 3.20)

project(cl
    VERSION 0.1.0
    DESCRIPTION "A programming language implementation in C"
    LANGUAGES C
)

# Set C23 standard (newest C standard)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Export compile_commands.json for IDE support
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set default build type to Release if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Compiler warnings and best practices
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
        -Werror
        -Wformat=2
        -Wformat-security
        -Wnull-dereference
        -Wstack-protector
        -fstack-protector-strong
        -fPIE
        $<$<CONFIG:Debug>:-O0>
        $<$<CONFIG:Debug>:-g3>
        $<$<CONFIG:Debug>:-ggdb>
        $<$<CONFIG:Release>:-O3>
    )
    add_link_options(
        -Wl,-z,relro
        -Wl,-z,now
        -Wl,-z,noexecstack
    )
elseif(MSVC)
    add_compile_options(
        /W4
        /WX
        /permissive-
        $<$<CONFIG:Debug>:/Od>
        $<$<CONFIG:Debug>:/Zi>
        $<$<CONFIG:Release>:/O2>
    )
endif()

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Source files
set(CL_SOURCES
    src/main.c
    src/lexer.c
    src/parser.c
    src/ast.c
    src/error.c
)

# Main executable
add_executable(cl ${CL_SOURCES})

# Link against math library on Unix-like systems
if(UNIX)
    target_link_libraries(cl m)
endif()

# Enable testing
enable_testing()

# Add tests subdirectory
add_subdirectory(tests)

# Installation
install(TARGETS cl DESTINATION bin)
