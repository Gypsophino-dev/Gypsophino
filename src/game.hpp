#pragma once

#include "basic.hpp"
#include "const.hpp"
#include "shape.hpp"
#include "song_map.hpp"
#include "score.hpp"
#include <memory>
#include <raylib.h>
#include <vector>

namespace gyp {

class note : public sprite {
public:
  int hit_time; // In us
  note();
  note(int hit_time, int speed);
  ~note() = default;
  void draw();
};

class slide {
public:
  note start;
  note end;
  Color color;
  Image image;
  slide();
  ~slide();
};

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

enum playground_status { playing, paused, not_running };

class playground : public std::vector<track>, public rectangle {
private:
  // Geometry
  int track_number;

  // Playground style
  Color outline;
  int thick;

  int current_time;
  int speed;
  const song_map * song;
  Music music;
  playground_status status;
  bool is_initialized;

public:
  // Constructor & Desttructor
  playground();
  /*
  playground(int pos_x, int pos_y, int width, int height, int track_number,
             Color outline_color, int outline_thickness, Color inner_fill_color,
             Color inner_outline_color, int inner_thickness);
  */
  ~playground();

  // Setter
  void set_geometry(int pos_x, int pos_y, int width, int height, int track_number);
  void set_playground_style(Color outline_color, int outline_thickness);
  void set_speed(int speed);
  // CAUTION: set_track() must be called after setter above !!
  void set_track(Color fill_color, Color outline_color, int outline_thickness);

  // Method
  // CAUTION: Any method must be called after set_track(),
  //          for performance, these function will not examine
  //          is_initialized before they run.
  // Contain: [i].set_interator [i].init()
  // CAUTION: Init() must be run at first.
  void init();
  void load(const song_map * selected_song);
  void play(); // play a single frame
  void pause(); // pause for a single frame
  void quit();
  void draw() const;
};

class game {
  // A ultimately bit class which will contain everything except story and
  // settings, song selection
private:
  song_map_db song_database;

public:
  game();
  ~game();
};
} // namespace gyp
