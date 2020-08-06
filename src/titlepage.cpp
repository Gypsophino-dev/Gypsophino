#include "titlepage.hpp"

#include "const.hpp"
#include "shape.hpp"

namespace gyp {

titlepage::titlepage(std::string title) : title(std::move(title)) {}

void titlepage::set_button_list(std::vector<button<int>> &&button_list) {
  this->button_list = std::move(button_list);
}

void titlepage::set_title(const std::string &title, Font font, float font_size,
                          float spacing, Color font_color) {
  this->title = title;
  this->font = font;
  this->font_size = font_size;
  this->spacing = spacing;
  this->font_color = font_color;
}

int titlepage::interact_button_list() {
  Vector2 mouse_pos = GetMousePosition();
  for (auto &i : button_list) {
    int button_ret = i.interact(mouse_pos);
    if (button_ret != -1 && button_ret != cinema_call_back->current_scene) {
      cinema_call_back->next_scene = button_ret;
      return 1;
    }
  }
  return -1;
}

void titlepage::draw() {
  vector2d title_size(MeasureTextEx(font, title.c_str(), font_size, spacing));
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(final_color);
    DrawTexture(background, DEFAULT_WIDTH / 2 - background.width / 2,
                DEFAULT_HEIGHT / 2 - background.height / 2, WHITE);
    int ret = interact_button_list();
    DrawTextEx(font, title.c_str(),
               vector2d(DEFAULT_WIDTH / 2 - title_size.x / 2,
                        DEFAULT_HEIGHT / 2 - title_size.y / 2)
                   .ray_vector2d(),
               font_size, spacing, font_color);
    EndDrawing();
    if (ret != -1) {
      return;
    }
  }
}

} // namespace gyp
