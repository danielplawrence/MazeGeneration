#include <doctest/doctest.h>
#include <mazegenerator/HuntAndKill.h>

TEST_CASE("Hunt and kill") {
  auto grid = Grid::create(4, 4);
  auto grid2 = Grid::create(4, 4);
  auto result = HuntAndKill().on(grid);
  CHECK(result->grid != grid2->grid);
}