#include "scene.hpp"
#include "game.hpp"
#include "const.hpp"

int main() {
  InitWindow(gyp::DEFAULT_WIDTH, gyp::DEFAULT_HEIGHT, "Gypsophino");
  SetTargetFPS(60);
  gyp::scene test_scene(BLACK, WHITE, 120, 20);
  gyp::game test_game("./song_maps/song_map_db.json");
  test_scene.body = test_game;
  test_scene.enter();
  test_scene.draw();
  test_scene.leave();
  return 0;
}
