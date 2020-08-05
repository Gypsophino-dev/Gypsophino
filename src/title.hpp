#pragma once

#include "control.hpp"
#include "scene.hpp"
#include <vector>

namespace gyp {

class title : public scene {
private:
  std::vector<button<int>> button_list;

public:
  title() = default;
  explicit title(std::string title_name);
  // void set_button_list(const button& style, std::vector<std::string>&&
  // string_list);
  // Setter
  void set_button_list(std::vector<button<int>> &&button_list);
  // Method
  int interact_button_list();
  void draw() override;
};

} // namespace gyp
