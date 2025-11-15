#pragma once
#ifndef CONTROLS_H
#define CONTROLS_H
#include "raylib.h"
#include <string>

struct ControlMenu
{
    bool active = false;
};
bool HandlePauseMenu(bool& gamePaused, bool& exitGame);

#endif
