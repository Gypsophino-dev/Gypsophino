#pragma once

#include "control.hpp"
#include "scene.hpp"
#include <vector>

namespace gyp {

class titlepage : public scene {
private:
  Font font{};
  float font_size{};
  float spacing{};
  Color font_color{};
  std::string title;
  std::vector<button<int>> button_list;

public:
  titlepage() = default;
  ~titlepage() = default;
  explicit titlepage(std::string title);
  // void set_button_list(const button& style, std::vector<std::string>&&
  // string_list);
  // Setter
  void set_button_list(std::vector<button<int>> &&button_list);
  void set_title(const std::string& title, Font font, float font_size, float spacing, Color font_color);
  // Method
  int interact_button_list();
  void draw() override;
};

} // namespace gyp
