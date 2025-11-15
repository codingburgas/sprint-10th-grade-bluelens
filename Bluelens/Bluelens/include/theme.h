#pragma once
#ifndef THEME_H
#define THEME_H

#include "raylib.h"

struct Theme
{
    const char* name;
    Color background;
    Color wallColor;
    Color playerColor;
    Color enemyColor;
    Color textColor;
    Color buttonColor;
    Color buttonHoverColor;
};

extern Theme themes[];
extern int currentThemeIndex;
extern const int THEME_COUNT;

// Function to get current theme
Theme GetCurrentTheme();
void SetTheme(int index);

#endif