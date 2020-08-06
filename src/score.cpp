#include "score.hpp"

namespace gyp {
// class parabolic_func:

void parabolic_func::set_error(int error_time) {
  this->error_time = error_time;
}

[[nodiscard]] int parabolic_func::get_error() const { return error_time; }

float parabolic_func::operator()(int hit_time, int target_time) const {
  float raw_score = 1 - static_cast<float>((target_time - hit_time) * (target_time - hit_time)) / static_cast<float>(error_time * error_time);
  return std::max(static_cast<float>(0), raw_score);
}

} // namespace gyp
