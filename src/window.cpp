#include "window.hpp"

namespace gyp {

window::window() {}

window::window(int width, int height, std::string window_title, int fps)
    : width(width), height(height), window_title(std::move(window_title)),
      fps(fps), is_initialized(false) {
  InitWindow(width, height, window_title.c_str());
}

window::~window() {
  CloseWindow();
}

void window::set_size(int width, int height) {
  this->width = width;
  this->height = height;
  SetWindowSize(width, height);
}

void window::set_title(const std::string& window_title) {
  this->window_title = window_title;
  SetWindowTitle(window_title.c_str());
}

void window::set_fps(int fps) {
  this->fps = fps;
  SetTargetFPS(fps);
}

[[nodiscard]] int window::get_fps() const {
  return fps;
}

[[nodiscard]] vector2d window::get_size() const {
  return vector2d(width, height);
}

[[nodiscard]] int window::get_width() const {
  return width;
}

[[nodiscard]] int window::get_height() const {
  return height;
}

[[nodiscard]] std::string window::get_window_title() const {
  return window_title;
}

void window::detect() {
}

int window::init() {
  if (!is_initialized) {
    InitWindow(width, height, window_title.c_str());
    int check_cnt = 0;
    while (!IsWindowReady() && check_cnt < 20) {
      ;
    }
    if (IsWindowReady()) {
      is_initialized = true;
      return 0;
    }
    is_initialized = false;
    return 1;
  }
  return 2;
}

} // namespace gyp
