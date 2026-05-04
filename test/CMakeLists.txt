# Create the test executable
add_executable(unit_tests testTemperatureSensor.cpp)

# Link against Catch2 and its default main()
target_link_libraries(unit_tests PRIVATE Catch2::Catch2WithMain)

# Automatic test discovery for CTest
include(Catch)
catch_discover_tests(unit_tests)
