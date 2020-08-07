#pragma once

#include "shape.hpp"

namespace gyp {

struct text {
private:
  std::string content;
public:
  enum anchor {
    left_up,
    center_up,
    right_up,
    left,
    center,
    right,
    left_down,
    center_down,
    right_down,
  };
  vector2d pos;
  anchor anc;
  Font font;
  float size;
  float spacing;
  Color color;

  text();
  ~text();
  // Setter
  void set_content(const std::string& content);
  void draw();
};

} // namespace gyp
