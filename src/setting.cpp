#include "setting.hpp"

#include <cmath>
#include <utility>
#include <string>

#ifndef RELEASE
#include <iostream>
#endif // RELEASE

namespace gyp {

setting::setting(std::vector<button<int>> button_list, window *window_call_back)
    : button_list(std::move(button_list)), window_call_back(window_call_back) {}

void setting::set_button_list(const std::vector<button<int>> &button_list) {
  this->button_list = button_list;
}

void setting::set_window_call_back(window *window_call_back) {
  this->window_call_back = window_call_back;
}

int setting::interact_button_list() {
  Vector2 mouse_pos = GetMousePosition();
  for (auto &i : button_list) {
    int button_ret = i.interact(mouse_pos);
    if (button_ret != -1) {
      return button_ret;
    }
  }
  return -1;
}

void setting::draw() {
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(final_color);
    float current_volume = window_call_back->get_volume() * 100;
    std::string current_volume_str = std::to_string(static_cast<int>(std::round(current_volume)));
    vector2d current_volume_size(MeasureTextEx(GetFontDefault(), current_volume_str.c_str(), 20.0F, 1.5F));
    DrawTexture(background, DEFAULT_WIDTH / 2 - background.width / 2,
                DEFAULT_HEIGHT / 2 - background.height / 2, WHITE);
    DrawTextEx(GetFontDefault(), current_volume_str.c_str(),
               vector2d(DEFAULT_WIDTH / 2 - current_volume_size.x / 2,
                        DEFAULT_HEIGHT / 2 - current_volume_size.y / 2).ray_vector2d(),
               20.0F, 1.5F, BLACK);
    int ret = interact_button_list();
    EndDrawing();
    if (ret != -1) {
#ifndef RELEASE
        std::cerr << "[Debug] setting_page draw ret: " << ret << std::endl;
#endif // RELEASE
      if (ret == 0) {
        window_call_back->change_volume(-0.1F);
      } else if (ret == 1) {
        window_call_back->change_volume(0.1F);
      } else if (ret == 2) {
        cinema_call_back->next_scene = cinema_call_back->prev_scene;
        return;
      }
    }
  }
}

} // namespace gyp
