#pragma once
#include <SDL.h>
#include <iostream>
#include <SDL_ttf.h>
class Util
{

    static Util* clock;

    Uint32 minimum_fps_delta_time = (1000 / 6); // minimum 6 fps, if the computer is slower than this: slow down.
    Uint32 last_game_step = SDL_GetTicks(); // initial value
    uint32_t last_tick_time = 0;

    TTF_Font* font;


public:
    float camX = 0;
    float camY = 0;
    bool loadNextLevel = false;


    const int WIDTH = 700;
    const int HEIGHT = 700;
    bool DEBUG = true;

    SDL_Renderer* renderer;
    uint32_t deltaTime = 0;

    enum GAMESTATUS
    {
        PLAYING,
        GAMEOVER,
        MENU
    };
    GAMESTATUS gameStatus = MENU;

    void init();

    static Util* get();
    void showText(int x, int y, std::string text, SDL_Color fg = { 232, 187, 23 }); // show text
    void ticKClock();// calculate deltatime


};


