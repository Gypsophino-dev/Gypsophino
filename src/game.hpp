#pragma once

#include "song_map.hpp"

namespace gyp {

class game {
  // A ultimately bit class which will contain everything except story and
  // settings, song selection
private:
  song_map_db song_database;

public:
  game();
  ~game();
};
} // namespace gyp
