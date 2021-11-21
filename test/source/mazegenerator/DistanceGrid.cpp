#include <doctest/doctest.h>
#include <mazegenerator/DistanceGrid.h>

TEST_CASE("DistanceGrid") {
  SUBCASE("Returning cell contents when no distances have been set") {
    auto distanceGrid = DistanceGrid::create(5, 5);
    auto val = distanceGrid->contentsOf(distanceGrid->get(0, 0), 1);
    CHECK(std::get<4>(val) == Color{0.0, 0.0, 0.0});
    CHECK(std::get<3>(val) == 0);
    CHECK(std::get<2>(val) == 0);
    CHECK(std::get<1>(val) == 0);
    CHECK(std::get<0>(val) == 0);
  }
  SUBCASE("The returned cell respects cellSize") {
    auto distanceGrid = DistanceGrid::create(5, 5);
    auto root = distanceGrid->get(0, 0);
    auto second = distanceGrid->get(1, 1);
    root->link(second);
    auto d = std::dynamic_pointer_cast<DistanceGrid>(distanceGrid);
    d->setDistances(d->get(0, 0)->getDistances());
    auto val = distanceGrid->contentsOf(distanceGrid->get(1, 1), 2);
    CHECK(std::get<3>(val) == 4);
    CHECK(std::get<2>(val) == 4);
    CHECK(std::get<1>(val) == 2);
    CHECK(std::get<0>(val) == 2);
  }
  SUBCASE("The returned cell is colored based on its distance from root") {
    auto distanceGrid = DistanceGrid::create(5, 5);
    auto root = distanceGrid->get(0, 0);
    auto second = distanceGrid->get(1, 1);
    auto third = distanceGrid->get(1, 0);
    second->link(third);
    root->link(second);
    auto d = std::dynamic_pointer_cast<DistanceGrid>(distanceGrid);
    d->setDistances(root->getDistances());
    auto thirdVal = distanceGrid->contentsOf(third, 1);
    auto secondVal = distanceGrid->contentsOf(second, 1);
    auto rootVal = distanceGrid->contentsOf(root, 1);
    CHECK(rootVal == std::tuple<int, int, int, int, Color>(0, 0, 1, 1, {1.0, 0.5, 0.5}));
    CHECK(secondVal == std::tuple<int, int, int, int, Color>(1, 1, 2, 2, {0.5, 0.25, 0.25}));
    CHECK(thirdVal == std::tuple<int, int, int, int, Color>(0, 1, 1, 2, {0, 0, 0}));
  }
  SUBCASE("The case where there is no path to the target cell") {
    auto distanceGrid = DistanceGrid::create(5, 5);
    auto root = distanceGrid->get(0, 0);
    auto second = distanceGrid->get(1, 1);
    auto d = std::dynamic_pointer_cast<DistanceGrid>(distanceGrid);
    d->setDistances(root->getDistances());
    auto val = distanceGrid->contentsOf(second, 1);
    CHECK(val == std::tuple<int, int, int, int, Color>(0, 0, 0, 0, {0.0, 0.0, 0.0}));
  }
}