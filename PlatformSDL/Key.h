#pragma once
#pragma once
#include"GameObject.h" 
#include <iostream>
#include <string>
using namespace std;

class Key : public GameObject
{

public:

	Key(int x, int y)
		:GameObject(x, y, speed, new SpriteSheet("assets/key.png", 1, 1, 1, 32, 32), PLAYER, 1)
	{
		spriteSheet->setCurrent(0); // right
	}

	void update() {

	}

	void onCollide(GameObject* other) {
		if (other->getType() == PLAYER) {
			Util::get()->loadNextLevel = true;
		}
	}

	void draw() {
		spriteSheet->follow(pos.x - Util::get()->camX, pos.y - Util::get()->camY);
		spriteSheet->draw();

	}
};

