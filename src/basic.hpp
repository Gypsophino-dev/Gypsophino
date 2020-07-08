#ifndef _BASIC_HPP_
#define _BASIC_HPP_

#include <raylib.h>
#include <vector>
#include <string>
#include <utility>

namespace gyp {
  struct statue {
    int height;
    int width;
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
  template <typename _Tp>
  struct contain : statue {
    std::vector<_Tp> content;
  };
}

#endif // _BASIC_HPP_
