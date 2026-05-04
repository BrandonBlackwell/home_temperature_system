#include "catch2/catch_test_macros.hpp"

uint32_t factorial(uint32_t number) {
    return number <= 1 ? number : factorial(number - 1) * number;
}

TEST_CASE("factorial", "[math]") {
    REQUIRE(factorial(1) == 1);
    REQUIRE(factorial(5) == 120);
}