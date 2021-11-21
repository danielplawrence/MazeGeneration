#include <doctest/doctest.h>
#include <mazegenerator/Cell.h>
#include <mazegenerator/Distances.h>
#include <algorithm>

#include <vector>

TEST_CASE("Cell") {
  SUBCASE("A cell has a location") {
    auto cell1 = Cell::create(0, 0);
    std::pair<int, int> expectedLocation = {0, 0};
    CHECK(cell1->getLocation() == expectedLocation);
  }
  SUBCASE("A cell has a table of links") {
    auto cell1 = Cell::create(0, 0);
    CHECK(cell1->getLinks() == std::vector<std::shared_ptr<Cell>>());
  }
  SUBCASE("A cell can be linked to another unidirectionally") {
    auto cell1 = Cell::create(0, 0);
    auto cell2 = Cell::create(1, 1);
    cell1->link(cell2, false);
    CHECK(cell1->linkedTo(cell2));
    CHECK(!cell2->linkedTo(cell1));
    CHECK(std::find(cell1->getLinks().begin(), cell1->getLinks().end(), cell2)
          != cell1->getLinks().end());
    CHECK(std::find(cell2->getLinks().begin(), cell2->getLinks().end(), cell1)
          == cell2->getLinks().end());
  }
  SUBCASE("A cell can be linked to another bidirectionally") {
    auto cell1 = Cell::create(0, 0);
    auto cell2 = Cell::create(1, 1);
    cell1->link(cell2, true);
    CHECK(cell1->linkedTo(cell2));
    CHECK(cell2->linkedTo(cell1));
    CHECK(std::find(cell1->getLinks().begin(), cell1->getLinks().end(), cell2)
          != cell1->getLinks().end());
    CHECK(std::find(cell2->getLinks().begin(), cell2->getLinks().end(), cell1)
          != cell1->getLinks().end());
  }
  SUBCASE("A cell can list its neighbors") {
    auto cell = Cell::create(0, 0);
    auto cell2 = Cell::create(1, 1);
    cell->neighbours.north = cell2;
    cell->neighbours.south = cell2;
    cell->neighbours.east = cell2;
    cell->neighbours.west = cell2;
    auto res = cell->getNeighbors();
    CHECK(res.size() == 4);
  }
  SUBCASE("A cell returns an empty list for no neighbors") {
    auto cell = Cell::create(0, 0);
    auto res = cell->getNeighbors();
    CHECK(res.size() == 0);
  }
  SUBCASE("A cell returns its distances") {
    auto root = Cell::create(0, 0);
    auto firstNode = Cell::create(0, 0);
    auto secondNode = Cell::create(0, 0);
    auto thirdNode = Cell::create(0, 0);
    auto thirdNode2 = Cell::create(0, 0);
    secondNode->link(thirdNode);
    secondNode->link(thirdNode2);
    firstNode->link(secondNode);
    root->link(firstNode);
    auto distances = root->getDistances();
    CHECK(distances->get(thirdNode).value() == 3);
    CHECK(distances->get(thirdNode2).value() == 3);
    CHECK(distances->get(secondNode).value() == 2);
    CHECK(distances->get(firstNode).value() == 1);
    CHECK(distances->get(root).value() == 0);
  }
}