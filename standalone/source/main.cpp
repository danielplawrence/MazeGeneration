
#include <mazegenerator/BinaryTree.h>
#include <mazegenerator/DistanceGrid.h>
#include <mazegenerator/HuntAndKill.h>
#include <mazegenerator/Wilson.h>

#include <fstream>
#include <iostream>

#include "mazegenerator/Grid.h"

auto main(int argc, char** argv) -> int {
  (void)argc;
  (void)argv;

  auto grid = DistanceGrid::create(30, 30);
  grid = HuntAndKill().on(grid);

  std::ofstream out("grid.ppm");
  out << grid->toPortablePixmap(50);
  out.close();

  auto dGrid = std::dynamic_pointer_cast<DistanceGrid>(grid);
  auto start = dGrid->get(15, 15);
  dGrid->setDistances(start->getDistances());

  std::ofstream out2("grid_distances.ppm");
  out2 << dGrid->toPortablePixmap(50);
  out2.close();

  return 0;
}
