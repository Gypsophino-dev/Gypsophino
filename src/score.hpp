#ifndef _SCORE_HPP_
#define _SCORE_HPP_

#include "basic.hpp"
#include <vector>
#include <string>

namespace gyp {
  struct letter_grade : statue {
    std::string letter;
  };
  struct character : statue {
    char c;
  };
  class score {
    private:
      std::vector<std::string> letter_grade_table;
    public:
      int total;
      int current;
      std::string letter_grade;
  };
}

#endif // _SCORE_HPP_
