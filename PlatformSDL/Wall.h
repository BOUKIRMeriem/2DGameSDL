#pragma once
#include"GameObject.h" 
#include <iostream>
#include <string>

class Wall : public GameObject
{
	GameObject* player = nullptr;
	
	float timeToFLip = 0;
	float countTime = 0;
public:

	Wall(int x, int y, int w, int h,float timeToFLip = 0)
		:GameObject(x, y, 0, new SpriteSheet("null.png", 1, 1, 1, w, h), WALL, 1)
	{
		spriteSheet->follow(pos.x - Util::get()->camX, pos.y - Util::get()->camY);
		this->timeToFLip = timeToFLip;
		vel.x = 3;
	}

	void update() {

		if (timeToFLip > 0) { // moving wall
			pos.x += vel.x;
			countTime += Util::get()->deltaTime;
			if (countTime >= timeToFLip) {
				countTime = 0;
				vel.x *= -1;
			}
		}


		spriteSheet->follow(pos.x - Util::get()->camX, pos.y - Util::get()->camY);
	}

	void onCollide(GameObject* other) {
		if (other->getType() == PLAYER) {
			player = other;
			SDL_Rect playerRect = other->getRect();
			SDL_Rect wallRect = getRect();

			// moving wall
			if (timeToFLip > 0) {
				player->setPos((player->getPos().x + vel.x), player->getPos().y);
			}

			player->setOnGround(false);
			// stop player
			// 2 box collide
			// top , left, right, bottom

			if (playerRect.y + playerRect.h > wallRect.y && wallRect.y > playerRect.y) // player above the wall
			{
				float diff = playerRect.y + playerRect.h - wallRect.y;
				player->setVel(player->getVel().x, 0);
				player->setOnGround(true);
				player->setPos(player->getPos().x , playerRect.y - diff + 2);
			}
			// player on the left side
			else if (playerRect.y + playerRect.h < wallRect.y + wallRect.h && playerRect.x + playerRect.w > wallRect.x && playerRect.x < wallRect.x) {
				float diff = playerRect.x + playerRect.w - wallRect.x;
				player->setPos(playerRect.x - diff + Util::get()->camX, playerRect.y);
				player->setVel(0, player->getVel().y);
			}
			// player on the right side
			else if (playerRect.y + playerRect.h < wallRect.y + wallRect.h && playerRect.x < wallRect.x + wallRect.w && playerRect.x + playerRect.w > wallRect.x) {
				float diff = wallRect.x + wallRect.w - playerRect.x;
				player->setPos(playerRect.x + diff + Util::get()->camX, playerRect.y);
				player->setVel(0, player->getVel().y);
				//player->setPos(wallRect.x + wallRect.w + Util::get()->camX, playerRect.y);
				//player->setDirXy(0, 0);
			}
			// player below the wall
			else if (wallRect.y + wallRect.h > playerRect.y && playerRect.y > wallRect.y)
			{
				float diff = wallRect.y + wallRect.h - playerRect.y;
				player->setVel(player->getVel().x, 0);
				player->setPos(player->getPos().x, playerRect.y + diff );
			}
		}
	}

	void draw() {
		drawRectangle(getRect(),195,133,55);
	}
};

