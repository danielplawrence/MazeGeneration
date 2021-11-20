#include <doctest/doctest.h>
#include <mazegenerator/Cell.h>
#include <mazegenerator/Distances.h>

TEST_CASE("Distances") {
  SUBCASE("Initializating a Distances instance") {
    auto cell = Cell::create(1, 1);
    auto distances = Distances(cell);
    auto firstCell = distances.getCells()[0];
    bool cellsMatch = cell == firstCell;
    CHECK(cellsMatch);
  }
  SUBCASE("Adding and retrieving a value") {
    auto cell = Cell::create(1, 1);
    auto cell2 = Cell::create(1, 1);
    auto distances = Distances(cell);
    distances.set(cell2, 10);
    CHECK(distances.get(cell2) == 10);
  }
  SUBCASE("Retrieving the value of a cell which hasn't been added") {
    auto cell = Cell::create(1, 1);
    auto cell2 = Cell::create(1, 1);
    auto distances = Distances(cell);
    CHECK(!distances.get(cell2).has_value());
  }
  SUBCASE("Listing all cells") {
    auto cell = Cell::create(1, 1);
    auto cell2 = Cell::create(1, 1);
    auto distances = Distances(cell);
    distances.set(cell2, 10);
    auto cells = distances.getCells();
    CHECK(cells.size() == 2);
  }
  SUBCASE("Finding the shortest path between two cells") {
    // A -> B
    // A -> C
    // B -> C
    // Shortest path from A to C is direct, not through B
    auto a = Cell::create(0, 1);
    auto b = Cell::create(0, 2);
    auto c = Cell::create(0, 3);
    a->link(b);
    a->link(c);
    b->link(c);
    auto distances = a->getDistances();
    auto pathResult = distances->pathTo(c);
    auto path = pathResult->getCells();
    auto pathZeroIsA = path[0] == a;
    auto pathOneIsC = path[1] == c;
    CHECK(pathZeroIsA);
    CHECK(pathOneIsC);
  }
}