#include <mazegenerator/BinaryTree.h>
#include <mazegenerator/Grid.h>

#include <iterator>
#include <random>

template <typename Iter, typename RandomGenerator>
Iter select_randomly(Iter start, Iter end, RandomGenerator& g) {
  std::uniform_int_distribution<> dis(int(0), int(std::distance(start, end) - 1));
  std::advance(start, dis(g));
  return start;
}

template <typename Iter> Iter select_randomly(Iter start, Iter end) {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  return select_randomly(start, end, gen);
}

GridPtr BinaryTree::on(GridPtr grid) {
  for (auto& cell : grid->cells()) {
    std::vector<std::shared_ptr<Cell>> neighbours;
    if (cell->neighbours.north != nullptr) {
      neighbours.emplace_back(cell->neighbours.north);
    }
    if (cell->neighbours.east != nullptr) {
      neighbours.emplace_back(cell->neighbours.east);
    }
    if (!neighbours.empty()) {
      auto neighbour = *select_randomly(neighbours.begin(), neighbours.end());
      if (neighbour != nullptr) {
        cell->link(neighbour);
      }
    }
  }
  return grid;
}
