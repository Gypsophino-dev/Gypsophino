#include "note.hpp"

namespace gyp {

note::note() : hit_time(-1) {}

note::note(int hit_t, int speed) : hit_time(hit_t) {
  velocity.x = 0;
  velocity.y = speed;
}

void note::draw() { DrawRectangle(x, y, width, height, color); }

} // namespace gyp
