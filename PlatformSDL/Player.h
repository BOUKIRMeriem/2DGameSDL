#pragma once
#include"GameObject.h" 
#include <iostream>
#include <string>
using namespace std;

class Player : public GameObject
{
	int dirX;
	int dirY;

public:


	Player(int x, int y, int speed) 
		:GameObject(x,y,speed,new SpriteSheet("assets/player.png",2,1,2,48,48),PLAYER,1)
	{
		spriteSheet->setCurrent(0); // 
	}

	void update() {
		GameObject::update();
		applyForce(Vec2(0, 0.58)); // gravity

		pos.x += dirX * speed; // move left right

		if (pos.y > Util::get()->HEIGHT) {
			Util::get()->gameStatus = Util::GAMEOVER;
		}

	}

	void draw() {
		spriteSheet->follow(pos.x - Util::get()->camX, pos.y - Util::get()->camY);
		spriteSheet->draw();

	}

	void onKeyDown(SDL_Keycode key) { 
		// adws : move left right up down
		if (key == SDLK_a) {
			dirX = -1;
			spriteSheet->setCurrent(1);
		}
		else if (key == SDLK_d) {
			dirX = 1;
			spriteSheet->setCurrent(0);
		}
		if (key == SDLK_w) {
			dirY = -1;
		}
		else if (key == SDLK_s) {
			dirY = 1;
		}

		if (key == SDLK_SPACE && !jumping) { // jump and only jump 1
			jumping = true;
			pos.y -= 5;
			applyForce(Vec2(0, -12.81));
			spriteSheet->follow(pos.x - Util::get()->camX, pos.y - Util::get()->camY);
		}
	}
	void onKeyUp(SDL_Keycode key) {
		// reset direction if key up
		if (key == SDLK_a && dirX == -1) {
			dirX = 0;
		}
		else if (key == SDLK_d && dirX == 1) {
			dirX = 0;
		}
		if (key == SDLK_w && dirY == -1) {
			dirY = 0;
		}
		else if (key == SDLK_s && dirY == 1) {
			dirY = 0;
		}
	}
};

