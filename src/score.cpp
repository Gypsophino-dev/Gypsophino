#include "score.hpp"

namespace gyp {

// class parabolic_func:
parabolic_func::parabolic_func(int hit_time) : hit_time(hit_time) {}

double parabolic_func::operator()(int target_time) {
  double raw_score = -(target_time - hit_time) * (target_time - hit_time) + 1;
  return std::max(static_cast<double>(0), raw_score);
}

// class score:
template <typename Calc> score<Calc>::score() {
  letter_grade_table[0] = std::make_pair(std::string("D"), 70);
  letter_grade_table[1] = std::make_pair(std::string("C"), 80);
  letter_grade_table[2] = std::make_pair(std::string("B"), 90);
  letter_grade_table[3] = std::make_pair(std::string("A"), 95);
  letter_grade_table[4] = std::make_pair(std::string("S"), 99);
  letter_grade_table[5] = std::make_pair(std::string("SS"), 100);
  total = GYP_MAX_SCORE;
  current = 0;
}

template <typename Calc> score<Calc>::~score() = default;

template <typename Calc>
void score<Calc>::update(int hit_time, int target_time) {
  Calc fn;
  current += fn(hit_time, target_time);
}

template <typename Calc> std::string score<Calc>::get_letter_grade() {
  for (int i = 0; i < GRADE_KIND - 1; i++) {
    if (current < letter_grade_table.at(i).second) {
      return letter_grade_table.at(i).first;
    }
  }
  return letter_grade_table[GRADE_KIND - 1].first;
}

template <typename Calc>
void score<Calc>::draw(const std::pair<int, int>& pos, int font_size) {
  DrawText(std::to_string(current).c_str(), pos.first, pos.second, font_size, BLUE);
}
} // namespace gyp
