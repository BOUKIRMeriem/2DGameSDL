#pragma once
#include "SpriteSheet.h"
#include "Vec.h"
using namespace std;
class GameObject
{
public:

	enum TYPE
	{
		PLAYER,
		ENEMY,
		WALL,
		KEY,
		BACKGROUND
	};

protected:
	SpriteSheet* spriteSheet;

	int speed;
	bool isAlive = true;
	bool onGround = false;
	bool jumping = false;

	int life;
	TYPE type;

	Vec2 pos; // position
	Vec2 vel; // velocity
	Vec2 acc; // acceleration

public:
	GameObject(){}
	GameObject(int x, int y,int speed, SpriteSheet* sheet, TYPE type, int life = 1) {
		pos = Vec2(x, y);
		this->speed = speed;
		spriteSheet = sheet;
		this->type = type;
		this->life = life;
	}
	void applyForce(Vec2 f) {
		acc = Vec2(acc.x + f.x, acc.y + f.y);
	}

	// child class may implement these virtual function
	virtual void update() {
		vel = Vec2(vel.x + acc.x, vel.y + acc.y);
		pos = Vec2(pos.x + vel.x, pos.y + vel.y);
		acc = Vec2(0, 0);
	}
	virtual void draw() {
		spriteSheet->playAnimation();
		spriteSheet->follow(pos.x - Util::get()->camX, pos.y - Util::get()->camY);
		spriteSheet->draw();
	}
	virtual void onCollide(GameObject* obj) {}
	virtual void onMouseDown(int x, int y) {}
	virtual SDL_Rect getRect() {
		if (type == BACKGROUND) {
			return { 0,0,0,0 };
		}
		return spriteSheet->getRect();
	}
	bool checkCollide(GameObject* obj) {
		if (type == BACKGROUND) {
			return false;
		}

		SDL_Rect a = getRect();
		SDL_Rect b = obj->getRect();

		if (a.x < b.x + b.w &&
			a.x + a.w > b.x &&
			a.y < b.y + b.h &&
			a.h + a.y > b.y) {
			return true;
		}
		return false;
	}

	void setAlive(bool alive) {
		this->isAlive = alive;
	}
	int getLife() { return life; }
	void setLife(int l) {
		life = l;
		if (life <= 0) {
			isAlive = false;
		}
	}
	bool isDead() {
		return isAlive == false;
	}
	void setOnGround(bool b) {
		onGround = b;
		if (onGround) {
			jumping = false;
		}
	}

	TYPE getType() {
		return type;
	}


	// useful function
	static bool checkClickCollide(SDL_Rect a, int x, int y) {
		if (x >= a.x && x <= a.x + a.w
			&& y >= a.y && y <= a.y + a.h) {
			return true;
		}
		return false;
	}
	void drawRectangle(SDL_Rect r,int red,int green,int blue) {
		SDL_SetRenderDrawColor(Util::get()->renderer, red, green, blue, 1);
		SDL_RenderFillRect(Util::get()->renderer, &r);
	}

	Vec2 getPos() {
		return pos;
	}
	void setPos(Vec2 v) {
		pos = v;
	}
	void setPos(float x,float y) {
		pos = Vec2(x,y);
		spriteSheet->follow(pos.x - Util::get()->camX, pos.y - Util::get()->camY);
	}
	Vec2 getVel() {
		return vel;
	}
	void setVel(float x, float y) {
		vel = Vec2(x, y);
	}
};

