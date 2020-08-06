#include "scene.hpp"
#include "game.hpp"
#include "const.hpp"
#include "titlepage.hpp"
#include "slideshow.hpp"

#include <vector>
#include <array>
#include <string>

int main() {
  InitWindow(gyp::DEFAULT_WIDTH, gyp::DEFAULT_HEIGHT, "Gypsophino");
  SetTargetFPS(60);
  gyp::cinema game_cinema;
  gyp::game test_game("./song_maps/song_map_db.json");
  test_game.set_background_image("res/background.png");
  test_game.set_transient(BLACK, WHITE, 60, 1);
  test_game.set_cinema_call_back(&game_cinema);
  gyp::titlepage starter;
  std::vector<gyp::button<int>> button_initial_list;
  gyp::button<int> start_button;
  start_button.set_color(std::array<Color, 3>{BLACK, GRAY, BLUE}, std::array<Color, 3>{WHITE, WHITE, WHITE});
  start_button.set_geometry(gyp::DEFAULT_WIDTH / 2 - 100, (3 * gyp::DEFAULT_HEIGHT) / 4 - 50, 200, 100);
  start_button.set_status(gyp::normal);
  start_button.set_text(GetFontDefault(), 20.0F, 1.5F, std::array<std::string, 3>{"Start", "Start", "Start"});
  start_button.set_call_back(std::array<int, 4>{-1, 2, -1, -1});
  button_initial_list.push_back(start_button);
  starter.set_button_list(std::move(button_initial_list));
  starter.set_background_image("res/background.png");
  starter.set_transient(BLACK, WHITE, 60, 1);
  starter.set_cinema_call_back(&game_cinema);
  starter.set_title("Gypsophino", GetFontDefault(), 100.0F, 10.0F, BLACK);
  game_cinema.push_back(static_cast<gyp::scene *>(&starter));
  game_cinema.push_back(static_cast<gyp::scene *>(&test_game));
  // int init_size = game_cinema.size();
  std::array<gyp::slideshow, 4> interplay;
  for (int i = 0; i < 4; i++) {
    interplay.at(i).set_background_image("res/chap_0" + std::to_string(i + 1) + ".png");
    interplay.at(i).set_transient(BLACK, WHITE, 60, 1);
    interplay.at(i).set_cinema_call_back(&game_cinema);
    interplay.at(i).set_timeout(120);
    interplay.at(i).set_call_back(-1, 1);
    game_cinema.push_back(static_cast<gyp::scene *>(&interplay.at(i)));
  }
  game_cinema.push_back(static_cast<gyp::scene *>(&test_game));
  game_cinema.play();
  return 0;
}
