#pragma once
#ifndef MAINMENU_H
#define MAINMENU_H

#include "raylib.h"
int main();
enum MenuState { MENU_MAIN, MENU_CONTROLS, MENU_PLAYING, MENU_EXIT, MENU_DEAD};
MenuState DrawMainMenu();
MenuState DrawControlsMenu();
#endif
