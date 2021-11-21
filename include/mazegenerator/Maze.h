#pragma once

#include <mazegenerator/Grid.h>

#include <random>

class Maze {
  virtual GridPtr on(GridPtr grid) = 0;

public:
  static CellPtr randomElement(std::vector<CellPtr> neighbors) {
    std::random_device random_device;
    std::mt19937 engine{random_device()};
    std::uniform_int_distribution<int> dist(int(0), int(neighbors.size() - 1));
    return neighbors[dist(engine)];
  }
  static int randomInt() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, 2);
    return distr(gen);
  }
};