#pragma once

#include "basic.hpp"
#include "const.hpp"
#include "shape.hpp"
#include "song_map.hpp"
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
  using vci = std::vector<int>::const_iterator;
  Color fill;
  Color outline;
  int thick;
  int current_time; // lower limit for note to display
  int visible_time; // upper limit for note to display
  int speed;
  note note_style;
  vci notes_begin;
  vci notes_end;
  vci notes_current;
  vci notes_visible;
public:
  track();
  track(int pos_x, int pos_y, int width, int height, int speed);
  track(int pos_x, int pos_y, int width, int height, int speed,
        Color fill_color, Color outline_color, int outline_thickness);
  //  track(const track &other);
  //  track(track &&other) noexcept;
  ~track() = default;
  void set_geometry(int pos_x, int pos_y, int width, int height, int speed);
  void set_track_style(Color fill_color, Color outline_color, int outline_thickness);
  void set_note_style(int height, Color color);
  void set_note_style(int height, Image image);
  void set_iterator(vci iter_begin, vci iter_end);
  void update();
  void sync(int current_time);
  void draw() const;
};

enum playground_status { playing, paused, not_running };

class playground : public std::vector<track>, public rectangle {
  int track_number;
  Color outline;
  int thick;
  int current_time;
  int speed;
  song_map song;
  playground_status status;
  bool is_initialized;
public:
  playground();
  playground(int pos_x, int pos_y, int width, int height, int track_number,
             Color outline_color, int outline_thickness, Color inner_fill_color,
             Color inner_outline_color, int inner_thickness);
  ~playground() = default;

  // Setter
  void set_geometry(int pos_x, int pos_y, int width, int height, int track_number, int speed);
  void set_playground_style(Color outline_color, int outline_thickness);
  void set_track_style(Color fill_color, Color outline_color, int outline_thickness);

  void load(const song_map & selected_song);
  void play();
  void pause();
  void quit();
  void draw() const;
};

class game {
  // A ultimately bit class which will contain everything except story and
  // settings, song selection
private:
  int track_number;
  void _draw_note();
  void _draw_track();

public:
  game();
  ~game();
};
} // namespace gyp
