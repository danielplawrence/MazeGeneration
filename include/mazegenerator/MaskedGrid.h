#include <mazegenerator/Grid.h>
#include <mazegenerator/Mask.h>

#include <utility>

class MaskedGrid : public Grid {
public:
  explicit MaskedGrid(Mask& mask) : Grid(mask.rows, mask.columns) { this->mask = mask; }
  static GridPtr create(Mask& mask) {
    auto grid = new MaskedGrid(mask);
    grid->prepareGrid();
    grid->configureCells();
    grid->ptr = GridPtr(grid);
    return grid->ptr;
  }
  void prepareGrid() override;
  std::shared_ptr<Cell> randomCell() override;

private:
  Mask mask;
};