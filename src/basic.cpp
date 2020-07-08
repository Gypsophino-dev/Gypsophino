#include "basic.hpp"

namespace gyp {
  statue::statue() {}
  statue::~statue() {}
  sprite::sprite() {}
  sprite::~sprite() {}
  void sprite::update(int t) {
    pos.first += t * velocity.first;
    pos.second += t * velocity.second;
  }
}
