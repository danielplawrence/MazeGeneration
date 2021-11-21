#include <mazegenerator/Cell.h>
#include <mazegenerator/Distances.h>

#include <vector>
#include <algorithm>

std::pair<int, int> Cell::getLocation() { return {this->row, this->column}; }

Cell::Cell(int row, int column) {
  this->row = row;
  this->column = column;
}
void Cell::link(const CellPtr& cell, bool biDirectional) {
  links[cell] = true;
  if (biDirectional) {
    cell->link(this->getPtr(), false);
  }
}

void Cell::unlink(const CellPtr& cell, bool biDirectional) {
  links[cell] = false;
  if (biDirectional) {
    cell->unlink(this->getPtr(), false);
  }
}
std::vector<CellPtr> Cell::getLinks() {
  std::vector<CellPtr> val;
  for (const auto& kv : this->links) {
    if (kv.second) {
      val.emplace_back(kv.first);
    }
  }
  return val;
}
bool Cell::linkedTo(const CellPtr& cell) {
  if (this->links[cell]) {
    return true;
  }
  return false;
}
CellPtr Cell::create(int r, int c) {
  auto cell = new Cell(r, c);
  auto ptr = CellPtr(cell);
  cell->ptr = ptr;
  return ptr;
}
bool Cell::operator==(const Cell& cell) const {
  return this->row == cell.row && this->column == cell.column;
}
std::vector<CellPtr> Cell::getNeighbors() { return this->neighbours.getAll(); }
DistancesPtr Cell::getDistances() {
  auto distances = Distances::create(this->getPtr());
  auto frontier = std::vector<CellPtr>{this->getPtr()};
  while (!frontier.empty()) {
    auto newFrontier = std::vector<CellPtr>{};
    for (auto& cell : frontier) {
      for (auto& link : cell->getLinks()) {
        if (distances->get(link).has_value()) {
          continue;
        }
        if (distances->get(cell).has_value()) {
          distances->set(link, distances->get(cell).value() + 1);
        }
        newFrontier.emplace_back(link);
      }
    }
    frontier = newFrontier;
  }
  return distances;
}
std::vector<CellPtr> Neighbours::getAll() {
  auto result = std::vector<CellPtr>();
  if (this->north != nullptr) {
    result.emplace_back(north);
  }
  if (this->south != nullptr) {
    result.emplace_back(south);
  }
  if (this->east != nullptr) {
    result.emplace_back(east);
  }
  if (this->west != nullptr) {
    result.emplace_back(west);
  }
  return result;
}
