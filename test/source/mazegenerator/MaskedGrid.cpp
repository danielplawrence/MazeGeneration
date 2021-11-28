#include <doctest/doctest.h>
#include <mazegenerator/MaskedGrid.h>

TEST_CASE("Masked grid") {
  SUBCASE("A masked grid turns off masked cells") {
    auto mask = Mask(5, 5);
    mask.set(0, 0, false);
    mask.set(2, 2, false);
    mask.set(4, 4, false);
    auto grid = MaskedGrid::create(mask);
    auto zerozero = grid->get(0, 0) == nullptr;
    auto twotwo = grid->get(2, 2) == nullptr;
    auto fourfour = grid->get(4, 4) == nullptr;
    CHECK(zerozero);
    CHECK(twotwo);
    CHECK(fourfour);
  }
}