#include "game.hpp"

namespace gyp {

note::note() : hit_time(-1) {}

note::note(int hit_t, int speed) : hit_time(hit_t) {
  velocity.x = 0;
  velocity.y = speed;
}

void note::draw() { DrawRectangle(x, y, width, height, color); }

//  Class: track
track::track()
    : fill(DEFAULT_BG), outline(DEFAULT_FG), thick(DEFAULT_THICKNESS),
      current_time(0), visible_time(0), speed(1), notes_begin(nullptr),
      notes_end(nullptr), notes_current(nullptr), notes_visible(nullptr) {
  note_style.height = 50;
  note_style.color = DEFAULT_FG;
}

track::track(int pos_x, int pos_y, int width, int height, int speed)
    : fill(DEFAULT_BG), outline(DEFAULT_FG), thick(DEFAULT_THICKNESS),
      current_time(0), speed(speed) {
  x = pos_x;
  y = pos_y;
  this->width = width;
  this->height = height;
  visible_time = 0 + height / speed;
}

track::track(int pos_x, int pos_y, int w, int h, int v, Color fil_c,
             Color otl_c, int otl_tck)
    : fill(fil_c), outline(otl_c), thick(otl_tck), current_time(0), speed(v) {
  x = pos_x;
  y = pos_y;
  width = w;
  height = h;
  visible_time = 0 + height / speed;
  note_style.height = 50;
  note_style.color = BLACK;
}

void track::set_geometry(int pos_x, int pos_y, int width, int height,
                         int speed) {
  x = pos_x;
  y = pos_y;
  this->width = width;
  this->height = height;
  this->speed = speed;
  visible_time = height / speed;
}

void track::set_track_style(Color fill_color, Color outline_color,
                            int outline_thickness) {
  fill = fill_color;
  outline = outline_color;
  thick = outline_thickness;
}

void track::set_note_style(int h, Color c) {
  note_style.height = h;
  note_style.color = c;
}

void track::set_iterator(vci iter_begin, vci iter_end) {
  notes_begin = iter_begin;
  notes_end = iter_end;
  notes_current = iter_begin;
  notes_visible = iter_begin;
  while (notes_current != notes_end && *notes_current < current_time) {
    notes_current++;
  }
  while (notes_visible != notes_end && *notes_visible < visible_time) {
    notes_visible++;
  }
}

void track::update() {
  current_time++;
  visible_time++;
  while (notes_current != notes_end && *notes_current < current_time) {
    notes_current++;
  }
  while (notes_visible != notes_end && *notes_visible < visible_time) {
    notes_visible++;
  }
}

void track::draw() const {
  DrawRectangle(x, y, width, height, fill);
  for (vci i = notes_current; i != notes_visible && i != notes_end; i++) {
    DrawRectangle(x, y + height - (*i - current_time) * speed, width, note_style.height,
                  note_style.color);
  }
  DrawRectangleLinesEx(ray_rectangle(), thick, outline);
}

// Class: playground

playground::playground()
    : track_number(DEFAULT_TRACK_NUM), outline(DEFAULT_FG),
      thick(DEFAULT_THICKNESS), current_time(0), speed(DEFAULT_SPEED),
      status(not_running), is_initialized(false) {}

playground::playground(int pos_x, int pos_y, int w, int h, int t_num,
                       Color otl_c, int otl_tck, Color inr_fil_c,
                       Color inr_otl_c, int inr_tck)
    : track_number(t_num), outline(otl_c), thick(otl_tck), current_time(0) {
  x = pos_x;
  y = pos_y;
  width = w;
  height = h;
  int track_width = width / t_num;
  for (int i = 0; i < t_num; i++) {
    this->push_back(track(pos_x + i * track_width, pos_y, track_width, h, 1,
                          inr_fil_c, inr_otl_c, inr_tck));
  }
}

void playground::set_geometry(int pos_x, int pos_y, int width, int height,
                              int track_number, int speed) {
  x = pos_x;
  y = pos_y;
  this->width = width;
  this->height = height;
  this->track_number = track_number;
  this->speed = speed;
}

void playground::set_playground_style(Color outline_color,
                                      int outline_thickness) {
  outline = outline_color;
  thick = outline_thickness;
}

void playground::set_track_style(Color fill_color, Color outline_color,
                                 int outline_thickness) {
  if (is_initialized) {
    for (auto &i : *this) {
      i.set_track_style(fill_color, outline_color, outline_thickness);
    }
  } else {
    int track_width = width / track_number;
    for (int i = 0; i < track_number; i++) {
      //push_back(track(x + i * track_width, y, track_width, height, speed, fill_color, outline_color, outline_thickness));
      push_back(track());
      back().set_geometry(x + i * track_width, y, track_width, height, speed);
      back().set_track_style(fill_color, outline_color, outline_thickness);
      back().set_note_style(50, BLACK);
    }
    is_initialized = true;
  }
}

void playground::load(const song_map &selected_song) {
  song = selected_song;
  for (int i = 0; i < song.track_number; i++) {
    at(i).set_iterator(song.notes.at(i).cbegin(), song.notes.at(i).cend());
  }
}

void playground::play() {
  status = playing;
  current_time++;
  for (int i = 0; i < track_number; i++) {
    at(i).update();
  }
}

void playground::pause() { status = paused; }

void playground::quit() {}

void playground::draw() const {
  for (const auto &i : *this) {
    i.draw();
  }
  DrawRectangleLinesEx(this->ray_rectangle(), thick, outline);
}

} // namespace gyp
