#include <imagewriter/Canvas.h>
#include <imagewriter/Color.h>
#include <mazegenerator/Grid.h>

#include <algorithm>
#include <iterator>
#include <random>

void Grid::prepareGrid() {
  for (int i = 0; i < rows; ++i) {
    std::vector<std::shared_ptr<Cell>> r;
    r.reserve(columns);
    for (int j = 0; j < columns; j++) {
      r.emplace_back(Cell::create(i, j));
    }
    grid.emplace_back(r);
  }
}
void Grid::configureCells() {
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; j++) {
      auto cell = get(i, j);
      cell->neighbours.north = get(i - 1, j);
      cell->neighbours.south = get(i + 1, j);
      cell->neighbours.east = get(i, j + 1);
      cell->neighbours.west = get(i, j - 1);
    }
  }
}
int randomInt() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distr(0, 2);
  return distr(gen);
}
std::shared_ptr<Cell> Grid::get(int row, int col) {
  if (row < 0 || row > rows - 1) {
    return nullptr;
  }
  if (col < 0 || col > columns - 1) {
    return nullptr;
  }
  return grid[row][col];
}
int Grid::size() const { return rows * columns; }
std::shared_ptr<Cell> Grid::randomCell() { return get(randomInt(), randomInt()); }
std::string Grid::toPortablePixmap(int cellSize) {
  auto imgWidth = cellSize * this->columns;
  auto imgHeight = cellSize * this->rows;
  auto background = WHITE;
  auto wall = BLACK;
  auto img = Canvas(imgWidth + 1, imgHeight + 1, background);
  for (int x = 0; x < this->rows; ++x) {
    for (int y = 0; y < this->columns; ++y) {
      auto cell = get(x, y);
      auto contents = contentsOf(cell, cellSize);
      img.writeRect(std::get<0>(contents), std::get<1>(contents), std::get<2>(contents),
                    std::get<3>(contents), std::get<4>(contents));
    }
  }
  for (int x = 0; x < this->rows; ++x) {
    for (int y = 0; y < this->columns; ++y) {
      auto cell = get(x, y);
      auto location = cell->getLocation();
      auto x1 = location.second * cellSize;
      auto y1 = location.first * cellSize;
      auto x2 = (location.second + 1) * cellSize;
      auto y2 = (location.first + 1) * cellSize;
      if (cell->neighbours.north == nullptr) {
        img.writeLine(x1, y1, x2, y1, wall);
      }
      if (cell->neighbours.west == nullptr) {
        img.writeLine(x1, y1, x1, y2, wall);
      }
      if (!cell->linkedTo(cell->neighbours.east)) {
        img.writeLine(x2, y1, x2, y2, wall);
      }
      if (!cell->linkedTo(cell->neighbours.south)) {
        img.writeLine(x1, y2, x2, y2, wall);
      }
    }
  }
  return img.toPortablePixmap();
}
std::vector<std::shared_ptr<Cell>> Grid::cells() {
  std::vector<std::shared_ptr<Cell>> res;
  for (int x = 0; x < this->rows; ++x) {
    for (int y = 0; y < this->columns; ++y) {
      res.emplace_back(get(x, y));
    }
  }
  return res;
}
std::tuple<int, int, int, int, Color> Grid::contentsOf(CellPtr cell, int cellSize) {
  (void)cell;
  (void)cellSize;
  return {};
}
std::vector<CellPtr> Grid::deadEnds() {
  std::vector<CellPtr> res;
  auto c = this->cells();
  std::copy_if(c.begin(), c.end(), std::back_inserter(res),
               [](const CellPtr& cell) { return cell->getLinks().size() == 1; });
  return res;
}
