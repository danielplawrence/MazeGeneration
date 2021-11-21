#include <doctest/doctest.h>
#include <mazegenerator/RecursiveBackTracker.h>

TEST_CASE("Recursive Backtracker") {
  auto grid = Grid::create(4, 4);
  auto grid2 = Grid::create(4, 4);
  auto result = RecursiveBackTracker().on(grid);
  CHECK(result->grid != grid2->grid);
}