#include <mazegenerator/BinaryTree.h>
#include <mazegenerator/Grid.h>

GridPtr BinaryTree::on(GridPtr grid) {
  for (auto& cell : grid->cells()) {
    std::vector<std::shared_ptr<Cell>> neighbours;
    if (cell->neighbours.north != nullptr) {
      neighbours.emplace_back(cell->neighbours.north);
    }
    if (cell->neighbours.east != nullptr) {
      neighbours.emplace_back(cell->neighbours.east);
    }
    if (!neighbours.empty()) {
      auto neighbour = randomElement(neighbours);
      if (neighbour != nullptr) {
        cell->link(neighbour);
      }
    }
  }
  return grid;
}
