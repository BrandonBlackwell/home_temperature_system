#include <catch2/catch_test_macros.hpp>

#include "rgbController.hpp"

TEST_CASE("RGBController tests") {
  // Set rgb_led color using the temp.
  // Temp dictates the zone
    RGBController rgb_led = RGBController();
    rgb_led.setColor(50);
    REQUIRE(rgb_led.zone == Zone::HOT);

    rgb_led.setColor(3);
    REQUIRE(rgb_led.zone == Zone::COLD);

    rgb_led.setColor(22);
    REQUIRE(rgb_led.zone == Zone::COMFORTABLE);

    rgb_led.setColor(26);
    REQUIRE(rgb_led.zone == Zone::WARM);
}