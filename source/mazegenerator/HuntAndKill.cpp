
#include <mazegenerator/HuntAndKill.h>

#include <algorithm>
#include <iterator>

GridPtr HuntAndKill::on(GridPtr grid) {
  auto current = grid->randomCell();
  while (current != nullptr) {
    auto neighbors = current->getNeighbors();
    std::vector<CellPtr> unvisited;
    std::copy_if(neighbors.begin(), neighbors.end(), std::back_inserter(unvisited),
                 [](const CellPtr& n) { return n->getLinks().empty(); });
    if (!unvisited.empty()) {
      auto neighbor = randomElement(unvisited);
      current->link(neighbor);
      current = neighbor;
    } else {
      current = nullptr;
    }
    for (const auto& cell : grid->cells()) {
      std::vector<CellPtr> visited;
      auto neighbors1 = cell->getNeighbors();
      std::copy_if(neighbors1.begin(), neighbors1.end(), std::back_inserter(visited),
                   [](const CellPtr& n) { return !n->getLinks().empty(); });
      if (cell->getLinks().empty() && !visited.empty()) {
        current = cell;
        auto neighbor1 = randomElement(visited);
        current->link(neighbor1);
        break;
      }
    }
  }
  return grid;
}
