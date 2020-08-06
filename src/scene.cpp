#include "scene.hpp"

#include "const.hpp"
#include "game.hpp"

namespace gyp {

void scene::set_background_image(std::string path = "res/background.png") {
  Image bg_img = LoadImage(path.c_str());
  ImageResize(&bg_img, bg_img.width / bg_img.height * DEFAULT_HEIGHT,
              DEFAULT_HEIGHT);
  background = LoadTextureFromImage(bg_img);
  UnloadImage(bg_img);
}

void scene::set_transient(Color initial_color, Color final_color,
                          int transient_length, int color_stop) {
  this->initial_color = initial_color;
  this->final_color = final_color;
  this->transient_length = transient_length;
  this->color_stop = color_stop;
}

scene::scene(Color initial_color, Color final_color, int transient_length,
             int color_stop)
    : initial_color(initial_color), final_color(final_color),
      transient_length(transient_length), color_stop(color_stop) {
  set_background_image();
}

void scene::enter() {
  int frame_count = 0;
  float alpha_step = (1.0F) / static_cast<float>(transient_length) *
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

void scene::draw() {}

void scene::leave() {
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
