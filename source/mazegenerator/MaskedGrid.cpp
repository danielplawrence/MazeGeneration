#include <mazegenerator/MaskedGrid.h>

void MaskedGrid::prepareGrid() {
  for (int i = 0; i < rows; ++i) {
    std::vector<std::shared_ptr<Cell>> r;
    r.reserve(columns);
    for (int j = 0; j < columns; j++) {
      if (mask.get(i, j)) {
        r.emplace_back(Cell::create(i, j));
      } else {
        r.emplace_back(nullptr);
      }
    }
    grid.emplace_back(r);
  }
}
std::shared_ptr<Cell> MaskedGrid::randomCell() {
  auto location = mask.randomLocation();
  return get(location->first, location->second);
}
