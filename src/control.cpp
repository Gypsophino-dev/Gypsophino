#include "control.hpp"

#include "const.hpp"

#include <utility>

namespace gyp {

button::button()
  : status(normal) {
  color[0] = BLACK;
  color[1] = GRAY;
  color[2] = BLUE;
  tint[0] = WHITE;
  tint[1] = WHITE;
  tint[2] = WHITE;
  text[0] = "Text";
  text[1] = "Text";
  text[2] = "Text";
  font = GetFontDefault();
  font_size = DEFAULT_FONT_SIZE;
  spacing = 0.5;
}

button::button(int pos_x, int pos_y, int width, int height) {
  x = pos_x;
  y = pos_y;
  this->width = width;
  this->height = height;
  status = normal;
  color[0] = BLACK;
  color[1] = GRAY;
  color[2] = BLUE;
  tint[0] = WHITE;
  tint[1] = WHITE;
  tint[2] = WHITE;
  text[0] = "Text";
  text[1] = "Text";
  text[2] = "Text";
  font = GetFontDefault();
  font_size = DEFAULT_FONT_SIZE;
  spacing = 0.5;
}

button::button(int pos_x, int pos_y, int width, int height, std::string text,
               float font_size) {
  x = pos_x;
  y = pos_y;
  this->width = width;
  this->height = height;
  status = normal;
  color[0] = BLACK;
  color[1] = GRAY;
  color[2] = BLUE;
  tint[0] = WHITE;
  tint[1] = WHITE;
  tint[2] = WHITE;
  this->text[0] = text;
  this->text[1] = text;
  this->text[2] = text;
  font = GetFontDefault();
  font_size = DEFAULT_FONT_SIZE;
  spacing = 0.5;
}

button::button(int pos_x, int pos_y, int width, int height,
               std::array<std::string, 3> text, float font_size)
    : text(std::move(text)) {
  x = pos_x;
  y = pos_y;
  this->width = width;
  this->height = height;
  status = normal;
  color[0] = BLACK;
  color[1] = GRAY;
  color[2] = BLUE;
  this->font_size = font_size;
  spacing = 0.5;
}

void button::set_geometry(int pos_x, int pos_y, int width, int height) {
  x = pos_x;
  y = pos_y;
  this->width = width;
  this->height = height;
}

void button::set_color(std::array<Color, 3> background, std::array<Color, 3> foreground) {
  color = background;
  tint = foreground;
}

void button::set_text(Font font, float font_size, float spacing, std::array<std::string, 3> text) {
  this->font = font;
  this->font_size = font_size;
  this->spacing = spacing;
  this->text = std::move(text);
}

void button::set_status(button_status stat) {
  status = stat;
}

button_status button::get_status() {
  return status;
}

void button::draw() { draw(status); }

void button::draw(button_status stat) {
  DrawRectangle(x, y, width, height, color.at(stat));
  Vector2 text_size = MeasureTextEx(font, text.at(stat).c_str(), font_size, spacing);
  rectangle text_box;
  text_box.x = x + width / 2 - static_cast<int>(text_size.x) / 2;
  text_box.y = y + height / 2 - static_cast<int>(text_size.y) / 2;
  text_box.width = static_cast<int>(text_size.x);
  text_box.height = static_cast<int>(text_size.y);
  DrawTextRec(GetFontDefault(), text.at(stat).c_str(), text_box.ray_rectangle(),
              DEFAULT_FONT_SIZE, 0.5, true, RAYWHITE);
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
