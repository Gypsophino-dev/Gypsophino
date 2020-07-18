#pragma once

#include <array>
#include <memory>
#include <raylib.h>
#include <string>
#include <utility>
#include <vector>

namespace gyp {
struct statue {
  int width;
  int height;
  std::pair<int, int> pos;
  Color color;
  Image image;
  std::string name;
  statue();
  ~statue();
};

struct sprite : statue {
  std::pair<int, int> velocity;
  sprite();
  ~sprite();
  void update(int t);
};

class container {
private:
  std::array<std::unique_ptr<container>, 2> child;

public:
  std::pair<int, int> pos; // first -> x, second -> y
  int width;               // Max x
  int height;              // Max y
  int split_pos;
  int is_horizontal;
  container();
  container(const container &a);
  container(container &&a) noexcept;
  container(std::pair<int, int> p, int w, int h);
  container(std::pair<int, int> p, int w, int h, int s, int is_h);
  ~container();
  container &operator=(const container &a);
  container &operator=(container &&a);
  int split(int split_p, int is_h);
};
} // namespace gyp
