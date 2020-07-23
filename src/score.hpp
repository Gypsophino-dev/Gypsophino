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

class parabolic_func {

public:
  parabolic_func() = default;
  ~parabolic_func() = default;
  double operator()(int hit_time, int target_time);
};

template <typename CalcFunc = parabolic_func>
class score {
private:
  std::array<std::pair<std::string, double>, GRADE_KIND> letter_grade_table;
  std::string letter_grade;
  CalcFunc fn;

public:
  int total;
  double current;
  score() {
    letter_grade_table[0] = std::make_pair(std::string("D"), 70);
    letter_grade_table[1] = std::make_pair(std::string("C"), 80);
    letter_grade_table[2] = std::make_pair(std::string("B"), 90);
    letter_grade_table[3] = std::make_pair(std::string("A"), 95);
    letter_grade_table[4] = std::make_pair(std::string("S"), 99);
    letter_grade_table[5] = std::make_pair(std::string("SS"), 100);
    total = GYP_MAX_SCORE;
    current = 0;
  }
  ~score() = default;
  void add(int hit_time, int target_time) {
    current += fn(hit_time, target_time);
  }
  std::string get_letter_grade() {
    for (int i = 0; i < GRADE_KIND - 1; i++) {
      if (current < letter_grade_table.at(i).second) {
        return letter_grade_table.at(i).first;
      }
    }
    return letter_grade_table[GRADE_KIND - 1].first;
  }
  void draw(const std::pair<int, int>& pos, int font_size) {
    DrawText(std::to_string(current).c_str(), pos.first, pos.second, font_size, BLUE);
  }
  void draw(const std::pair<int, int>& pos, int width, int height);
};

} // namespace gyp
