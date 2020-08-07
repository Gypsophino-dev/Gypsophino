#include "setting.hpp"

#include <cmath>
#include <utility>
#include <string>

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

void setting::enter() {
  int frame_count = 0;
  float alpha_step = (0.2F) / static_cast<float>(transient_length) *
                     static_cast<float>(color_stop);
  Color current_color = Fade(initial_color, 1.0F);
  while (!WindowShouldClose() && frame_count < transient_length) {
    BeginDrawing();
    ClearBackground(final_color);
    DrawTexture(background, DEFAULT_WIDTH / 2 - background.width / 2,
                DEFAULT_HEIGHT / 2 - background.height / 2, WHITE);
    DrawRectangle(0, 0, gyp::DEFAULT_WIDTH, gyp::DEFAULT_HEIGHT, current_color);
    frame_count++;
    if (frame_count % color_stop == 0) {
      current_color = Fade(
          initial_color,
          1.0F - alpha_step * static_cast<float>(frame_count / color_stop));
    }
    EndDrawing();
  }
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
    DrawRectangle(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT, Fade(BLACK, 0.8F));
    DrawTextEx(GetFontDefault(), current_volume_str.c_str(),
               vector2d(DEFAULT_WIDTH / 2 - current_volume_size.x / 2,
                        DEFAULT_HEIGHT / 2 - current_volume_size.y / 2).ray_vector2d(),
               30.0F, 2.5F, WHITE);
    int ret = interact_button_list();
    EndDrawing();
    if (ret != -1) {
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

void setting::leave() {
  int frame_count = 0;
  float alpha_step = (1.0F) / static_cast<float>(transient_length) *
                     static_cast<float>(color_stop);
  Color current_color = Fade(initial_color, 0.0F);
  while (!WindowShouldClose() && frame_count < transient_length) {
    BeginDrawing();
    ClearBackground(final_color);
    DrawTexture(background, DEFAULT_WIDTH / 2 - background.width / 2,
                DEFAULT_HEIGHT / 2 - background.height / 2, WHITE);
    DrawRectangle(0, 0, gyp::DEFAULT_WIDTH, gyp::DEFAULT_HEIGHT, current_color);
    frame_count++;
    if (frame_count % color_stop == 0) {
      current_color =
          Fade(initial_color,
               alpha_step * static_cast<float>(frame_count / color_stop));
    }
    EndDrawing();
  }
}

} // namespace gyp
