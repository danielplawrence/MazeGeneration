#include <doctest/doctest.h>
#include <mazegenerator/BinaryTree.h>

TEST_CASE("Binary tree") {
  auto grid = Grid::create(4, 4);
  auto grid2 = Grid::create(4, 4);
  auto result = BinaryTree::on(grid);
  CHECK(result->grid != grid2->grid);
}
