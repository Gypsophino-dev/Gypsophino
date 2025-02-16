#pragma once

#include <raylib.h>
#include <string>

#include "shape.hpp"

namespace gyp {

class window {
private:
  int width;
  int height;
  std::string window_title;
  int fps;
  float volume;
  bool is_initialized;

public:
  window() = default;
  window(int width, int heigh, std::string window_title, int fps);
  ~window();
  // Setter
  void set_size(int width, int heigh);
  void set_title(const std::string& window_title);
  void set_fps(int fps);
  void set_volume(float volume);
  void change_volume(float delta);
  // Getter
  [[nodiscard]] int get_fps() const;
  [[nodiscard]] vector2d get_size() const;
  [[nodiscard]] int get_width() const;
  [[nodiscard]] int get_height() const;
  [[nodiscard]] std::string get_window_title() const;
  [[nodiscard]] float get_volume() const;
  // Method
  // TODO(tonyfettes): implement detect.
  void detect(); // Planned
  int init(); // -> 0: Succeed, 1: Failed, 2: Already initialized
};

} // namespace gyp
