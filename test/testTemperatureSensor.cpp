#include "catch2/catch_test_macros.hpp"
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "temperatureSensor.hpp"

TEST_CASE("TemperatureSensor", "[sensor]") {
    TemperatureSensor sensor(3950.0f, 10'000.0f, 4095.0f, 298.15f);

    float rawADC = 0; // Example of bad raw ADC value
    REQUIRE(std::isnan(sensor.getTemperatureCelsius(rawADC)));
    REQUIRE(std::isnan(sensor.getTemperatureFahrenheit(rawADC)));

    rawADC = 4095; // Example of bad raw ADC value
    REQUIRE(std::isnan(sensor.getTemperatureCelsius(rawADC)));
    REQUIRE(std::isnan(sensor.getTemperatureFahrenheit(rawADC)));

    rawADC = 1960.0f; // Example of good raw ADC value
    REQUIRE_THAT(
        sensor.getTemperatureCelsius(rawADC), 
        Catch::Matchers::WithinRel(23.0, 0.1)
    );
    REQUIRE_THAT(
        sensor.getTemperatureFahrenheit(rawADC), 
        Catch::Matchers::WithinRel(73.5, 0.1)
    );
}