#pragma once

#include "scene.hpp"
#include "song_map.hpp"
#include "playground.hpp"
#include "window.hpp"

#include <vector>

namespace gyp {

class game : public scene {
  // A ultimately bit class which will contain everything except story and
  // settings, song selection
private:
  song_map_db song_database;
  bool is_paused;
  window* window_call_back;

public:
  playground plg;

  // Constructor & Destructor
  explicit game(const std::string& song_db_path, window* window_call_back);
  ~game() = default;
  // Setter
  void set_window_call_back(window* window_call_back);
  // Method
  void load(int song_index);
  void load(int song_index, int fps);
  int interact();
  void draw() override;
};

} // namespace gyp
