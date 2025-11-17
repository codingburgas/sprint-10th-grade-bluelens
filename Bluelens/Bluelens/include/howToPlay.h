#pragma once
#ifndef CONTROLS_H
#define CONTROLS_H
#include "raylib.h"
#include <string>

// Represents the pause/control menu state.
struct ControlMenu
{
    // Flag for whether the control menu is active
    bool active = false;
};
bool HandlePauseMenu(bool& gamePaused, bool& exitGame);

#endif
