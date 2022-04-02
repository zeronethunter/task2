add_library(buffer_lib src/buffer.c)

if(ENABLE_COVERAGE)
    target_compile_options(buffer_lib PUBLIC -fprofile-arcs -ftest-coverage -O0)
    target_link_options(buffer_lib PUBLIC -coverage -lgcov)
endif()

target_include_directories(buffer_lib PUBLIC include)

if(ENABLE_TESTS)
    add_subdirectory(tests)
endif()
