
#include <mazegenerator/BinaryTree.h>
#include <mazegenerator/DistanceGrid.h>
#include <mazegenerator/HuntAndKill.h>
#include <mazegenerator/Mask.h>
#include <mazegenerator/MaskedGrid.h>
#include <mazegenerator/RecursiveBackTracker.h>
#include <mazegenerator/Wilson.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <fstream>
#include <iostream>

#include "mazegenerator/Grid.h"

auto main(int argc, char** argv) -> int {
  (void)argc;
  (void)argv;
  int width, height, channels;
  unsigned char* img = stbi_load("/Users/danlaw/Downloads/city.png", &width, &height, &channels, 0);
  if (img == NULL) {
    printf("Error in loading the image\n");
    exit(1);
  }
  std::cout << "Loaded image with height: " << height << " and width: " << width << std::endl;
  auto m = Mask(img, width, height, channels);
  auto grid = MaskedGrid::create(m);
  grid = RecursiveBackTracker().on(grid);

  std::ofstream out("grid.ppm");
  out << grid->toPortablePixmap(10);
  out.close();

  return 0;
}
