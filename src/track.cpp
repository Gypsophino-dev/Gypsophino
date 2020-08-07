#include "track.hpp"
#include "const.hpp"
#include "shape.hpp"
#include <cmath>

namespace gyp {

track::track()
    : fill(DEFAULT_BG), outline(DEFAULT_FG), thick(DEFAULT_THICKNESS),
      bind_key(KEY_SPACE), current_time(0), visible_time(0), error_time(0),
      speed(-1), is_iterator_set(false), judge_height(0) {
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
                            int outline_thickness, KeyboardKey bind_key) {
  fill = fill_color;
  outline = outline_color;
  thick = outline_thickness;
  this->bind_key = bind_key;
}

void track::set_note_style(int h, Color c) {
  note_style.height = h;
  note_style.color = c;
}

void track::set_note_style(int h, Image image) {
  note_style.height = h;
  note_style.image = image;
}

void track::set_time(int current_time, int visible_time, int error_time) {
  this->current_time = current_time;
  this->visible_time = visible_time;
  this->error_time = error_time;
  track_score.set_error(error_time);
}

void track::set_speed(int speed) { this->speed = speed; }

void track::set_iterator(vci iter_begin, vci iter_end) {
  is_iterator_set = true;
  notes_begin = iter_begin;
  notes_end = iter_end;
  notes_current = iter_begin;
  notes_visible = iter_begin;
  while (notes_current != notes_end &&
         *notes_current < static_cast<float>(current_time)) {
    notes_current++;
  }
  while (notes_visible != notes_end &&
         *notes_visible < static_cast<float>(visible_time)) {
    notes_visible++;
  }
}

[[nodiscard]] float track::get_score() const {
  return track_score.current / (track_score.total == 0 ? 1 : track_score.total);
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
  judge_height = (error_time * height) / visible_time;
  return 0;
}

void track::update() {
  current_time++;
  visible_time++;
  while (notes_current != notes_end &&
         *notes_current < static_cast<float>(current_time)) {
    notes_current++;
  }
  while (notes_visible != notes_end &&
         *notes_visible < static_cast<float>(visible_time)) {
    notes_visible++;
  }
}

void track::sync(int current_time) {
  this->current_time = current_time;
  this->visible_time = current_time + height / speed;
  notes_current = notes_begin;
  notes_visible = notes_begin;
  while (notes_current != notes_end &&
         *notes_current < static_cast<float>(this->current_time)) {
    notes_current++;
  }
  while (notes_visible != notes_end &&
         *notes_visible < static_cast<float>(this->visible_time)) {
    notes_visible++;
  }
}

void track::draw() const {
  DrawRectangle(x, y, width, height, fill);
  for (vci i = notes_current; i != notes_visible && i != notes_end; i++) {
    DrawRectangle(x,
                  y + height -
                      (static_cast<int>(std::round(*i)) - current_time) * speed,
                  width, note_style.height, note_style.color);
  }
  DrawRectangleLinesEx(ray_rectangle(), thick, outline);
  DrawLineEx(vector2d(x, DEFAULT_HEIGHT - judge_height).ray_vector2d(),
             vector2d(x + width, DEFAULT_HEIGHT - judge_height).ray_vector2d(), static_cast<float>(thick), BLACK);
}

void track::draw_pressed() const {
  DrawRectangle(x, DEFAULT_HEIGHT - judge_height, width, judge_height, outline);
}

void track::hit() {
  if (notes_current == notes_end) {
    return;
  }
  if (*notes_current >= static_cast<float>(current_time) &&
      *notes_current < static_cast<float>(visible_time)) {
    track_score.add(current_time + error_time, *notes_current);
    notes_current++;
  }
}

void track::interact() {
  if (IsKeyPressed(bind_key)) {
    hit();
  }
  if (IsKeyDown(bind_key)) {
    draw_pressed();
  }
}

} // namespace gyp
