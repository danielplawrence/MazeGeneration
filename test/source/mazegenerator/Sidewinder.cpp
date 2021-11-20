#include <doctest/doctest.h>
#include <mazegenerator/Sidewinder.h>

TEST_CASE("Sidewinder") {
  auto grid = Grid::create(4, 4);
  auto grid2 = Grid::create(4, 4);
  auto result = Sidewinder::on(grid);
  CHECK(result->grid != grid2->grid);
}
