#pragma once

#include <mazegenerator/Grid.h>
#include <mazegenerator/Maze.h>

#include <random>

class BinaryTree : Maze {
public:
  GridPtr on(GridPtr grid) override;
};