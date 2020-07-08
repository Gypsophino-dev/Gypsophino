#ifndef _NOTE_HPP_
#define _NOTE_HPP_

#include <utility>
#include <raylib.h>
#include "basic.hpp"

namespace gyp {
  class note : sprite {
    public:
      int hit_time; // In us
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
}

#endif // _NOTE_HPP_
