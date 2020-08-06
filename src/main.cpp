#include "scene.hpp"
#include "game.hpp"
#include "const.hpp"
#include "title.hpp"
#include <vector>

int main() {
  InitWindow(gyp::DEFAULT_WIDTH, gyp::DEFAULT_HEIGHT, "Gypsophino");
  SetTargetFPS(60);
  gyp::cinema game_cinema;
  gyp::game test_game("./song_maps/song_map_db.json");
  test_game.set_background_image("res/background.png");
  test_game.set_transient(BLACK, WHITE, 120, 20);
  test_game.set_cinema_call_back(&game_cinema);
  gyp::title starter;
  std::vector<gyp::button<int>> button_initial_list;
  gyp::button<int> start_button;
  start_button.set_color(std::array<Color, 3>{BLACK, GRAY, BLUE}, std::array<Color, 3>{WHITE, WHITE, WHITE});
  start_button.set_geometry(gyp::DEFAULT_WIDTH / 2 - 100, gyp::DEFAULT_HEIGHT / 2 - 50, 200, 100);
  start_button.set_status(gyp::normal);
  start_button.set_text(GetFontDefault(), 20.0F, 1.5F, std::array<std::string, 3>{"Start", "Start", "Start"});
  start_button.set_call_back(std::array<int, 4>{-1, 1, -1, -1});
  button_initial_list.push_back(start_button);
  starter.set_button_list(std::move(button_initial_list));
  starter.set_background_image("res/background.png");
  starter.set_transient(BLACK, WHITE, 120, 20);
  starter.set_cinema_call_back(&game_cinema);
  game_cinema.push_back(static_cast<gyp::scene *>(&starter));
  game_cinema.push_back(static_cast<gyp::scene *>(&test_game));
  game_cinema.play();
  return 0;
}
