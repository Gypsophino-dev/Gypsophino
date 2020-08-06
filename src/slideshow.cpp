#include "slideshow.hpp"

namespace gyp {

slideshow::slideshow() {
  this->timeout.set_call_back(std::array<int, 2>{-1, -1});
}

slideshow::slideshow(int timeout) {
  this->timeout.set_count_down(timeout);
  this->timeout.set_call_back(std::array<int, 2>{-1, -1});
}

void slideshow::set_timeout(int timeout) {
  this->timeout.set_count_down(timeout);
}

void slideshow::set_call_back(int before, int after) {
  this->timeout.set_call_back(std::array<int, 2>{before, after});
}

void slideshow::draw() {
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(final_color);
    DrawTexture(background, DEFAULT_WIDTH / 2 - background.width / 2,
                DEFAULT_HEIGHT / 2 - background.height / 2, WHITE);
    int ret = timeout.interact();
    EndDrawing();
    if (ret != -1) {
      cinema_call_back->next_scene = ret;
      return;
    }
  }
}

} // namespace gyp
