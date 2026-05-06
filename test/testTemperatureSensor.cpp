#include "catch2/catch_test_macros.hpp"
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "../src/temperatureSensor.hpp"

TEST_CASE("TemperatureSensor", "[sensor]") {
    TemperatureSensor sensor(3950, 10000, 5.0, 298.15);
    REQUIRE_THAT(
        sensor.getTemperatureCelsius(1023), 
        Catch::Matchers::WithinAbs(25.0, 0.1)
    );
}