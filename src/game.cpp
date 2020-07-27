#include "game.hpp"
#include "const.hpp"

namespace gyp {

game::game(std::string song_db_path)
  : is_paused(true) {
  song_database.load(std::move(song_db_path));
  const int block_width = 200;
  const int block_height = 50;
  plg.set_geometry(gyp::DEFAULT_WIDTH / 2 - 2 * block_width, 0, 4 * block_width,
                   gyp::DEFAULT_HEIGHT, gyp::DEFAULT_TRACK_NUM);
  plg.set_playground_style(BLACK, gyp::DEFAULT_THICKNESS * 2);
  plg.set_speed(gyp::DEFAULT_SPEED);
  // This setter MUST be executed last.
  plg.set_track(gyp::DEFAULT_BG, gyp::DEFAULT_FG, gyp::DEFAULT_THICKNESS, block_height, BLACK);
  plg.init();
  plg.load(&song_database[0]);
}

void game::load() {}

void game::interact() {
  if (!is_paused) {
    if (IsKeyPressed(KEY_D)) {
      plg[0].hit();
    }
    if (IsKeyPressed(KEY_F)) {
      plg[1].hit();
    }
    if (IsKeyPressed(KEY_J)) {
      plg[2].hit();
    }
    if (IsKeyPressed(KEY_K)) {
      plg[3].hit();
    }
  }
  if (IsKeyPressed(KEY_SPACE)) {
    is_paused = !is_paused;
  }
  if (is_paused) {
    plg.pause();
  } else {
    plg.play();
  }
}

void game::draw() {
  while (!WindowShouldClose()) {
    BeginDrawing();
    interact();
    plg.draw();
    EndDrawing();
  }
}

} // namespace gyp
