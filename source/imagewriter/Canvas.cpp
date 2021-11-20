#include <fmt/format.h>
#include <imagewriter/Canvas.h>
#include <imagewriter/Color.h>

#include <vector>

Canvas::Canvas(int width, int height, Color background) {
  this->width = width;
  this->height = height;
  this->pixels = std::vector<std::vector<Color>>(width);
  for (int x = 0; x < width; x++) {
    this->pixels[x] = std::vector<Color>(height);
  }
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      writePixel(x, y, background);
    }
  }
}
void Canvas::writePixel(int x, int y, Color c) { this->pixels[x][y] = c; }
void Canvas::writeLine(int x1, int y1, int x2, int y2, Color c) {
  for (int x = x1; x <= x2; ++x) {
    for (int y = y1; y <= y2; ++y) {
      this->writePixel(x, y, c);
    }
  }
}
Color Canvas::pixelAt(int x, int y) { return this->pixels[x][y]; }
std::string Canvas::toPortablePixmap() {
  std::string ppmVariant("P3");
  std::string maxColorValue("255");
  std::string header(ppmVariant + "\n" + fmt::to_string(this->width) + " "
                     + fmt::to_string(this->height) + "\n" + maxColorValue + "\n");
  for (int y = 0; y < this->height; y++) {
    std::string line;
    for (int x = 0; x < this->width; x++) {
      Color c = this->pixels[x][y];
      std::vector<double> colorVals{c.red, c.green, c.blue};
      std::for_each(colorVals.begin(), colorVals.end(), [&line, &header](double f) {
        std::string val
            = fmt::to_string(std::ceil(std::clamp(float(f * 255.0), float(0.0), float(255.0))));
        if (line.size() + val.size() > 70) {
          line.pop_back();
          header += line + "\n";
          line = "";
        }
        line += val + " ";
      });
    }
    line.pop_back();
    header += line + "\n";
  }
  return header;
}
void Canvas::writeRect(int x1, int y1, int x2, int y2, Color c) {
  for (int x = x1; x < x2; ++x) {
    writeLine(x, y1, x, y2, c);
  }
}
