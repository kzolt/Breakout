#pragma once

#include "Log.h"

#define ASSERT(condition, message) if (!(condition)) { LOG_FATAL(message); __debugbreak(); }