#include <mazegenerator/DistanceGrid.h>

#include <fstream>
#include <iostream>

#include "mazegenerator/BinaryTree.h"
#include "mazegenerator/Grid.h"
#include "mazegenerator/Sidewinder.h"

auto main(int argc, char** argv) -> int {
  (void)argc;
  (void)argv;

  auto grid = DistanceGrid::create(30, 30);
  grid = Sidewinder::on(grid);

  std::ofstream out("grid.ppm");
  out << grid->toPortablePixmap(50);
  out.close();

  auto dGrid = std::dynamic_pointer_cast<DistanceGrid>(grid);
  auto start = dGrid->get(0, 0);
  auto distances = start->getDistances();
  dGrid->setDistances(distances->pathTo(grid->get(15, 15)));

  std::ofstream out2("grid_solution.ppm");
  out2 << dGrid->toPortablePixmap(50);
  out2.close();

  return 0;
}
