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

vector2d::vector2d() : x(0), y(0) {}

vector2d::vector2d(int x, int y) : x(x), y(y) {}

vector2d::vector2d(Vector2 other)
    : x(static_cast<int>(other.x)), y(static_cast<int>(other.y)) {}

[[nodiscard]] Vector2 vector2d::ray_vector2d() const {
  Vector2 ret;
  ret.x = static_cast<float>(x);
  ret.y = static_cast<float>(y);
  return ret;
}

} // namespace gyp
