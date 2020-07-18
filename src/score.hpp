#pragma once

#include "basic.hpp"
#include <array>
#include <string>

namespace gyp {
const int GRADE_KIND = 6;
const int GYP_MAX_SCORE = 1000000;
struct letter_grade : statue {
  std::string letter;
};

struct character : statue {
  char c;
};

struct parabolic_func {
private:
  int hit_time;

public:
  explicit parabolic_func(int hit_time);
  double operator()(int target_time);
};

template <typename CalcFunc = parabolic_func> class score {
private:
  std::array<std::pair<std::string, double>, GRADE_KIND> letter_grade_table;
  std::string letter_grade;

public:
  int total;
  double current;
  score();
  ~score();
  void update(int hit_time, int target_time);
  std::string get_letter_grade();
  void draw(const std::pair<int, int>& pos, int font_size);
  void draw(const std::pair<int, int>& pos, int width, int height);
};

} // namespace gyp
