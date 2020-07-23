#pragma once

#include "shape.hpp"
#include <array>
#include <raylib.h>
#include <string>
#include <utility>
#include <vector>

namespace gyp {

enum button_status { normal, hover, pressed };

class button : public rectangle {
private:

public:
  button_status status;
  std::array<Color, 3> color;
  std::array<Image, 3> image;
  std::string text;
  button();
  button(int pos_x, int pos_y, int width, int height, std::string text);
  ~button();
  void draw();
  void draw(button_status status);
  int interact(Vector2 mouse);
};

//class keyboard_listener : std::vector<KeyboardKey> {};

class menu {};
} // namespace gyp
