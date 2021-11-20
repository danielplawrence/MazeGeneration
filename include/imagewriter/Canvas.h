#pragma once

#include <imagewriter/Color.h>

#include <string>
#include <vector>

/**
 * @brief Represents the image canvas
 */
class Canvas {
public:
  int width{};
  int height{};
  /**
   * @brief Create a new Canvas
   * @param width width of the Canvas in pixels
   * @param height height of the Canvas in pixels
   */
  Canvas(int width, int height, Color background = WHITE);
  /**
   * @brief Write a pixel with color c to coordinates x and y
   * @param x x coordinate
   * @param y y coordinate
   * @param c color
   */
  void writePixel(int x, int y, Color c);
  /**
   * @brief Write a line with color c from coordinates x1 and y1 to x2 and y2
   * @param x1 x coordinate
   * @param y1 y coordinate
   * @param x2 x coordinate
   * @param y2 y coordinate
   * @param c color
   */
  void writeLine(int x1, int y1, int x2, int y2, Color c);
  /**
   * @brief Write a rectangle to the canvas
   * @param x1 x coordinate
   * @param y1 y coordinate
   * @param x2 x coordinate
   * @param y2 y coordinate
   */
  void writeRect(int x1, int y1, int x2, int y2, Color c);
  /**
   * @brief Return a pointer to the color at coordinates x and y
   * @param x x coordinate
   * @param y y coordinate
   * @return color
   */
  Color pixelAt(int x, int y);
  /**
   * @brief Return the Portable Pixmap representation of this Canvas
   * @return Portable Pixmap representation of this Canvas
   */
  std::string toPortablePixmap();

private:
  std::vector<std::vector<Color>> pixels;
};
