#pragma once

#include <raylib.h>

namespace gyp {
class rectangle {
public:
  int x;
  int y;
  int width;
  int height;
  rectangle();
  rectangle(int posX, int posY, int width, int height);
//  rectangle(const rectangle &a);
//  rectangle(rectangle &&a) noexcept;
//  rectangle &operator=(const rectangle &a);
//  rectangle &operator=(rectangle &&a);
  ~rectangle() = default;
  [[nodiscard]] Rectangle ray_rectangle() const;
};

struct vector2d {
public:
  int x;
  int y;
  vector2d();
  vector2d(int x, int y);
  ~vector2d() = default;
  [[nodiscard]] Vector2 ray_vector2d() const;
};

} // namespace gyp
