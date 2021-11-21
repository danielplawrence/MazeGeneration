#pragma once

#include <mazegenerator/Maze.h>

class HuntAndKill : public Maze {
public:
  GridPtr on(GridPtr grid) override;
};