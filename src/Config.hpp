#pragma once
#include <cstdint>
#include <limits>

static const std::uint32_t WIN_WIDTH = 1600;
static const std::uint32_t WIN_HEIGHT = 900;
static const std::uint32_t RENDER_WIDTH = 1200;
static const std::uint32_t RENDER_HEIGHT = (RENDER_WIDTH / 16) * 9;
static const float SENSITIVITY = 0.005f;
static const float BASE_CAMERA_HEIGHT = 3;

static const float PLANE_SIZE_X = 20;
static const float PLANE_SIZE_Y = 20;
static const float BASE_MAX_FUNCTION = 90;