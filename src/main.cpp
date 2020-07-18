#include <raylib.h>
#include <utility>
#include "song_map.hpp"
#include "const.hpp"
#include "control.hpp"
using gyp::button_status;
using gyp::button;
using gyp::song_map_db;
using gyp::song_map;

void draw_borader(int track_number) {
  int block_width = 200;
  int boarder_width = 10;
  int boarder_height = gyp::DEFAULT_HEIGH;
  int intX = gyp::DEFAULT_WIDTH / 2;
  int intY = 0;
  for (int i = 0; i < track_number + 1; i++)
    DrawRectangle(intX + (i - 2) * block_width, intY, boarder_width, boarder_height, BLACK);
}

int main(int argc, const char * argv[]) {
  // Command line argument process

  // Init the window
  InitWindow(gyp::DEFAULT_WIDTH, gyp::DEFAULT_HEIGH, "Gypsophino");
  InitAudioDevice();
  SetTargetFPS(60);
  Music scarlet_faith = LoadMusicStream("./song_maps/scarlet_faith.mp3");
  PlayMusicStream(scarlet_faith);
  int current_time = 0;
  song_map_db smpdb;
  smpdb.load("./song_maps/song_map_db.json");
  song_map smp = smpdb[0];
  int block_width = 200;
  int block_height = 50;
  button test_button(std::make_pair(50, 50), 100, 25, std::string("Test button"));
  button_status bs = gyp::normal;

  // Main loop
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawFPS(0, 0);
    UpdateMusicStream(scarlet_faith);
    Vector2 mouse_pos = GetMousePosition();
    test_button.update(mouse_pos);
    test_button.draw();
    DrawText(std::to_string(mouse_pos.x).c_str(), 50, 100, 14, BLUE);
    DrawText(std::to_string(mouse_pos.y).c_str(), 50, 150, 14, BLUE);
    DrawText("Button status", 50, 200, 14, BLUE);
    DrawText(std::to_string(static_cast<int>(test_button.status)).c_str(), 50, 250, 14, BLUE);
    draw_borader(smp.track_number);
    current_time += 10;
    for (int i = 0; i < smp.track_number; i++) {
      for (int j = 0; j < (int)smp.notes[i].size(); j++) {
        int intX = gyp::DEFAULT_WIDTH / 2;
        int intY = gyp::DEFAULT_HEIGH - (smp.notes[i][j] - current_time);
        if (intY < 0 || intY > gyp::DEFAULT_HEIGH)
          continue;
        else
          DrawRectangle(intX + (i - 2) * block_width, intY, block_width, block_height, BLACK);
      }
    }
    EndDrawing();
  }
  return 0;
}
