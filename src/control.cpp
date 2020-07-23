#include "control.hpp"

#include <utility>

namespace gyp {
button::button(int pos_x, int pos_y, int width, int height, std::string text)
    : text(std::move(text)) {
  x = pos_x;
  y = pos_y;
  this->width = width;
  this->height = height;
  status = normal;
  color[0] = BLACK;
  color[1] = GRAY;
  color[2] = BLUE;
}
button::~button() = default;
void button::draw() { draw(status); }
void button::draw(button_status stat) {
  DrawRectangle(x, y, width, height, color.at(stat));
  DrawTextRec(GetFontDefault(), text.c_str(),
              rectangle(x, y, width, height).ray_rectangle(), 20.0, 0.5, true,
              RAYWHITE);
}
int button::interact(Vector2 mouse) {
  int mx = static_cast<int>(mouse.x);
  int my = static_cast<int>(mouse.y);
  if (mx > x && mx < x + width && my > y && my < y + height) {
    for (int i = 0; i <= 2; i++) {
      if (IsMouseButtonReleased(i)) {
        status = pressed;
        draw();
        return i;
      }
    }
    // else
    status = hover;
    draw();
    return -1;
  }
  // else
  status = normal;
  draw();
  return -1;
}
} // namespace gyp
