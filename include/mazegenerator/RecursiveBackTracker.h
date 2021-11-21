#pragma once

#include <mazegenerator/Maze.h>

class RecursiveBackTracker : public Maze {
public:
  GridPtr on(GridPtr grid) override;
};