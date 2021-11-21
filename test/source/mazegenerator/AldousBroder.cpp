#include <doctest/doctest.h>
#include <mazegenerator/AldousBroder.h>

TEST_CASE("Aldous-Broder") {
  auto grid = Grid::create(4, 4);
  auto grid2 = Grid::create(4, 4);
  auto result = AldousBroder().on(grid);
  CHECK(result->grid != grid2->grid);
}