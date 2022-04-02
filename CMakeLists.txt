cmake_minimum_required(VERSION 3.18)

project(task2)

option(ENABLE_ASYNC "ENABLE ASYNC" OFF)
option(ENABLE_SANITIZERS "ENABLE_SANITIZERS" OFF)
option(ENABLE_TESTS "ENABLE_TESTS" OFF)
option(ENABLE_COVERAGE "ENABLE_COVERAGE" OFF)

add_compile_options(-Wpedantic -Wall -Werror -Wextra -Wshadow)

if(ENABLE_ASYNC)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()

if(ENABLE_SANITIZERS)
    message(STATUS "Adding Sanitizers")
    add_compile_options(-fsanitize=address
            -fsanitize=undefined
            -fno-sanitize-recover=all
            -fsanitize-undefined-trap-on-error)
    add_link_options(-fsanitize=address
            -fsanitize=undefined
            -fno-sanitize-recover=all
            -fsanitize-undefined-trap-on-error)
endif()

if(ENABLE_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})
endif()

add_subdirectory(libs/temperature_lib)
add_subdirectory(libs/buffer_lib)

add_executable(${PROJECT_NAME} src/main.c)
target_link_libraries(${PROJECT_NAME} temperature_lib)
