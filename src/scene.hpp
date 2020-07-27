#pragma once

#include <raylib.h>
#include <vector>
#include <any>

namespace gyp {

class scene {
private:
  Image background;
  Color initial_color;
  Color final_color;
  int transient_length; // frame count for the whole transient effect
  int color_stop; // time between each change in color

public:
  std::any body;
  scene() = default;
  scene(Color initial_color, Color final_color, int transient_length,
        int color_stop);
  ~scene() = default;
  void enter();
  void draw();
  void leave();
};

class cinema : std::vector<scene> {
  private:
    size_t current_scene;

  public:
    cinema() = default;
    ~cinema() = default;
};

} // namespace gyp
