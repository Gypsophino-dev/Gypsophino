#pragma once

#include <raylib.h>
#include <string>
#include <array>
#include <utility>

namespace gyp {
enum button_status { normal, hover, pressed };
class button {
private:
public:
  button_status status;
  std::pair<int, int> pos;
  int width;
  int height;
  std::array<Color, 3> color;
  std::array<Image, 3> image;
  std::string text;
  button();
  button(std::pair<int, int> pos, int width, int height, std::string text);
  ~button();
  void draw();
  void draw(button_status status);
  void draw(Vector2 mouse);
  void update(Vector2 mouse);
};
class menu {};
} // namespace gyp
