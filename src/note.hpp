#pragma once

#include "basic.hpp"
#include <raylib.h>

namespace gyp {

class note : public sprite {
public:
  int hit_time; // In us
  note();
  note(int hit_time, int speed);
  ~note() = default;
  void draw();
};

class slide {
public:
  note start;
  note end;
  Color color;
  Image image;
  slide();
  ~slide();
};

} // namespace gyp
