#pragma once

#include "const.hpp"
#include "shape.hpp"
#include <array>
#include <raylib.h>
#include <string>
#include <utility>
#include <vector>

namespace gyp {

enum button_status { normal, hover, pressed };

template <class callback_type> class button : public rectangle {
private:
  button_status status{};
  std::array<Color, 3> color{};
  std::array<Image, 3> image{};
  std::array<Color, 3> tint{};
  std::array<std::string, 3> text{};
  std::array<callback_type, 4> call_back{};
  float font_size{};
  float spacing{};
  Font font{};

public:
  button();
  button(int pos_x, int pos_y, int width, int height);
  button(int pos_x, int pos_y, int width, int height, const std::string &text,
         float font_size = DEFAULT_FONT_SIZE);
  button(int pos_x, int pos_y, int width, int height,
         std::array<std::string, 3> text, float font_size = DEFAULT_FONT_SIZE);
  ~button() = default;
  // Setter
  void set_geometry(int pos_x, int pos_y, int width, int height);
  void set_color(std::array<Color, 3> background,
                 std::array<Color, 3> foreground);
  void set_text(Font font, float font_size, float spacing,
                std::array<std::string, 3> &&text);
  void set_status(button_status stat);
  void set_call_back(std::array<callback_type, 4> call_back);
  // Getter
  button_status get_status();
  // Method
  void draw();
  void draw(button_status status);
  callback_type interact(Vector2 mouse);
};

template <class callback_type>
button<callback_type>::button() : status(normal) {
  set_color(std::array<Color, 3>{BLACK, GRAY, BLUE},
            std::array<Color, 3>{WHITE, WHITE, WHITE});
  set_text(GetFontDefault(), DEFAULT_FONT_SIZE, DEFAULT_FONT_SPACING,
           std::array<std::string, 3>{"Text", "Text", "Text"});
}

template <class callback_type>
button<callback_type>::button(int pos_x, int pos_y, int width, int height)
    : status(normal) {
  set_geometry(pos_x, pos_y, width, height);
  set_color(std::array<Color, 3>{BLACK, GRAY, BLUE},
            std::array<Color, 3>{WHITE, WHITE, WHITE});
  set_text(GetFontDefault(), DEFAULT_FONT_SIZE, DEFAULT_FONT_SPACING,
           std::array<std::string, 3>{"Text", "Text", "Text"});
}

template <class callback_type>
button<callback_type>::button(int pos_x, int pos_y, int width, int height,
                              const std::string &text, float font_size)
    : status(normal) {
  set_geometry(pos_x, pos_y, width, height);
  set_color(std::array<Color, 3>{BLACK, GRAY, BLUE},
            std::array<Color, 3>{WHITE, WHITE, WHITE});
  set_text(GetFontDefault(), font_size, DEFAULT_FONT_SPACING,
           std::array<std::string, 3>{text, text, text});
}

template <class callback_type>
button<callback_type>::button(int pos_x, int pos_y, int width, int height,
                              std::array<std::string, 3> text, float font_size)
    : status(normal), text(std::move(text)) {
  set_geometry(pos_x, pos_y, width, height);
  set_color(std::array<Color, 3>{BLACK, GRAY, BLUE},
            std::array<Color, 3>{WHITE, WHITE, WHITE});
  set_text(GetFontDefault(), font_size, DEFAULT_FONT_SPACING, std::move(text));
}

template <class callback_type>
void button<callback_type>::set_geometry(int pos_x, int pos_y, int width,
                                         int height) {
  x = pos_x;
  y = pos_y;
  this->width = width;
  this->height = height;
}

template <class callback_type>
void button<callback_type>::set_color(std::array<Color, 3> background,
                                      std::array<Color, 3> foreground) {
  color = background;
  tint = foreground;
}

template <class callback_type>
void button<callback_type>::set_text(Font font, float font_size, float spacing,
                                     std::array<std::string, 3> &&text) {
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
void button<callback_type>::set_call_back(
    std::array<callback_type, 4> call_back) {
  this->call_back = call_back;
}

template <class callback_type>
button_status button<callback_type>::get_status() {
  return status;
}

template <class callback_type> void button<callback_type>::draw() {
  draw(status);
}

template <class callback_type>
void button<callback_type>::draw(button_status stat) {
  DrawRectangle(x, y, width, height, color.at(stat));
  Vector2 text_size =
      MeasureTextEx(font, text.at(stat).c_str(), font_size, spacing);
  text_size.x /= -2;
  text_size.y /= -2;
  text_size.x += x + width / 2;
  text_size.y += y + height / 2;
  DrawTextEx(font, text.at(stat).c_str(), text_size, font_size, spacing, tint.at(stat));
}

template <class callback_type>
callback_type button<callback_type>::interact(Vector2 mouse) {
  int mx = static_cast<int>(mouse.x);
  int my = static_cast<int>(mouse.y);
  if (mx > x && mx < x + width && my > y && my < y + height) {
    // If in the box
    status = hover;
    for (int i = 0; i <= 2; i++) {
      if (IsMouseButtonReleased(i)) {
        status = pressed;
        draw();
        return call_back[i + 1];
      }
      if (IsMouseButtonDown(i)) {
        status = pressed;
      }
    }
    // else
    draw();
    return call_back[0];
  }
  // else: not in the box
  status = normal;
  draw();
  return call_back[0];
}

template <class callback_type>
class timer {
  private:
    int count_down{};
    std::array<callback_type, 2> call_back;

  public:
    timer() = default;
    explicit timer(int count_down);
    ~timer() = default;
    // Setter
    void set_count_down(int count_down);
    void set_call_back(std::array<callback_type, 2> call_back);
    //
    void draw();
    callback_type interact();
};

template <class callback_type>
timer<callback_type>::timer(int count_down) : count_down(count_down) {}

template <class callback_type>
void timer<callback_type>::set_count_down(int count_down) {
  this->count_down = count_down;
}

template <class callback_type>
void timer<callback_type>::set_call_back(std::array<callback_type, 2> call_back) {
  this->call_back = call_back;
}

template <class callback_type>
void timer<callback_type>::draw() {
  count_down--;
}

template <class callback_type>
callback_type timer<callback_type>::interact() {
  count_down--;
  if (count_down <= 0) {
    return call_back[1];
  }
  return call_back[0];
}

} // namespace gyp
