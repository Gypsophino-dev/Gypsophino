#include "control.hpp"

#include <utility>

namespace gyp {
//button::button(std::pair<int, int> pos, int width, int height, std::string text)
//    : pos(std::move(pos)), width(width), height(height), text(std::move(text)) {
//  status = normal;
//  color[0] = BLACK;
//  color[1] = GRAY;
//  color[2] = BLUE;
//}
button::button(int posX, int posY, int width, int height, std::string text)
  : text(std::move(text)) {
  x = posX;
  y = posY;
  this->width = width;
  this->height = height;
  status = normal;
  color[0] = BLACK;
  color[1] = GRAY;
  color[2] = BLUE;
}
button::~button() = default;
void button::draw() {
  draw(status);
}
void button::draw(button_status stat) {
  DrawRectangle(x, y, width, height, color.at(stat));
  DrawTextRec(GetFontDefault(), text.c_str(), rectangle(x, y, width, height).ray_rectangle(), 14.0, 0.5, true, RAYWHITE);
}
void button::draw(Vector2 mouse) {
  update(mouse);
  draw();
}
void button::update(Vector2 mouse) {
  int mx = static_cast<int>(mouse.x);
  int my = static_cast<int>(mouse.y);
  if (mx > x && mx < x + width && my > y && my < y + height) {
    status = hover;
    if (IsMouseButtonDown(0) || IsMouseButtonDown(1) || IsMouseButtonDown(2)) {
      status = pressed;
    }
  } else {
    status = normal;
  }
}
} // namespace gyp
