#pragma once
#include <cstdint>

namespace pixelmancy {

constexpr static uint16_t DEFAULT_FRAME_DELAY_IN_MS = 500;
constexpr static uint16_t DEFAULT_FRAME_DELAY = DEFAULT_FRAME_DELAY_IN_MS / 10;
constexpr uint16_t MAX_COLORS_SUPPORTED_IN_GIF = 256;
constexpr int COLOR_CLAMP_VALUE = 255;
constexpr int DEFAULT_ALPHA = 255;
constexpr int MAX_ALPHA = 255;
constexpr int MIN_ALPHA = 0;
constexpr int DEFAULT_OUTLINE_WIDTH = 1;

} // namespace pixelmancy
