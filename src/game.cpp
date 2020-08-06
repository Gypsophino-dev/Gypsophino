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

/*
void game::interact() {
  if (IsKeyDown(KEY_D)) {
#ifndef RELEASE
    std::cout << "d" << std::endl;
#endif
    plg[0].draw_pressed();
  }
  if (IsKeyDown(KEY_F)) {
#ifndef RELEASE
    std::cout << "f" << std::endl;
#endif
    plg[1].draw_pressed();
  }
  if (IsKeyDown(KEY_J)) {
#ifndef RELEASE
    std::cout << "j" << std::endl;
#endif
    plg[2].draw_pressed();
  }
  if (IsKeyDown(KEY_K)) {
#ifndef RELEASE
    std::cout << "k" << std::endl;
#endif
    plg[3].draw_pressed();
  }
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
    if (IsKeyPressed(KEY_R)) {
      plg.restart();
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
*/

void game::interact() {
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
}

void game::draw() {
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(final_color);
    DrawTexture(background, DEFAULT_WIDTH / 2 - background.width / 2,
                DEFAULT_HEIGHT / 2 - background.height / 2, WHITE);
    plg.draw();
    interact();
    EndDrawing();
  }
}

} // namespace gyp
