#pragma once

#include "control.hpp"
#include "scene.hpp"
#include "window.hpp"
#include <raylib.h>
#include <vector>

namespace gyp {

class setting : public scene {
private:
  std::vector<button<int>> button_list;
  window *window_call_back;

public:
  setting() = default;
  ~setting() = default;
  setting(std::vector<button<int>> button_list, window *window_call_back);
  // Setter
  void set_button_list(const std::vector<button<int>> &button_list);
  void set_window_call_back(window *window_call_back);
  // Method
  int interact_button_list();
  void draw() override;
};

} // namespace gyp
