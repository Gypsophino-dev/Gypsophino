#include "const.hpp"
#include "control.hpp"
#include "game.hpp"
#include "playground.hpp"
#include "song_map.hpp"
#include <raylib.h>
#include <thread>
#include <utility>

#include <iostream>

using gyp::button;
using gyp::button_status;
using gyp::playground;
using gyp::song_map;
using gyp::song_map_db;

int main(int  /*argc*/, const char * /*argv*/[]) {
  // Command line argument process

  // Init the window
  InitWindow(gyp::DEFAULT_WIDTH, gyp::DEFAULT_HEIGH, "Gypsophino");
  InitAudioDevice();
  SetTargetFPS(60);
  song_map_db smpdb;
  smpdb.load("./song_maps/song_map_db.json");
  song_map smp = smpdb[0];
  int block_width = 200;
  int block_height = 50;
  button test_button(50, 50, 100, 25);
  button_status bs = gyp::normal;
  playground plg;
  plg.set_geometry(gyp::DEFAULT_WIDTH / 2 - 2 * block_width, 0, 4 * block_width,
                   gyp::DEFAULT_HEIGH, gyp::DEFAULT_TRACK_NUM);
  plg.set_playground_style(BLACK, 10);
  plg.set_speed(10);
  // This setter MUST be executed last.
  plg.set_track(WHITE, BLACK, 5);
  plg.init();
  plg.load(&smp);
  bool is_paused = true;

  // Main loop
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawFPS(0, 0);
    Vector2 mouse_pos = GetMousePosition();
    DrawText(std::to_string(mouse_pos.x).c_str(), 50, 100, 14, BLUE);
    DrawText(std::to_string(mouse_pos.y).c_str(), 50, 150, 14, BLUE);
    int result = test_button.interact(mouse_pos);
    DrawText(std::to_string(result).c_str(), 50, 300, 20, BLUE);
    test_button.draw();
    DrawText("Button status", 50, 200, 14, BLUE);
    DrawText(std::to_string(static_cast<int>(test_button.get_status())).c_str(), 50,
             250, 14, BLUE);
    if (IsKeyPressed(KEY_D)) {
      std::cout << "d pressed" << std::endl;
      plg[0].hit();
    }
    if (IsKeyPressed(KEY_F)) {
      std::cout << "f pressed" << std::endl;
      plg[1].hit();
    }
    if (IsKeyPressed(KEY_J)) {
      std::cout << "j pressed" << std::endl;
      plg[2].hit();
    }
    if (IsKeyPressed(KEY_K)) {
      std::cout << "k pressed" << std::endl;
      plg[3].hit();
    }
    if (is_paused) {
      plg.pause();
    } else {
      plg.play();
    }
    plg.draw();
    if (result == MOUSE_LEFT_BUTTON || IsKeyPressed(KEY_SPACE)) {
      is_paused = !is_paused;
    }
    EndDrawing();
  }
  return 0;
}
