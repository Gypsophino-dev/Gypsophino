#include "setting.hpp"

#include <utility>

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
    if (button_ret != -1 && button_ret != cinema_call_back->current_scene) {
      cinema_call_back->next_scene = button_ret;
      return 1;
    }
  }
  return -1;
}

void setting::draw() {
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(final_color);
    DrawTexture(background, DEFAULT_WIDTH / 2 - background.width / 2,
                DEFAULT_HEIGHT / 2 - background.height / 2, WHITE);
    int ret = interact_button_list();
    EndDrawing();
    if (ret != -1) {
      return;
    }
  }
}

} // namespace gyp
