#pragma once
#ifndef MAINMENU_H
#define MAINMENU_H

#include "raylib.h"

enum MenuState { MENU_MAIN, MENU_CONTROLS, MENU_PLAYING };

MenuState DrawMainMenu();

#endif
