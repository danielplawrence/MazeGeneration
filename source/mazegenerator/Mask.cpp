#include <mazegenerator/Mask.h>

#include <iostream>
#include <random>

bool Mask::get(int row, int column) {
  if (row < rows && column < columns) {
    return bits[row][column];
  }
  return false;
}
void Mask::set(int row, int column, bool value) {
  if (row < rows && column < columns) {
    bits[row][column] = value;
  }
}
int Mask::count() {
  int count = 0;
  for (const auto& col : bits) {
    for (auto bit : col) {
      if (bit) {
        ++count;
      }
    }
  }
  return count;
}
std::optional<std::pair<int, int>> Mask::randomLocation() {
  if (count() == 0) {
    return {};
  }
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> rowDistr(0, rows - 1);
  std::uniform_int_distribution<> colDistr(0, columns - 1);
  for (;;) {
    int x = rowDistr(gen);
    int y = colDistr(gen);
    if (bits[x][y]) {
      return {{x, y}};
    }
  }
}
Mask::Mask(std::stringstream& file) {
  std::vector<std::vector<bool>> res;
  for (std::string line; std::getline(file, line);) {
    std::vector<bool> lineRes;
    for (auto& token : line) {
      if (token == 'X') {
        lineRes.push_back(false);
      } else {
        lineRes.push_back(true);
      }
    }
    res.push_back(lineRes);
  }
  this->rows = int(res.size());
  this->columns = int(res[0].size());
  this->bits = res;
}
Mask::Mask(unsigned char* img, int width, int height, int channels) {
  size_t img_size = width * height * channels;
  std::vector<std::vector<bool>> res;
  for (unsigned char* r = img; r != img + img_size; r += (width * channels)) {
    std::vector<bool> lineRes;
    for (unsigned char* p = r; p < r + width * channels; p += channels) {
      int v = 0;
      for (int channel = 0; channel < channels; channel++) {
        v += *(p + channel);
      }
      if (v / channels < 100) {
        lineRes.push_back(false);
      } else {
        lineRes.push_back(true);
      }
    }
    res.push_back(lineRes);
  }
  this->rows = height;
  this->columns = width;
  this->bits = res;
}