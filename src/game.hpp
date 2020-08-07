#pragma once

#include "scene.hpp"
#include "song_map.hpp"
#include "playground.hpp"

#include <vector>

namespace gyp {

class game : public scene {
  // A ultimately bit class which will contain everything except story and
  // settings, song selection
private:
  song_map_db song_database;
  bool is_paused;

public:
  playground plg;
  explicit game(const std::string& song_db_path);
  ~game() = default;
  void load(int song_index);
  int interact();
  void draw() override;
};

} // namespace gyp
