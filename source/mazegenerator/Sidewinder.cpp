#include <mazegenerator/Sidewinder.h>

GridPtr Sidewinder::on(GridPtr grid) {
  for (auto &thisRow : grid->grid) {
    std::vector<std::shared_ptr<Cell>> run;
    for (auto &cell : thisRow) {
      run.emplace_back(cell);
      auto atEasternBoundary = (cell->neighbours.east == nullptr);
      auto atNorthernBoundary = (cell->neighbours.north == nullptr);
      auto shouldCloseOut = atEasternBoundary || (!atNorthernBoundary && randomInt() == 0);
      if (shouldCloseOut) {
        if (!run.empty()) {
          auto member = randomElement(run);
          if (member->neighbours.north != nullptr) {
            member->link(member->neighbours.north);
            std::vector<std::shared_ptr<Cell>>().swap(run);
          }
        }
      } else {
        cell->link(cell->neighbours.east);
      }
    }
  }
  return grid;
}
