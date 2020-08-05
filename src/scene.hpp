#pragma once

#include <raylib.h>
#include <vector>
#include <string>

namespace gyp {

class cinema;

class scene {
protected:
  Texture background;
  Color initial_color;
  Color final_color;
  int transient_length; // frame count for the whole transient effect
  int color_stop; // time between each change in color
  cinema* cinema_call_back;

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

enum scene_list { titlepage, settings, gaming, pausing, adventure };

class cinema : std::vector<scene *> {
  public:
    size_t current_scene;
    size_t next_scene;
    cinema() = default;
    ~cinema() = default;
};

} // namespace gyp
