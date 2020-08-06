#pragma once

#include "control.hpp"
#include "scene.hpp"

namespace gyp {

class slideshow : public scene {
private:
  timer<int> timeout;

public:
  slideshow();
  explicit slideshow(int timeout);
  ~slideshow() = default;
  // Setter
  void set_timeout(int timeout);
  void set_call_back(int before, int after);
  // Method
  void draw() override;
};

}  // namespace gyp
