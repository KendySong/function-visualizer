#pragma once
#include <cstdint>

static const std::uint32_t WIN_WIDTH = 1600;
static const std::uint32_t WIN_HEIGHT = 900;
static const std::uint32_t RENDER_WIDTH = 1200;
static const std::uint32_t RENDER_HEIGHT = (RENDER_WIDTH / 16) * 9;
static const float SENSITIVITY = 0.005f;
static const float BASE_CAMERA_HEIGHT = 10;

static const float PLANE_SIZE_X = 50;
static const float PLANE_SIZE_Y = 50;
static const float PLANE_GRID_X = 20;
static const float PLANE_GRID_Y = 20;
static const float BASE_MAX_FUNCTION = 20;