#include "song_map.hpp"

namespace gyp {
  template <typename Compare>
  void song_map_db::sort(Compare comp) {
    std::sort(content.begin(), content.end(), comp);
  }
  song_map& song_map_db::operator[](size_t index) {
    return content[index];
  }
}
