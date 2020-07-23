#pragma once

#include "shape.hpp"
#include "score.hpp"
#include "note.hpp"
#include <raylib.h>
#include <vector>

namespace gyp {
class track : rectangle {
private:
  using vci = std::vector<int>::const_iterator;
  // Track Style
  Color fill;
  Color outline;
  int thick;
  // Node Style
  note note_style;
  // Timing
  int current_time; // lower limit for note to display
  int visible_time; // upper limit for note to display
  int error_time;   // max time difference
  // Speed (Setted by set_geometry())
  int speed;
  // Iterator
  bool is_iterator_set;
  vci notes_begin;   // For drawing
  vci notes_end;     // For drawing
  vci notes_current; // For drawing
  vci notes_visible; // For drawing
  // Score
  score<parabolic_func> track_score;

public:
  // Constructor & Destructor
  track();
  //  track(const track &other);
  //  track(track &&other) noexcept;
  ~track() = default;

  // Setter
  void set_geometry(int pos_x, int pos_y, int width, int height);
  void set_track_style(Color fill_color, Color outline_color, int outline_thickness);
  void set_note_style(int height, Color color);
  void set_note_style(int height, Image image);
  void set_time(int current_time, int visible_time, int error_time);
  void set_speed(int speed);
  void set_iterator(vci iter_begin, vci iter_end);

  // Method
  int init();
  void update();
  void sync(int current_time);
  void draw() const;
  void hit(); // just for update the canvas, not for score
};

} // namespace gyp
