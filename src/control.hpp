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
  button_status status;
  std::array<Color, 3> color;
  std::array<Image, 3> image;
  std::array<Color, 3> tint;
  std::array<std::string, 3> text;
  float font_size;
  float spacing;
  Font font;

public:
  button();
  button(int pos_x, int pos_y, int width, int height);
  button(int pos_x, int pos_y, int width, int height,
         std::string text, float font_size = 20.0);
  button(int pos_x, int pos_y, int width, int height,
         std::array<std::string, 3> text, float font_size = 20.0);
  ~button() = default;
  // Setter
  void set_geometry(int pos_x, int pos_y, int width, int height);
  void set_color(std::array<Color, 3> background, std::array<Color, 3> foreground);
  void set_text(Font font, float font_size, float spacing, std::array<std::string, 3> text);
  void set_status(button_status stat);
  // Getter
  button_status get_status();
  // Method
  void draw();
  void draw(button_status status);
  int interact(Vector2 mouse);
};

class menu {};
} // namespace gyp
