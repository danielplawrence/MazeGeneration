#include <mazegenerator/RecursiveBackTracker.h>

#include <algorithm>
#include <iterator>

GridPtr backTracker(GridPtr grid, const CellPtr& startAt) {
  std::vector<CellPtr> stack;
  stack.push_back(startAt);
  while (!stack.empty()) {
    auto current = (stack.end() - 1)->get();
    auto currentNeighbors = current->getNeighbors();
    std::vector<CellPtr> neighbors;
    std::copy_if(currentNeighbors.begin(), currentNeighbors.end(), std::back_inserter(neighbors),
                 [](const CellPtr& n) { return n->getLinks().empty(); });
    if (neighbors.empty()) {
      stack.pop_back();
    } else {
      auto neighbor = Maze::randomElement(neighbors);
      current->link(neighbor);
      stack.push_back(neighbor);
    }
  }
  return grid;
}
GridPtr RecursiveBackTracker::on(GridPtr grid) { return backTracker(grid, grid->randomCell()); }