#include <mazegenerator/Distances.h>
#include <mazegenerator/Grid.h>

#include <utility>

class DistanceGrid : public Grid {
  using Grid::Grid;
  GridPtr ptr;
  DistancesPtr distances;
  Color color;

public:
  static GridPtr create(int rows, int columns, Color color = {1.0, 0.5, 0.5}) {
    auto grid = new DistanceGrid(rows, columns);
    grid->color = color;
    grid->ptr = GridPtr(grid);
    return grid->ptr;
  }
  void setDistances(DistancesPtr dist) { this->distances = std::move(dist); }
  std::tuple<int, int, int, int, Color> contentsOf(CellPtr cell, int cellSize) override;
};