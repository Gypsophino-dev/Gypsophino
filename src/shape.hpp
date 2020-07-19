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
  rectangle(const rectangle &a);
  rectangle(rectangle &&a) noexcept;
  rectangle &operator=(const rectangle &a);
  rectangle &operator=(rectangle &&a);
  ~rectangle() = default;
  Rectangle ray_rectanlge() const;
};
} // namespace gyp
