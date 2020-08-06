#pragma once

#include <raylib.h>
#include <string>
#include <array>

namespace gyp {

const int DEFAULT_WIDTH = 1920;
const int DEFAULT_HEIGHT = 1080;
const int DEFAULT_TRACK_NUM = 4;
const Color DEFAULT_FG = BLACK;
const Color DEFAULT_BG = BLANK;
const int DEFAULT_GEOMETRY = -1;
const int DEFAULT_THICKNESS = 5;
const int DEFAULT_SPEED = 10;
const float DEFAULT_FONT_SIZE = 20.0F;
const float DEFAULT_FONT_SPACING = 0.5F;
//extern const std::string TOP_NAME;
extern const char * TOP_NAME;
extern const std::array<KeyboardKey, 9> DEFAULT_KEY_BINDING;

} // namespace gyp
