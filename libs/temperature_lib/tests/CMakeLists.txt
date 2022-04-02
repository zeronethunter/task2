add_executable(temperature_test temperature_test.cpp)
target_link_libraries(temperature_test temperature_lib GTest::Main)
add_test(NAME temperature_test
        COMMAND temperature_test)
