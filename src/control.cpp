#include "control.hpp"

namespace gyp {
button::button(std::pair<int, int> pos, int width, int height, std::string text)
    : pos(std::move(pos)), width(width), height(height), text(std::move(text)) {
  status = normal;
  color[0] = BLACK;
  color[1] = GRAY;
  color[2] = BLUE;
}
button::~button() = default;
void button::draw() {
  DrawRectangle(pos.first, pos.second, width, height, color.at(status));
}
void button::draw(button_status stat) {
  DrawRectangle(pos.first, pos.second, width, height, color.at(stat));
}
void button::draw(Vector2 mouse) {
  update(mouse);
  draw();
}
void button::update(Vector2 mouse) {
  int x = static_cast<int>(mouse.x);
  int y = static_cast<int>(mouse.y);
  if (x > pos.first && x < pos.first + width && y > pos.second &&
      y < pos.second + height) {
    status = hover;
    if (IsMouseButtonDown(0) || IsMouseButtonDown(1) || IsMouseButtonDown(2)) {
      status = pressed;
    }
  } else {
    status = normal;
  }
}
} // namespace gyp
