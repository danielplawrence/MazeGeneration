#include <doctest/doctest.h>
#include <mazegenerator/Grid.h>

TEST_CASE("Grid") {
  SUBCASE("A grid contains row x columns cells") {
    auto grid = Grid(2, 2);
    CHECK(grid.get(0, 0)->getLocation() == std::pair<int, int>(0, 0));
    CHECK(grid.get(0, 1)->getLocation() == std::pair<int, int>(0, 1));
    CHECK(grid.get(1, 0)->getLocation() == std::pair<int, int>(1, 0));
    CHECK(grid.get(1, 1)->getLocation() == std::pair<int, int>(1, 1));
  }
  SUBCASE("Cells contain pointers to their neighbours") {
    auto grid = Grid(3, 3);
    auto middle = grid.get(1, 1);
    auto match1 = middle->neighbours.north == grid.get(0, 1);
    auto match2 = middle->neighbours.south == grid.get(2, 1);
    auto match3 = middle->neighbours.east == grid.get(1, 2);
    auto match4 = middle->neighbours.west == grid.get(1, 0);
    CHECK(match1);
    CHECK(match2);
    CHECK(match3);
    CHECK(match4);
  }
  SUBCASE("Out-of-range gets return a null pointer") {
    auto grid = Grid(3, 3);
    auto highRow = nullptr == grid.get(4, 1);
    auto highCol = nullptr == grid.get(0, 4);
    auto lowRow = nullptr == grid.get(-1, 1);
    auto lowCol = nullptr == grid.get(1, -1);
    CHECK(highRow);
    CHECK(highCol);
    CHECK(lowRow);
    CHECK(lowCol);
  }
  SUBCASE("A grid has a size") {
    auto grid = Grid(3, 3);
    CHECK(grid.size() == 9);
  }
  SUBCASE("A grid can return a random cell") {
    auto grid = Grid(3, 3);
    CHECK(typeid(grid.randomCell()) == typeid(Cell::create(0, 0)));
  }
  SUBCASE("A grid can list its dead ends") {
    auto grid = Grid(3, 3);
    auto first = grid.get(0, 0);
    auto second = grid.get(1, 0);
    first->link(second);
    CHECK(grid.deadEnds().size() == 2);
  }
  SUBCASE("Converting a grid to a ppm string") {
    auto grid = Grid(3, 3);
    auto res = grid.toPortablePixmap(2);
    auto expected
        = "P3\n"
          "7 7\n"
          "255\n"
          "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
          "0 0 0 255 255 255 0 0 0 255 255 255 0 0 0 255 255 255 0 0 0\n"
          "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
          "0 0 0 255 255 255 0 0 0 255 255 255 0 0 0 255 255 255 0 0 0\n"
          "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
          "0 0 0 255 255 255 0 0 0 255 255 255 0 0 0 255 255 255 0 0 0\n"
          "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n";
    CHECK(res == expected);
  }
}