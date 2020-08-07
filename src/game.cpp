#include "game.hpp"
#include "const.hpp"

#ifndef RELEASE
#include <iostream>
#endif // RELEASE

namespace gyp {

game::game(const std::string& song_db_path) : is_paused(true) {
  song_database.load(song_db_path);
  const int block_width = 200;
  const int block_height = 50;
  plg.set_geometry(gyp::DEFAULT_WIDTH / 2 - 2 * block_width, 0, 4 * block_width,
                   gyp::DEFAULT_HEIGHT, song_database[0].track_number);
  plg.set_playground_style(BLACK, gyp::DEFAULT_THICKNESS * 2);
  plg.set_speed(gyp::DEFAULT_SPEED * 2);
  // This setter MUST be executed last.
  plg.set_track(Fade(WHITE, 0.8F), gyp::DEFAULT_FG, gyp::DEFAULT_THICKNESS,
                block_height, BLACK);
  plg.init();
  plg.load(&song_database[0], 60);
}

void game::load(int song_index) {
  plg.load(&song_database[song_index], 60);
}

int game::interact() {
  if (is_paused) {
    plg.pause();
  } else {
    plg.play();
  }
  for (auto& i : plg) {
    if (!is_paused) {
      i.interact();
    }
  }
  if (IsKeyPressed(KEY_P)) {
    is_paused = !is_paused;
  }
  if (IsKeyPressed(KEY_R)) {
    plg.restart();
  }
  if (IsKeyPressed(KEY_Q)) {
    plg.quit();
    return 1;
  }
  return 0;
}

void game::draw() {
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(final_color);
    DrawTexture(background, DEFAULT_WIDTH / 2 - background.width / 2,
                DEFAULT_HEIGHT / 2 - background.height / 2, WHITE);
    plg.draw();
    int ret = interact();
    EndDrawing();
    if (ret == 1) {
      return;
    }
  }
}

} // namespace gyp
