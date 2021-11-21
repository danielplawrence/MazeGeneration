#pragma once

#include <mazegenerator/Grid.h>
#include <mazegenerator/Maze.h>

class Sidewinder : Maze {
public:
  GridPtr on(GridPtr grid);
};