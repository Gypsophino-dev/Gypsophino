#include "scene.hpp"

#include "const.hpp"
#include "game.hpp"

namespace gyp {

scene::scene(Color initial_color, Color final_color, int transient_length,
             int color_stop)
    : initial_color(initial_color), final_color(final_color),
      transient_length(transient_length), color_stop(color_stop) {}

void scene::enter() {
  int frame_count = 0;
  float alpha_step = (1.0F) / static_cast<float>(transient_length) *
                     static_cast<float>(color_stop);
  Color current_color = Fade(final_color, 0.0F);
  while (!WindowShouldClose() && frame_count < transient_length) {
    BeginDrawing();
    ClearBackground(initial_color);
    DrawRectangle(0, 0, gyp::DEFAULT_WIDTH, gyp::DEFAULT_HEIGHT, current_color);
    frame_count++;
    if (frame_count % color_stop == 0) {
      current_color =
          Fade(final_color, alpha_step * static_cast<float>(frame_count / color_stop));
    }
    EndDrawing();
  }
}

void scene::draw() {
  if (body.type() == typeid(game)) {
    std::any_cast<game>(body).load();
    std::any_cast<game>(body).draw();
  }
}

void scene::leave() {
  int frame_count = 0;
  float alpha_step = (1.0F) / static_cast<float>(transient_length) *
                     static_cast<float>(color_stop);
  Color current_color = Fade(initial_color, 0.0F);
  while (!WindowShouldClose() && frame_count < transient_length) {
    BeginDrawing();
    ClearBackground(final_color);
    DrawRectangle(0, 0, gyp::DEFAULT_WIDTH, gyp::DEFAULT_HEIGHT, current_color);
    frame_count++;
    if (frame_count % color_stop == 0) {
      current_color =
          Fade(initial_color, alpha_step * static_cast<float>(frame_count / color_stop));
    }
    EndDrawing();
  }
}

} // namespace gyp
