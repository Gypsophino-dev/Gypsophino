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
      current_time(0), visible_time(0), error_time(0), speed(-1),
      is_iterator_set(false) {
  note_style.height = 50;
  note_style.color = DEFAULT_FG;
}

void track::set_geometry(int pos_x, int pos_y, int width, int height) {
  x = pos_x;
  y = pos_y;
  this->width = width;
  this->height = height;
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

void track::set_time(int current_time, int visible_time, int error_time) {
  this->current_time = current_time;
  this->visible_time = visible_time;
  this->error_time = error_time;
}

void track::set_speed(int speed) {
  this->speed = speed;
}


void track::set_iterator(vci iter_begin, vci iter_end) {
  is_iterator_set = true;
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

int track::init() {
  if (x == -1 || y == -1 || width == -1 || height == -1) {
    // check if geometry is set
    return 1;
  }
  if (is_iterator_set == false) { // check if iterators are set
    return 1;
  }
  if (speed == -1) { // check if speed is set
    speed = DEFAULT_SPEED;
  }
  if (visible_time == 0) { // check if time is set
    visible_time = height / speed;
  }
  return 0;
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

void track::hit() {
  if (notes_current == notes_end) {
    return;
  }
  if (*notes_current >= current_time && *notes_current < visible_time) {
    notes_current++;
  }
}

// Class: playground
playground::playground()
    : track_number(DEFAULT_TRACK_NUM), outline(DEFAULT_FG),
      thick(DEFAULT_THICKNESS), current_time(0), speed(-1), song(nullptr),
      status(not_running), is_initialized(false) {}

/* Old Constructor */
/*
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
*/

playground::~playground() {
  song = nullptr; // Why do this?
}

void playground::set_geometry(int pos_x, int pos_y, int width, int height,
                              int track_number) {
  x = pos_x;
  y = pos_y;
  this->width = width;
  this->height = height;
  this->track_number = track_number;
}

void playground::set_playground_style(Color outline_color,
                                      int outline_thickness) {
  outline = outline_color;
  thick = outline_thickness;
}

void playground::set_speed(int speed) {
  this->speed = speed;
}

void playground::set_track(Color fill_color, Color outline_color,
                           int outline_thickness) {
  if (speed == -1) {
    speed = DEFAULT_SPEED;
  }
  if (is_initialized) {
    for (auto &i : *this) {
      i.set_track_style(fill_color, outline_color, outline_thickness);
    }
  } else {
    int track_width = width / track_number;
    for (int i = 0; i < track_number; i++) {
      push_back(track());
      back().set_geometry(x + i * track_width, y, track_width, height);
      back().set_track_style(fill_color, outline_color, outline_thickness);
      back().set_note_style(50, BLACK);
      back().set_speed(speed);
    }
    is_initialized = true;
  }
}

void playground::init() {
  if (!IsAudioDeviceReady()) {
    InitAudioDevice();
    while (!IsAudioDeviceReady()) {
      ;
    }
  }
}

void playground::load(const song_map * selected_song) {
  song = selected_song;
  for (int i = 0; i < song->track_number; i++) {
    at(i).set_iterator(song->notes.at(i).cbegin(), song->notes.at(i).cend());
    at(i).init();
  }
  music = LoadMusicStream(selected_song->music_path.c_str());
  PlayMusicStream(music);
}

void playground::play() {
  if (!IsMusicPlaying(music)) {
    ResumeMusicStream(music);
  }
  UpdateMusicStream(music);
  status = playing;
  current_time++;
  for (int i = 0; i < track_number; i++) {
    at(i).update();
  }
}

void playground::pause() {
  if (IsMusicPlaying(music)) {
    PauseMusicStream(music);
  }
  status = paused;
}

void playground::quit() {
  StopMusicStream(music);
  UnloadMusicStream(music);
}

void playground::draw() const {
  for (const auto &i : *this) {
    i.draw();
  }
  DrawRectangleLinesEx(this->ray_rectangle(), thick, outline);
}

} // namespace gyp
