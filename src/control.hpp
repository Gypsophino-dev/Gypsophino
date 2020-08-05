#pragma once

#include "shape.hpp"
#include "const.hpp"
#include <array>
#include <raylib.h>
#include <string>
#include <utility>
#include <vector>

namespace gyp {

enum button_status { normal, hover, pressed };

template <class callback_type>
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
  callback_type call_back;

public:
  button();
  button(int pos_x, int pos_y, int width, int height);
  button(int pos_x, int pos_y, int width, int height,
         const std::string& text, float font_size = DEFAULT_FONT_SIZE);
  button(int pos_x, int pos_y, int width, int height,
         std::array<std::string, 3> text, float font_size = DEFAULT_FONT_SIZE);
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

template <class callback_type>
button<callback_type>::button()
  : status(normal) {
  set_color(std::array<Color, 3>{BLACK, GRAY, BLUE},
            std::array<Color, 3>{WHITE, WHITE, WHITE});
  set_text(GetFontDefault(), DEFAULT_FONT_SIZE, DEFAULT_FONT_SPACING, std::array<std::string, 3>{"Text", "Text", "Text"});
}

template <class callback_type>
button<callback_type>::button(int pos_x, int pos_y, int width, int height) {
  set_geometry(pos_x, pos_y, width, height);
  status = normal;
  set_color(std::array<Color, 3>{BLACK, GRAY, BLUE},
            std::array<Color, 3>{WHITE, WHITE, WHITE});
  set_text(GetFontDefault(), DEFAULT_FONT_SIZE, DEFAULT_FONT_SPACING, std::array<std::string, 3>{"Text", "Text", "Text"});
}

template <class callback_type>
button<callback_type>::button(int pos_x, int pos_y, int width, int height, const std::string& text,
               float font_size) {
  set_geometry(pos_x, pos_y, width, height);
  status = normal;
  set_color(std::array<Color, 3>{BLACK, GRAY, BLUE},
            std::array<Color, 3>{WHITE, WHITE, WHITE});
  set_text(GetFontDefault(), font_size, DEFAULT_FONT_SPACING, std::array<std::string, 3>{text, text, text});
}

template <class callback_type>
button<callback_type>::button(int pos_x, int pos_y, int width, int height,
               std::array<std::string, 3> text, float font_size)
    : text(std::move(text)) {
  set_geometry(pos_x, pos_y, width, height);
  status = normal;
  set_color(std::array<Color, 3>{BLACK, GRAY, BLUE},
            std::array<Color, 3>{WHITE, WHITE, WHITE});
  set_text(GetFontDefault(), font_size, DEFAULT_FONT_SPACING, std::move(text));
}

template <class callback_type>
void button<callback_type>::set_geometry(int pos_x, int pos_y, int width, int height) {
  x = pos_x;
  y = pos_y;
  this->width = width;
  this->height = height;
}

template <class callback_type>
void button<callback_type>::set_color(std::array<Color, 3> background, std::array<Color, 3> foreground) {
  color = background;
  tint = foreground;
}

template <class callback_type>
void button<callback_type>::set_text(Font font, float font_size, float spacing, std::array<std::string, 3> text) {
  this->font = font;
  this->font_size = font_size;
  this->spacing = spacing;
  this->text = std::move(text);
}

template <class callback_type>
void button<callback_type>::set_status(button_status stat) {
  status = stat;
}

template <class callback_type>
button_status button<callback_type>::get_status() {
  return status;
}

template <class callback_type>
void button<callback_type>::draw() { draw(status); }

template <class callback_type>
void button<callback_type>::draw(button_status stat) {
  DrawRectangle(x, y, width, height, color.at(stat));
  Vector2 text_size = MeasureTextEx(font, text.at(stat).c_str(), font_size, spacing);
  rectangle text_box;
  text_box.x = x + width / 2 - static_cast<int>(text_size.x) / 2;
  text_box.y = y + height / 2 - static_cast<int>(text_size.y) / 2;
  text_box.width = static_cast<int>(text_size.x);
  text_box.height = static_cast<int>(text_size.y);
  DrawTextRec(GetFontDefault(), text.at(stat).c_str(), text_box.ray_rectangle(),
              font_size, spacing, true, DEFAULT_FG);
}

template <class callback_type>
int button<callback_type>::interact(Vector2 mouse) {
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

class menu {};
} // namespace gyp
