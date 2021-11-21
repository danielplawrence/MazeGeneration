#pragma once

#include <mazegenerator/Maze.h>

class Wilson : public Maze {
public:
  GridPtr on(GridPtr grid);
};