#include "shape.hpp"

namespace gyp {
rectangle::rectangle() : x(-1), y(-1), width(-1), height(-1) {}
rectangle::rectangle(int posX, int posY, int width, int height)
    : x(posX), y(posY), width(width), height(height) {}
Rectangle rectangle::ray_rectangle() const {
  Rectangle ret;
  ret.x = static_cast<float>(x);
  ret.y = static_cast<float>(y);
  ret.width = static_cast<float>(width);
  ret.height = static_cast<float>(height);
  return ret;
}
} // namespace gyp
