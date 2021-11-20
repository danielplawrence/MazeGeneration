#include <mazegenerator/Distances.h>

#include <utility>

Distances::Distances(const std::shared_ptr<Cell>& root) {
  this->root = root;
  cells[root] = 0;
}
std::optional<int> Distances::get(const CellPtr& cell) {
  auto it = cells.find(cell);
  if (it == cells.end()) {
    return {};
  }
  return cells[cell];
}
void Distances::set(const CellPtr& cell, int dist) { cells[cell] = dist; }
std::vector<std::shared_ptr<Cell>> Distances::getCells() {
  std::vector<std::shared_ptr<Cell>> res;
  for (auto& cell : cells) {
    res.emplace_back(cell.first);
  }
  return res;
}
std::pair<int, CellPtr> Distances::max() {
  std::vector<int> res;
  for (auto& cell : cells) {
    res.emplace_back(cell.second);
  }
  auto max = *std::max_element(cells.begin(), cells.end(), [](const auto& p1, const auto& p2) {
    return p1.second < p2.second;
  });
  return {max.second, max.first};
}
DistancesPtr Distances::pathTo(CellPtr goal) {
  auto current = std::move(goal);
  auto breadcrumbs = Distances::create(root);
  breadcrumbs->set(current, this->cells[current]);
  do {
    for (const auto& neighbor : current->getLinks()) {
      if (this->get(neighbor).has_value() && this->get(current).has_value()
          && this->get(neighbor).value() < this->get(current).value()) {
        breadcrumbs->set(neighbor, this->get(neighbor).value());
        current = neighbor;
        break;
      }
    }
  } while (current != root);
  return breadcrumbs;
}
