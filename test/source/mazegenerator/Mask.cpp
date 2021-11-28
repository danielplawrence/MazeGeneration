
#include <doctest/doctest.h>
#include <mazegenerator/Mask.h>

TEST_CASE("Mask") {
  SUBCASE("Getting and setting the value of a bit") {
    auto m = Mask(2, 2);
    m.set(0, 0, true);
    CHECK(m.get(0, 0) == true);
  }
  SUBCASE("Setting the value of a bit which is out of range") {
    auto m = Mask(2, 2);
    m.set(3, 3, true);
  }
  SUBCASE("Getting the value of a bit which is out of range") {
    auto m = Mask(2, 2);
    CHECK(m.get(3, 3) == false);
  }
  SUBCASE("Counting the bits in the mask") {
    auto m = Mask(2, 2);
    CHECK(m.count() == 4);
    m.set(0, 0, false);
    CHECK(m.count() == 3);
  }
  SUBCASE("Returning a random location") {
    auto m = Mask(2, 2);
    m.set(0, 0, false);
    m.set(1, 0, false);
    m.set(0, 1, false);
    auto res = m.randomLocation();
    CHECK(res.has_value());
    CHECK(res->first == 1);
    CHECK(res->second == 1);
  }
  SUBCASE("Returning a random location when no cells are enabled") {
    auto m = Mask(2, 2);
    m.set(0, 0, false);
    m.set(1, 0, false);
    m.set(0, 1, false);
    m.set(1, 1, false);
    auto res = m.randomLocation();
    CHECK(!res.has_value());
  }
  SUBCASE("Creating a mask from a text file") {
    auto str = std::stringstream(
        "X........X\n"
        "....XX....\n"
        "...XXXX...\n"
        "....XX....\n"
        "X........X\n"
        "X........X\n"
        "....XX....\n"
        "...XXXX...\n"
        "....XX....\n"
        "X........X\n");
    auto m = Mask(str);
    CHECK(m.get(0, 0) == false);
    CHECK(m.get(0, 9) == false);
    CHECK(m.get(1, 4) == false);
    CHECK(m.get(1, 5) == false);
    CHECK(m.get(2, 3) == false);
    CHECK(m.get(2, 4) == false);
    CHECK(m.get(2, 5) == false);
    CHECK(m.get(2, 6) == false);
    CHECK(m.get(3, 4) == false);
    CHECK(m.get(3, 5) == false);
    CHECK(m.get(4, 0) == false);
    CHECK(m.get(4, 9) == false);
    CHECK(m.get(5, 0) == false);
    CHECK(m.get(5, 9) == false);
    CHECK(m.get(6, 4) == false);
    CHECK(m.get(6, 5) == false);
    CHECK(m.get(7, 3) == false);
    CHECK(m.get(7, 4) == false);
    CHECK(m.get(7, 5) == false);
    CHECK(m.get(7, 6) == false);
    CHECK(m.get(8, 4) == false);
    CHECK(m.get(8, 5) == false);
    CHECK(m.get(9, 0) == false);
    CHECK(m.get(9, 9) == false);
  }
  SUBCASE("Creating a mask from an image file") {
    int channels = 3;
    int width = 3;
    int height = 3;
    unsigned char img[] = {255, 255, 255, 255, 255, 255, 255, 255, 255, 0,   0,   0,   0,  0,
                           0,   0,   0,   0,   255, 255, 255, 255, 255, 255, 255, 255, 255};
    auto m = Mask(&img[0], width, height, channels);
    CHECK(m.get(0, 0) == true);
    CHECK(m.get(0, 1) == true);
    CHECK(m.get(0, 2) == true);
    CHECK(m.get(1, 0) == false);
    CHECK(m.get(1, 1) == false);
    CHECK(m.get(1, 2) == false);
    CHECK(m.get(2, 0) == true);
    CHECK(m.get(2, 1) == true);
    CHECK(m.get(2, 2) == true);
  }
}