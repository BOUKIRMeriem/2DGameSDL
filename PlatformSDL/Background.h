#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Util.h"
#include "GameObject.h"

class MImage  {
    SDL_Texture* texture;
    SDL_Rect    src;
    SDL_Point center;

public:
    SDL_Rect    dest;

    MImage(const char* path, int x, int y, int w, int h) {
        texture = SDL_CreateTextureFromSurface(Util::get()->renderer, IMG_Load(path));
        src.x = 0;
        src.y = 0;
        src.w = w;
        src.h = h;
        dest.x = x;
        dest.y = y;
        dest.w = w;
        dest.h = h;
    }

    void draw() {
        SDL_RenderCopy(Util::get()->renderer, texture, NULL, &dest);
    }
};

class Background : public GameObject {
    MImage* image;
    int y = 0;
    int x = -700;
public:
    Background() {
        image = new MImage("assets/bg.png", 0, y, 700, 700);
        type = BACKGROUND;
    }
    void update() {

    }
    void draw() {
        image->dest.x = x - Util::get()->camX;
        image->dest.y = 0;
        image->draw();

        image->dest.x = 700 + x - Util::get()->camX;
        image->dest.y = 0;
        image->draw();

        image->dest.x = 700 * 2 + x - Util::get()->camX;
        image->dest.y = 0;
        image->draw();

        image->dest.x = 700 * 3 + x - Util::get()->camX;
        image->dest.y = 0;
        image->draw();
    }
};