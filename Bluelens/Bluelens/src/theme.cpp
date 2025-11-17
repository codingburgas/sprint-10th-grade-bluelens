#include "../include/theme.h"

Theme themes[] = {
    {
        "Classic Dark",
        DARKGRAY,      
        GRAY,        
        BLUE,          
        RED,           
        RAYWHITE,      
        GRAY,          
        LIGHTGRAY      
    },
    {
        "Ocean",
        {20, 40, 80, 255},     
        {100, 200, 255, 255},  
        {255, 200, 50, 255},    
        {255, 100, 100, 255},   
        {200, 230, 255, 255},   
        {40, 80, 120, 255},     
        {60, 120, 180, 255}    
    },
    {
        "Forest",
        {20, 40, 20, 255},      
        {100, 150, 50, 255},    
        {255, 200, 100, 255},   
        {150, 50, 50, 255},     
        {200, 255, 200, 255},  
        {50, 100, 50, 255},    
        {80, 150, 80, 255}     
    },
    {
        "Neon",
        {10, 10, 30, 255},    
        {255, 0, 255, 255},   
        {0, 255, 255, 255},  
        {255, 255, 0, 255},   
        {255, 0, 255, 255},    
        {50, 0, 100, 255},    
        {100, 0, 200, 255}    
    },

    {
        "Light Mode",
        {240, 240, 240, 255},  
        {80, 80, 80, 255},     
        {50, 100, 200, 255},   
        {200, 50, 50, 255},    
        {20, 20, 20, 255},     
        {200, 200, 200, 255},   
        {170, 170, 170, 255}   
    }
};
int currentThemeIndex = 0;
const int THEME_COUNT = sizeof(themes) / sizeof(themes[0]);

// Returns the active theme currently being used by the game
Theme GetCurrentTheme()
{
    return themes[currentThemeIndex];
}

void SetTheme(int index)
{
    if (index >= 0 && index < THEME_COUNT)
    {
        currentThemeIndex = index;
    }
}