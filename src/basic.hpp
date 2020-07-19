#pragma once

#include <array>
#include <memory>
#include <raylib.h>
#include <string>
#include <utility>
#include <vector>
#include "shape.hpp"

namespace gyp {
struct statue : public rectangle {
  Color color;
  Image image;
  std::string name;
  statue();
  ~statue();
};

struct sprite : public statue {
  vector2d velocity;
  sprite();
  ~sprite();
  void update(int t);
};

class container : public rectangle {
private:
  std::array<std::unique_ptr<container>, 2> child;

public:
  int split_pos;
  int is_horizontal;
  container();
  container(const container &a);
  container(container &&a) noexcept;
  container(int pos_x, int pos_y, int width, int height);
  container(int pos_x, int pos_y, int width, int height, int split_pos, int is_horizontal);
  ~container();
  container &operator=(const container &a);
  container &operator=(container &&a);
  int split(int split_p, int is_h);
};
} // namespace gyp
