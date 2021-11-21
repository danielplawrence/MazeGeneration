#include <doctest/doctest.h>
#include <mazegenerator/Wilson.h>

TEST_CASE("Wilson's algorithm") {
  auto grid = Grid::create(4, 4);
  auto grid2 = Grid::create(4, 4);
  auto result = Wilson().on(grid);
  CHECK(result->grid != grid2->grid);
}
