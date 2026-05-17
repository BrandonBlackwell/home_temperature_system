#include <catch2/catch_test_macros.hpp>

#include "rgbController.hpp"

TEST_CASE("RGBController tests") {
  RGBController rgb_led = RGBController(1, 2, 3);

  // Pins are set as expected
  REQUIRE(rgb_led.red_pin == 1);
  REQUIRE(rgb_led.green_pin == 2);
  REQUIRE(rgb_led.blue_pin == 3);
  // Set rgb_led color using the temp.
  // Temp dictates the zone
    
  rgb_led.setColor(50);
  REQUIRE(rgb_led.zone == Zone::HOT);

  rgb_led.setColor(3);
  REQUIRE(rgb_led.zone == Zone::COLD);

  rgb_led.setColor(22);
  REQUIRE(rgb_led.zone == Zone::COMFORTABLE);

  rgb_led.setColor(26);
  REQUIRE(rgb_led.zone == Zone::WARM);
}

TEST_CASE("Color percentage tests") {
  /*
    Based on a temperature and temperature thresholds, 
    divvy up a percentage to red, green, or blue.
    Example:
      temp = 20°C
      temp < 22°C == COLD
      apply_cold_percentage(r, g, b)
      r = 0% of 255
      g = 20% of 255
      b = 80% of 255
  */
  RGBController rgb_led = RGBController();

  // Pins are defaulted when not provided
  REQUIRE(rgb_led.red_pin == 9);
  REQUIRE(rgb_led.green_pin == 10);
  REQUIRE(rgb_led.blue_pin == 11);

  rgb_led.setColor(20);
  // assert that the blue pin has 90% of the brightness since the temp falls in the cold threshold
  REQUIRE(rgb_led.red == 0);
  REQUIRE(rgb_led.green == 25.5f);
  REQUIRE(rgb_led.blue == 229.5f);
}