#pragma once
#ifndef MAINMENU_H
#define MAINMENU_H

#include "raylib.h"

// Menu states
enum MenuState
{
    MENU_MAIN,
    MENU_CONTROLS,
    MENU_PLAYING,
    MENU_EXIT,
    MENU_THEMES,
    MENU_CUSTOM,
    MENU_DEAD
};

// Main menu functions
MenuState DrawMainMenu();
MenuState DrawControlsMenu();
MenuState DrawThemesMenu();
MenuState DrawCustomMenu(int& mazeSize);

// Pause menu handling
bool HandlePauseMenu(bool& gamePaused, bool& exitGame);

#endif
