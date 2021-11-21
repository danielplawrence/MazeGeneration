//
// Created by Lawrence, Daniel on 11/17/21.
//
#include <mazegenerator/Sidewinder.h>

#include <random>

template <typename Iter, typename RandomGenerator>
Iter select_randomly(Iter start, Iter end, RandomGenerator &g) {
  std::uniform_int_distribution<> dis(int(0), std::distance(start, end) - 1);
  std::advance(start, dis(g));
  return start;
}

template <typename Iter> Iter select_randomly(Iter start, Iter end) {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  return select_randomly(start, end, gen);
}

int randomInt() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distr(0, 2);
  return distr(gen);
}

GridPtr Sidewinder::on(GridPtr grid) {
  for (auto &thisRow : grid->grid) {
    std::vector<std::shared_ptr<Cell>> run;
    for (auto &cell : thisRow) {
      run.emplace_back(cell);
      auto atEasternBoundary = (cell->neighbours.east == nullptr);
      auto atNorthernBoundary = (cell->neighbours.north == nullptr);
      auto shouldCloseOut = atEasternBoundary || (!atNorthernBoundary && randomInt() == 0);
      if (shouldCloseOut) {
        if (!run.empty()) {
          auto member = *select_randomly(run.begin(), run.end());
          if (member->neighbours.north != nullptr) {
            member->link(member->neighbours.north);
            std::vector<std::shared_ptr<Cell>>().swap(run);
          }
        }
      } else {
        cell->link(cell->neighbours.east);
      }
    }
  }
  return grid;
}
