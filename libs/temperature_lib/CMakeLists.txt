if(ENABLE_ASYNC)
    set(LIB_NAME async)
    set(LIB_SETTING SHARED)
else()
    set(LIB_NAME sync)
    set(LIB_SETTING STATIC)
endif()

add_library(temperature_lib ${LIB_SETTING} src/${LIB_NAME}/temperature.c)

if(ENABLE_COVERAGE)
    target_compile_options(temperature_lib PUBLIC --coverage -g -O0)
    target_link_options(temperature_lib PUBLIC --coverage)
endif()

target_include_directories(temperature_lib PUBLIC include)
target_link_libraries(temperature_lib PUBLIC buffer_lib)

if(ENABLE_TESTS)
    add_subdirectory(tests)
endif()
