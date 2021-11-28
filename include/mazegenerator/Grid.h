#pragma once

#include <imagewriter/Color.h>
#include <mazegenerator/Cell.h>

#include <memory>
#include <string>
#include <vector>

class Grid;
typedef std::shared_ptr<Grid> GridPtr;

class Grid {
protected:
  GridPtr ptr;
  int rows;
  int columns;
  void configureCells();
  virtual void prepareGrid();

public:
  Grid(int rows, int columns) {
    this->rows = rows;
    this->columns = columns;
  }
  virtual ~Grid() = default;
  static GridPtr create(int rows, int columns) {
    auto grid = new Grid(rows, columns);
    grid->prepareGrid();
    grid->configureCells();
    grid->ptr = GridPtr(grid);
    return grid->ptr;
  }
  std::shared_ptr<Cell> get(int row, int col);
  [[nodiscard]] int size() const;
  virtual std::shared_ptr<Cell> randomCell();
  std::string toPortablePixmap(int cellSize = 10);
  virtual std::tuple<int, int, int, int, Color> contentsOf(CellPtr cell, int cellSize);
  std::vector<std::shared_ptr<Cell>> cells();
  std::vector<std::shared_ptr<Cell>> deadEnds();
  std::vector<std::vector<std::shared_ptr<Cell>>> grid;
};