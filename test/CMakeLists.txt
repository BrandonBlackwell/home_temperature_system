# Create the test executable
add_executable(
    unit_tests 
    testTemperatureSensor.cpp
    testRGBController.cpp
)

# Link against the temperature_sensor library and Catch2
target_link_libraries(
    unit_tests 
    PRIVATE 
    temperature_sensor
    rgb_controller
    Catch2::Catch2WithMain
)

# Automatic test discovery for CTest
include(Catch)
catch_discover_tests(unit_tests)
