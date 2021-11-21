#pragma once

#include <map>
#include <memory>
#include <utility>
#include <vector>

class Neighbours;
class Cell;
class Distances;
typedef std::shared_ptr<Cell> CellPtr;
typedef std::shared_ptr<Distances> DistancesPtr;

class Neighbours {
public:
  CellPtr north{};
  CellPtr south{};
  CellPtr east{};
  CellPtr west{};
  std::vector<CellPtr> getAll();
  CellPtr sample();
};

class Cell {
  Cell() = default;
  [[nodiscard]] CellPtr getPtr() const { return this->ptr; }

public:
  Cell(int row, int column);
  std::pair<int, int> getLocation();
  void link(const CellPtr& cell, bool bidirectional = true);
  void unlink(const CellPtr& cell, bool bidirectional = true);
  std::vector<CellPtr> getLinks();
  bool linkedTo(const CellPtr& cell);
  std::vector<CellPtr> getNeighbors();
  static CellPtr create(int row, int column);
  bool operator==(const Cell& cell) const;
  Neighbours neighbours;
  DistancesPtr getDistances();

private:
  CellPtr ptr;
  std::map<CellPtr, bool> links;
  int row{};
  int column{};
};