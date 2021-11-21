
#include <mazegenerator/DistanceGrid.h>
#include <algorithm>

std::tuple<int, int, int, int, Color> DistanceGrid::contentsOf(CellPtr cell, int cellSize) {
  if (distances == nullptr) {
    return {};
  }
  auto location = cell->getLocation();
  auto x1 = location.second * cellSize;
  auto y1 = location.first * cellSize;
  auto x2 = (location.second + 1) * cellSize;
  auto y2 = (location.first + 1) * cellSize;
  auto distance = distances->get(cell);
  if (!distance.has_value()) {
    return {};
  }
  auto max = std::max({distances->max().first, 1});
  auto intensity = (float(max) - float(distance.value())) / float(max);
  auto c = color * intensity;
  return {x1, y1, x2, y2, c};
}