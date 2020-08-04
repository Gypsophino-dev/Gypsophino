#include "scene.hpp"
#include "game.hpp"
#include "const.hpp"

int main() {
  InitWindow(gyp::DEFAULT_WIDTH, gyp::DEFAULT_HEIGHT, "Gypsophino");
  SetTargetFPS(60);
  gyp::game test_game("./song_maps/song_map_db.json");
  test_game.set_background_image("res/background.png");
  test_game.set_transient(BLACK, WHITE, 120, 20);
  test_game.enter();
  test_game.draw();
  test_game.leave();
  return 0;
}
