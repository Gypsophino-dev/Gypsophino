#pragma once

#include <raylib.h>
#include <vector>
#include <string>

namespace gyp {

class scene {
protected:
  Texture background;
  Color initial_color;
  Color final_color;
  int transient_length; // frame count for the whole transient effect
  int color_stop; // time between each change in color

public:
  scene() = default;
  scene(Color initial_color, Color final_color, int transient_length,
        int color_stop);
  ~scene() = default;
  // Setter
  void set_background_image(std::string path);
  void set_transient(Color initial_color, Color final, int transient_length, int color_stop);
  // Method
  virtual void enter();
  virtual void draw();
  virtual void leave();
};

class cinema : std::vector<scene *> {
  private:
    size_t current_scene;

  public:
    cinema() = default;
    ~cinema() = default;
};

} // namespace gyp
