#include "playground.hpp"
#include "const.hpp"

#ifndef RELEASE
#include <iostream>
#endif

namespace gyp {

playground::playground()
    : track_number(DEFAULT_TRACK_NUM), outline(DEFAULT_FG),
      thick(DEFAULT_THICKNESS), current_time(0), speed(-1), song(nullptr),
      status(not_running), is_initialized(false), real_notes(DEFAULT_TRACK_NUM) {}

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

void playground::set_speed(int speed) { this->speed = speed; }

void playground::set_track(Color fill_color, Color outline_color, int outline_thickness,
                 int note_height, Color note_color) {
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
      back().set_note_style(note_height, note_color);
      back().set_speed(speed);
    }
    is_initialized = true;
  }
}

void playground::set_track(Color fill_color, Color outline_color, int outline_thickness,
                 int note_height, Image note_image) {
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
      back().set_note_style(note_height, note_image);
      back().set_speed(speed);
    }
    is_initialized = true;
  }
}

void playground::init() {
  real_notes.resize(track_number);
  if (!IsAudioDeviceReady()) {
    InitAudioDevice();
    while (!IsAudioDeviceReady()) {
      ;
    }
  }
}

void playground::load(const song_map *selected_song, float fps) {
  song = selected_song;
  if (song->track_number != track_number) {
    track_number = song->track_number;
    real_notes.resize(track_number);
  }
  float frame_per_fraction = 60.0F * fps / static_cast<float>(song->bpm * song->base_fraction);
  for (int i = 0; i < song->track_number; i++) {
    for (auto j = song->notes.at(i).cbegin(); j != song->notes.at(i).cend(); j++) {
      real_notes.at(i).push_back((static_cast<float>(*j) + song->offset) * frame_per_fraction);
    }
  }
  for (int i = 0; i < song->track_number; i++) {
    at(i).set_iterator(real_notes.at(i).cbegin(), real_notes.at(i).cend());
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
#ifndef RELEASE
  std::cerr << "[Info] Current time: " << current_time << std::endl;
#endif
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
  if (IsMusicPlaying(music)) {
    StopMusicStream(music);
  }
  UnloadMusicStream(music);
}

void playground::restart() {
  StopMusicStream(music);
  for (auto &i : *this) {
    i.sync(0);
  }
  PlayMusicStream(music);
}

void playground::draw() const {
  for (const auto &i : *this) {
    i.draw();
  }
  DrawRectangleLinesEx(this->ray_rectangle(), thick, outline);
}

} // namespace gyp
