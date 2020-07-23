#include "score.hpp"

namespace gyp {
// class parabolic_func:
double parabolic_func::operator()(int hit_time, int target_time) {
  double raw_score = -(target_time - hit_time) * (target_time - hit_time) + 1;
  return std::max(static_cast<double>(0), raw_score);
}
} // namespace gyp
