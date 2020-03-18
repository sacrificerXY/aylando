#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <aylando/utils/Array2d.h>
using namespace aylando;

TEST_CASE("Array2d") {
    auto array = utils::Array2d<int, 3, 10>{};

    SUBCASE("size") {
        CHECK(array.width == 3);
        CHECK(array.height == 10);
    }

    SUBCASE("reset") {
        reset(array, 123);
        for (int i : array) {
            CHECK(i == 123);
        }
    }
}
