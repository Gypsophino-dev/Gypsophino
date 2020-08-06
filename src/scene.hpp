#pragma once

#include <raylib.h>
#include <vector>
#include <string>

namespace gyp {

class cinema;

class scene {
protected:
  Texture background{};
  Color initial_color{};
  Color final_color{};
  int transient_length{}; // frame count for the whole transient effect
  int color_stop{}; // time between each change in color
  cinema* cinema_call_back{};

public:
  scene() = default;
  scene(Color initial_color, Color final_color, int transient_length,
        int color_stop);
  ~scene() = default;
  // Setter
  void set_background_image(const std::string & path);
  void set_transient(Color initial_color, Color final, int transient_length, int color_stop);
  void set_cinema_call_back(cinema * cinema_call_back);
  // Method
  virtual void enter();
  virtual void draw();
  virtual void leave();
};

//enum scene_list { title_page, settings, gaming, pausing, adventure };

class cinema : public std::vector<scene *> {
  public:
    int prev_scene;
    int current_scene;
    int next_scene;
    cinema();
    ~cinema() = default;
    // Method
    void switch_to(int index);
    void switch_to(int from, int to);
    void play();
};

} // namespace gyp
