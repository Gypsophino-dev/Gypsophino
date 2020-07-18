#include "basic.hpp"
#include <memory>
#include <utility>

namespace gyp {
statue::statue() : width(-1), height(-1) {}
statue::~statue() = default;
sprite::sprite() = default;
sprite::~sprite() = default;
void sprite::update(int t) {
  pos.first += t * velocity.first;
  pos.second += t * velocity.second;
}

container::container() {
  height = -1;
  width = -1;
  pos.first = -1;
  pos.second = -1;
  split_pos = -1;
  is_horizontal = -1;
}

container::container(std::pair<int, int> p, int w, int h)
    : pos(std::move(p)), width(w), height(h), split_pos(-1), is_horizontal(-1) {
}

container::container(std::pair<int, int> p, int w, int h, int s, int is_h)
    : pos(std::move(p)), width(w), height(h), split_pos(s),
      is_horizontal(is_h) {}

container::~container() = default;

int container::split(int split_p, int is_h) {
  split_pos = split_p;
  is_horizontal = is_h;
  if (child[0] == nullptr && child[1] == nullptr) {
    if (is_h != 0) {
      child[0] =
          std::make_unique<container>(pos, width, split_pos - pos.second);
      child[1] =
          std::make_unique<container>(std::make_pair(pos.first, split_pos),
                                      width, pos.first + height - split_pos);
    } else {
      child[0] =
          std::make_unique<container>(pos, split_pos - pos.first, height);
      child[1] =
          std::make_unique<container>(std::make_pair(split_pos, pos.second),
                                      pos.first + width - split_pos, height);
    }
    return 0;
  }
  return 1;
}
} // namespace gyp
