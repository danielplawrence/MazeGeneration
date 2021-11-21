#pragma once

#include <mazegenerator/Grid.h>
#include <mazegenerator/Maze.h>

#include <random>

class AldousBroder : public Maze {
public:
  GridPtr on(GridPtr grid);
};