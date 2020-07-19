#include "basic.hpp"
#include <memory>
#include <utility>

namespace gyp {
statue::statue() = default; // Default constructor of rectangle set -1
statue::~statue() = default;
sprite::sprite() = default;
sprite::~sprite() = default;
void sprite::update(int t) {
  x += t * velocity.x;
  y += t * velocity.y;
}

container::container()
  : split_pos(-1), is_horizontal(-1) {}

container::container(int pos_x, int pos_y, int w, int h)
    : split_pos(-1), is_horizontal(-1) {
  x = pos_x;
  y = pos_y;
  width = w;
  height = h;
}

container::container(int pos_x, int pos_y, int w, int h, int sp_pos, int is_h)
    : split_pos(sp_pos), is_horizontal(is_h) {
  x = pos_x;
  y = pos_y;
  width = w;
  height = h;
}

container::~container() = default;

int container::split(int split_p, int is_h) {
  split_pos = split_p;
  is_horizontal = is_h;
  if (child[0] == nullptr && child[1] == nullptr) {
    if (is_h != 0) {
      child[0] = std::make_unique<container>(x, y, width, split_pos - y);
      child[1] = std::make_unique<container>(x, split_pos, width,
                                             x + height - split_pos);
    } else {
      child[0] = std::make_unique<container>(x, y, split_pos - x, height);
      child[1] = std::make_unique<container>(split_pos, y,
                                             x + width - split_pos, height);
    }
    return 0;
  }
  return 1;
}
} // namespace gyp
