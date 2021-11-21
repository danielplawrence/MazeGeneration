#include <mazegenerator/Wilson.h>

GridPtr Wilson::on(GridPtr grid) {
  auto unVisited = std::vector<CellPtr>(grid->cells());
  auto first = randomElement(unVisited);
  unVisited.erase(std::remove(unVisited.begin(), unVisited.end(), first), unVisited.end());
  while (!unVisited.empty()) {
    auto cell = randomElement(unVisited);
    auto path = std::vector<CellPtr>({cell});
    while (std::find(unVisited.begin(), unVisited.end(), cell) != unVisited.end()) {
      cell = randomElement(cell->getNeighbors());
      auto position = std::find(path.begin(), path.end(), cell);
      if (position != path.end()) {
        path = std::vector<CellPtr>(path.begin(), position);
      } else {
        path.push_back(cell);
      }
    }
    for (int index = 0; index < int(path.size()) - 1; ++index) {
      path[index]->link(path[index + 1]);
      unVisited.erase(std::remove(unVisited.begin(), unVisited.end(), path[index]),
                      unVisited.end());
    }
  }
  return grid;
}