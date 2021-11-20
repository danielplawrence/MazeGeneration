
#include <imagewriter/Color.h>

#include <cmath>
#define EPS 0.0001

bool doubleEquals(double a, double b) { return abs(a - b) < EPS; }
Color::Color() {
  this->red = 0.0;
  this->green = 0.0;
  this->blue = 0.0;
}
Color::Color(double red, double green, double blue) {
  this->red = red;
  this->green = green;
  this->blue = blue;
}
Color Color::operator*(double f) const {
  double t[] = {this->red, this->green, this->blue, 0};
  return {t[0] * f, t[1] * f, t[2] * f};
}
Color Color::operator-(const Color &c) const {
  double t1[] = {this->red, this->green, this->blue, 0};
  double t2[] = {c.red, c.green, c.blue, 0};
  return {t1[0] - t2[0], t1[1] - t2[1], t1[2] - t2[2]};
}
Color Color::operator+(const Color &c) const {
  double t1[] = {this->red, this->green, this->blue, 0};
  double t2[] = {c.red, c.green, c.blue, 0};
  return {t1[0] + t2[0], t1[1] + t2[1], t1[2] + t2[2]};
}
Color Color::operator*(const Color &c) const {
  return {this->red * c.red, this->green * c.green, this->blue * c.blue};
}
bool Color::operator==(const Color &c) const {
  double t1[] = {this->red, this->green, this->blue, 0};
  double t2[] = {c.red, c.green, c.blue, 0};
  return doubleEquals(t1[0], t2[0]) && doubleEquals(t1[1], t2[1]) && doubleEquals(t1[2], t2[2]);
}