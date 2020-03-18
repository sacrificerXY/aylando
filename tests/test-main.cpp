#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

int factorial(int number) { return number <= 1 ? number : factorial(number - 1) * number; }

TEST_CASE("foo test") {
}
