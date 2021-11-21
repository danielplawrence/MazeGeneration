
#include <mazegenerator/AldousBroder.h>

GridPtr AldousBroder::on(GridPtr grid) {
  auto cell = grid->randomCell();
  auto unvisited = grid->size() - 1;
  while (unvisited > 0) {
    auto neighbor = randomElement(cell->neighbours.getAll());
    if (neighbor->getLinks().empty()) {
      cell->link(neighbor);
      unvisited--;
    }
    cell = neighbor;
  }
  return grid;
}
