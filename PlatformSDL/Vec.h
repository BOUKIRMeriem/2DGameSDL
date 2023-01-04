#pragma once
class Vec2 {
public:
	float x;
	float y;

	Vec2(){
		x = y = 0;
	}
	Vec2(float x, float y) {
		this->x = x;
		this->y = y;
	}
};