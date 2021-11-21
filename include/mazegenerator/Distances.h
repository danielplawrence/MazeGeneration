#pragma once

#include <map>
#include <memory>
#include <vector>
#include <optional>

#include "Cell.h"

class Distances {
  std::shared_ptr<Cell> root;
  std::map<std::shared_ptr<Cell>, int> cells;

public:
  explicit Distances(const std::shared_ptr<Cell>& root);
  static DistancesPtr create(const CellPtr& r) {
    auto dist = new Distances(r);
    dist->ptr = DistancesPtr(dist);
    return dist->ptr;
  }
  std::vector<CellPtr> getCells();
  std::optional<int> get(const CellPtr& cell);
  std::pair<int, CellPtr> max();
  void set(const CellPtr& cell, int distance);
  DistancesPtr getPtr() { return this->ptr; }
  DistancesPtr pathTo(CellPtr goal);

private:
  DistancesPtr ptr;
};