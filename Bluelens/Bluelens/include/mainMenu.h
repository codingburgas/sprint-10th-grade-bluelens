#pragma once
#ifndef MAINMENU_H
#define MAINMENU_H

#include "raylib.h"
int main();
enum MenuState { MENU_MAIN, MENU_CONTROLS, MENU_PLAYING,MENU_EXIT ,MENU_THEMES,MENU_CUSTOM };
MenuState DrawMainMenu();
MenuState DrawControlsMenu();
MenuState DrawThemesMenu();
MenuState DrawCustomMenu(int& mazeSize);
#endif
