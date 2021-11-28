#pragma once

#include <sstream>

#include "optional"
#include "vector"

class Mask {
public:
  Mask() = default;
  Mask(int rows, int columns) {
    this->rows = rows;
    this->columns = columns;
    auto columnsVec = std::vector<bool>(this->columns);
    for (int i = 0; i < columns; ++i) {
      columnsVec[i] = true;
    }
    for (int i = 0; i < rows; ++i) {
      bits.push_back(columnsVec);
    }
  }
  Mask(std::stringstream& file);
  Mask(unsigned char* rgb, int width, int height, int channels);
  bool get(int row, int column);
  void set(int row, int column, bool value);
  int count();
  std::optional<std::pair<int, int>> randomLocation();
  int rows;

  int columns;

private:
  std::vector<std::vector<bool>> bits;
};