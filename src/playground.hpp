#pragma once

#include "song_map.hpp"
#include "track.hpp"
#include "shape.hpp"
#include <raylib.h>
#include <vector>

namespace gyp {

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
  const song_map *song;
  Music music;
  playground_status status;
  bool is_initialized;
  std::vector<std::vector<float>> real_notes;

public:
  // Constructor & Desttructor
  playground();
  ~playground();

  // Setter
  void set_geometry(int pos_x, int pos_y, int width, int height,
                    int track_number);
  void set_playground_style(Color outline_color, int outline_thickness);
  void set_speed(int speed);
  // CAUTION: set_track() must be called after setter above !!
  void set_track(Color fill_color, Color outline_color, int outline_thickness,
                 int note_height, Color note_color);
  void set_track(Color fill_color, Color outline_color, int outline_thickness,
                 int note_height, Image note_image);

  // Method
  // CAUTION: Any method must be called after set_track(),
  //          for performance, these function will not examine
  //          is_initialized before they run.
  // Contain: [i].set_interator [i].init()
  // CAUTION: Init() must be run at first.
  void init();
  void load(const song_map *selected_song, float fps);
  void play();  // play a single frame
  void pause(); // pause for a single frame
  void quit();
  void draw() const;
};

} // namespace gyp
